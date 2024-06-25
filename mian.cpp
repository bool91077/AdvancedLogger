#include "Logger.h"

int main()
{
    // 配置Logger，设置日志文件前缀为 "app_log"，输出到控制台，最大文件大小为 10MB，禁用异步日志记录
    Logger::getInstance().configure("app_log", true, 10 * 1024 * 1024, false);

    // 其他初始化工作...

    // 程序其余部分，开始记录日志
    LOG_DEBUG("调试信息：变量 x = {}", 888.36);
    LOG_INFO("信息消息：{} 是 {}", "键", "值");
    LOG_INFO("这是一条信息日志");
    LOG_WARN("这是一条警告日志");
    LOG_ERROR("这是一条错误日志");
    LOG_DEBUG("这是一条调试日志");
    LOG_CRITICAL("这是一条关键日志");
    LOG_TRACE("这是一条跟踪日志");

    // 其他程序逻辑...

    return 0;
}