#include "Logger.h"

Logger &Logger::getInstance()
{
    // 返回静态局部变量的实例，保证单例模式
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    // 在构造函数中启动异步日志线程
    log_thread = std::thread(&Logger::asyncLog, this);
}

Logger::~Logger()
{
    {
        // 在析构函数中设置运行标志为 false，并通知所有等待的线程
        std::lock_guard<std::mutex> lock(log_mutex);
        running = false;
    }
    log_cv.notify_all(); // 唤醒所有等待的线程
    if (log_thread.joinable())
    {
        log_thread.join(); // 等待异步日志线程结束
    }

    if (log_file.is_open())
    {
        log_file.close(); // 关闭日志文件流
    }
}

void Logger::configure(const std::string &logFileNamePrefix, bool consoleOutput, std::size_t maxFileSize, bool async, Level minLogLevel)
{
    // 使用 std::lock_guard 保证线程安全
    std::lock_guard<std::mutex> guard(log_mutex);

    // 检查日志文件名前缀是否为空
    if (logFileNamePrefix.empty())
    {
        throw std::invalid_argument("日志文件名前缀不能为空");
    }

    // 检查最大文件大小是否小于 1024 字节
    if (maxFileSize < 1024)
    {
        throw std::invalid_argument("最大文件大小必须至少为 1KB");
    }

    // 设置类成员变量
    log_file_name_prefix = logFileNamePrefix;
    log_to_console = consoleOutput;
    this->max_file_size = maxFileSize;
    async_logging = async;
    min_log_level = minLogLevel;

    // 打开日志文件
    openLogFile();
}

std::string Logger::constructLogFileName() const
{
    // 构造日志文件名
    return log_file_name_prefix + "_" + current_date + ".log";
}

void Logger::openLogFile()
{
    // 获取构造的日志文件名
    std::string log_file_name = constructLogFileName();

    try
    {
        // 以追加模式打开日志文件
        log_file.open(log_file_name, std::ios_base::app);
        if (!log_file.is_open())
        {
            // 如果打开失败，抛出异常
            throw std::ios_base::failure("打开日志文件失败: " + log_file_name);
        }
        // 更新当前日期
        current_date = getCurrentDate();
    }
    catch (const std::ios_base::failure &e)
    {
        // 捕获异常并输出错误信息
        std::cerr << e.what() << std::endl;
        // 如果打开日志文件失败，则将日志输出到控制台
        log_to_console = true;
    }
}

void Logger::checkDateChange()
{
    std::string date = getCurrentDate(); // 获取当前日期字符串
    if (date != current_date)
    {
        log_file.close(); // 关闭当前日志文件
        openLogFile(); // 打开新的日志文件
    }
}

std::string Logger::getCurrentTime()
{
    auto now = std::chrono::system_clock::now(); // 获取当前时间点
    auto now_time_t = std::chrono::system_clock::to_time_t(now); // 转换为 time_t 类型
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000; // 毫秒部分
    std::tm now_tm = *std::localtime(&now_time_t); // 转换为本地时间
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << now_ms.count(); // 格式化时间字符串
    return oss.str(); // 返回格式化后的时间字符串
}

std::string Logger::getCurrentDate()
{
    auto now = std::chrono::system_clock::now(); // 获取当前时间点
    auto now_time_t = std::chrono::system_clock::to_time_t(now); // 转换为 time_t 类型
    std::tm now_tm = *std::localtime(&now_time_t); // 转换为本地时间
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d"); // 格式化日期字符串
    return oss.str(); // 返回格式化后的日期字符串
}

std::string Logger::levelToString(Level level)
{
    // 将日志级别枚举转换为对应的字符串表示
    switch (level)
    {
    case Level::INFO:
        return "INFO";
    case Level::WARNING:
        return "WARNING";
    case Level::ERROR:
        return "ERROR";
    case Level::DEBUG:
        return "DEBUG";
    case Level::CRITICAL:
        return "CRITICAL";
    case Level::TRACE:
        return "TRACE";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::getColor(Level level)
{
    // 根据日志级别返回对应的 ANSI 控制台颜色代码
    switch (level)
    {
    case Level::INFO:
        return "\033[32m"; // 绿色
    case Level::WARNING:
        return "\033[33m"; // 黄色
    case Level::ERROR:
        return "\033[31m"; // 红色
    case Level::DEBUG:
        return "\033[34m"; // 蓝色
    case Level::CRITICAL:
        return "\033[35m"; // 紫色
    case Level::TRACE:
        return "\033[36m"; // 青色
    default:
        return def_col; // 默认颜色
    }
}

void Logger::asyncLog()
{
    try
    {
        while (running) // 当日志系统处于运行状态时循环
        {
            std::function<void()> task;
            {
                // 使用 std::unique_lock 锁定互斥量 log_mutex
                std::unique_lock<std::mutex> lock(log_mutex);

                // 等待条件变量 log_cv 直到日志队列 log_queue 非空或日志系统不再运行
                log_cv.wait(lock, [this] { return !log_queue.empty() || !running; });

                // 如果日志系统不再运行并且日志队列为空，退出循环
                if (!running && log_queue.empty())
                    break;

                // 从日志队列中取出任务
                task = std::move(log_queue.front());
                log_queue.pop();
            }

            // 如果取出的任务不为空
            if (task)
            {
                // 使用 std::lock_guard 锁定互斥量 log_mutex 直到任务完成
                std::lock_guard<std::mutex> guard(log_mutex);
                task();

                // 如果日志文件是打开状态，则刷新日志文件
                if (log_file.is_open())
                {
                    log_file.flush();
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        // 捕获异常并输出错误信息
        std::cerr << "异步日志线程异常: " << e.what() << std::endl;
    }
}



void Logger::checkFileSize()
{
    if (log_file.is_open() && std::filesystem::file_size(constructLogFileName()) >= max_file_size)
    {
        log_file.close(); // 关闭当前日志文件
        openLogFile(); // 打开新的日志文件
    }
}

