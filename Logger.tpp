#ifndef LOGGER_TPP
#define LOGGER_TPP

#include "Logger.h"

// 实现 log 方法模板
template <typename... Args>
void Logger::log(Level level, const char *file, int line, const char *func, const std::string &fmt, Args... args)
{
    // 如果日志级别低于最小日志级别，则直接返回
    if (level < min_log_level)
    {
        return;
    }

    // 获取日志锁，确保日志操作是线程安全的
    std::lock_guard<std::mutex> guard(log_mutex);

    // 检查日期是否发生变化，如果变化则重新打开日志文件
    checkDateChange();
    
    // 检查日志文件大小是否超过最大限制，如果超过则重新打开日志文件
    checkFileSize();

    // 格式化日志消息，包含时间、日志级别、文件名、行号、函数名和用户提供的信息
    std::string log_msg = "[" + getCurrentTime() + "] [" + getColor(level) + levelToString(level) + def_col + "] [" + file + ":" + std::to_string(line) + "] [" + func + "] " + format(fmt, args...);

    // 如果启用了异步日志记录
    if (async_logging)
    {
        // 将日志任务推入日志队列，并通知日志线程处理任务
        log_queue.push([this, log_msg]() {
            std::lock_guard<std::mutex> guard(log_mutex);
            if (log_file.is_open())
            {
                // 将日志消息写入文件
                log_file << log_msg << std::endl;
                log_file.flush();
            }
            // 如果启用了控制台输出，则将日志消息输出到控制台
            if (log_to_console)
            {
                std::cout << log_msg << std::endl;
            }
        });
        log_cv.notify_one(); // 通知日志线程
    }
    else
    {
        // 直接将日志消息写入文件
        if (log_file.is_open())
        {
            log_file << log_msg << std::endl;
            log_file.flush();
        }
        // 如果启用了控制台输出，则将日志消息输出到控制台
        if (log_to_console)
        {
            std::cout << log_msg << std::endl;
        }
    }
}

// 实现 formatImpl 方法模板（单个参数版本）
template <typename T>
void Logger::formatImpl(std::ostringstream &oss, T &&arg)
{
    oss << std::forward<T>(arg); // 将参数写入 ostringstream 流中
}

// 实现 formatImpl 方法模板（多个参数版本）
template <typename T, typename... Args>
void Logger::formatImpl(std::ostringstream &oss, T &&arg, Args &&... args)
{
    oss << std::forward<T>(arg); // 将参数写入 ostringstream 流中
    formatImpl(oss, std::forward<Args>(args)...); // 递归调用，处理剩余参数
}

// 实现 format 方法模板
template <typename... Args>
std::string Logger::format(const std::string &fmt, Args &&... args)
{
    // 创建一个字符串输出流，用于格式化字符串
    std::ostringstream oss;

    // 正则表达式，用于匹配占位符 "{}"
    const std::regex pattern(R"(\{\})");

    // 复制传入的格式化字符串
    std::string formatted = fmt;

    // 将传入的不定参数展开并转换为字符串数组
    std::array<std::string, sizeof...(Args)> argArray = { (static_cast<std::ostringstream&>(std::ostringstream() << args).str())... };

    // 依次用参数替换占位符 "{}"
    for (const auto &arg : argArray)
    {
        formatted = std::regex_replace(formatted, pattern, arg, std::regex_constants::format_first_only);
    }

    // 返回替换后的格式化字符串
    return formatted;
}


#endif // LOGGER_TPP
