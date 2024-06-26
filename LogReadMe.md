使用这个优化和丰富功能的Logger类非常简单，主要分为配置和日志记录两个步骤。以下是使用方法的示例：

### 配置Logger

在使用Logger之前，需要进行配置，包括设置日志文件的前缀、是否输出到控制台、最大文件大小和是否启用异步日志记录。

```cpp
int main()
{
    // 配置Logger，设置日志文件前缀为 "app_log"，输出到控制台，最大文件大小为 10MB，启用异步日志记录
    Logger::getInstance().configure("app_log", true, 10 * 1024 * 1024, true);

    // 其他初始化工作...

    // 程序其余部分，开始记录日志
    LOG_INFO("程序启动");
    LOG_WARN("警告：内存使用过高");
    LOG_ERROR("错误：文件读取失败");
    LOG_DEBUG("调试信息：变量 x = {}", 42);
    LOG_CRITICAL("严重错误：程序崩溃");
    LOG_TRACE("跟踪信息");

    // 其他程序逻辑...

    return 0;
}
```

### 日志记录

一旦Logger被配置好，就可以通过使用预定义的宏来记录不同级别的日志。这些宏会自动记录当前的文件名、行号和函数名，以及提供的日志消息。

- **LOG_INFO**: 普通信息日志。
- **LOG_WARN**: 警告信息日志。
- **LOG_ERROR**: 错误信息日志。
- **LOG_DEBUG**: 调试信息日志，支持格式化字符串。
- **LOG_CRITICAL**: 严重错误日志。
- **LOG_TRACE**: 跟踪信息日志。

这些宏使用方式类似于printf风格的格式化输出，支持传入变长参数。

### 注意事项

- **异步日志**: 如果启用了异步日志记录（通过配置参数设置为true），则日志记录会在后台线程中进行，不会阻塞主线程。这对于性能要求较高的应用程序特别有用。
- **配置选项**: 可以根据实际需求调整配置，如关闭控制台输出、调整最大文件大小等，以满足不同的日志记录场景。

通过这种方式，Logger类提供了灵活且高效的日志记录功能，使开发者能够方便地在应用程序中集成和使用。