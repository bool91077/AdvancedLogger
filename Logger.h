#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <string>
#include <filesystem>
#include <queue>
#include <functional>
#include <thread>
#include <condition_variable>
#include <regex>

#define LOG_INFO(...) Logger::getInstance().log(Logger::Level::INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_WARN(...) Logger::getInstance().log(Logger::Level::WARNING, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance().log(Logger::Level::ERROR, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::getInstance().log(Logger::Level::DEBUG, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_CRITICAL(...) Logger::getInstance().log(Logger::Level::CRITICAL, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_TRACE(...) Logger::getInstance().log(Logger::Level::TRACE, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

// 日志记录器类，提供灵活的日志功能
class Logger
{
public:
    // 日志级别枚举
    enum class Level
    {
        INFO,     // 信息消息
        WARNING,  // 警告
        ERROR,    // 错误
        DEBUG,    // 调试信息
        CRITICAL, // 严重错误
        TRACE     // 追踪信息（最详细）
    };

    // 获取单例实例的静态方法
    static Logger &getInstance();

    // 配置日志记录器的方法
    void configure(const std::string &logFileNamePrefix,
                   bool consoleOutput = true,
                   std::size_t maxFileSize = 10 * 1024 * 1024,
                   bool async = false,
                   Level minLogLevel = Level::INFO);

    // 记录日志的模板方法，支持不定参数
    template <typename... Args>
    void log(Level level, const char *file, int line, const char *func, const std::string &fmt, Args... args);

private:
    // 单例模式的私有构造函数
    Logger();

    // 私有析构函数，用于资源清理
    ~Logger();

    // 禁止复制构造函数和赋值运算符
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    // 日志文件流
    std::ofstream log_file;

    // 日志文件名前缀
    std::string log_file_name_prefix;

    // 是否将日志输出到控制台
    bool log_to_console = true;

    // 是否异步记录日志
    bool async_logging = false;

    // 互斥锁，用于同步日志资源访问
    std::mutex log_mutex;

    // 控制台输出的默认颜色
    const std::string def_col = "\033[0m";

    // 当前日期，用于日志轮换
    std::string current_date;

    // 日志文件最大大小，超过则轮换
    std::size_t max_file_size = 10 * 1024 * 1024;

    // 异步日志记录队列
    std::queue<std::function<void()>> log_queue;

    // 异步日志记录条件变量
    std::condition_variable log_cv;

    // 异步日志记录线程
    std::thread log_thread;

    // 日志记录器运行状态标志
    bool running = true;

     // 最小日志级别
    Level min_log_level = Level::INFO; // 添加 min_log_level 成员变量

    // 打开日志文件的方法
    void openLogFile();

    // 检查日期变化，用于日志轮换
    void checkDateChange();

    // 获取当前时间的格式化字符串
    std::string getCurrentTime();

    // 获取当前日期的格式化字符串
    std::string getCurrentDate();

    // 将日志级别转换为字符串表示
    std::string levelToString(Level level);

    // 获取日志级别的 ANSI 颜色代码（用于控制台输出）
    std::string getColor(Level level);

    // 异步日志记录的处理函数
    void asyncLog();

    // 检查日志文件大小，超过最大大小则轮换
    void checkFileSize();

    // 获取Log文件名
    std::string constructLogFileName() const;  

    // 模板方法，用于格式化日志消息参数
    template <typename T>
    void formatImpl(std::ostringstream &oss, T &&arg);

    // 递归模板方法，用于格式化多个参数
    template <typename T, typename... Args>
    void formatImpl(std::ostringstream &oss, T &&arg, Args &&... args);

    // 将不定参数格式化为字符串
    template <typename... Args>
    std::string format(const std::string &fmt, Args &&... args);
};

// 包含日志记录器的模板实现文件
#include "Logger.tpp"

#endif // LOGGER_H
