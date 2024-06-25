这个日志记录器类（Logger）提供了一个灵活且功能丰富的日志记录解决方案，包含了以下主要功能和实现细节：

### 1. **单例模式**
- Logger类使用单例模式来确保全局只有一个日志记录器实例。
  ```cpp
  static Logger &getInstance() {
      static Logger instance;
      return instance;
  }
  ```

### 2. **日志级别**
- 支持多种日志级别：INFO, WARNING, ERROR, DEBUG, CRITICAL, TRACE。
- 通过`min_log_level`变量控制最小记录的日志级别。

### 3. **日志配置**
- 提供`configure`方法来设置日志文件名前缀、是否输出到控制台、最大文件大小、是否异步记录以及最小日志级别。
  ```cpp
  void configure(const std::string &logFileNamePrefix, bool consoleOutput, std::size_t maxFileSize, bool async, Level minLogLevel);
  ```

### 4. **日志记录**
- 使用宏定义简化日志记录操作：
  ```cpp
  #define LOG_INFO(...) Logger::getInstance().log(Logger::Level::INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
  ```
- 日志记录支持格式化字符串和不定参数：
  ```cpp
  template <typename... Args>
  void log(Level level, const char *file, int line, const char *func, const std::string &fmt, Args... args);
  ```

### 5. **异步日志**
- 支持异步日志记录，通过`async_logging`变量控制。
- 使用一个队列和条件变量实现异步日志记录，日志线程在后台处理日志任务：
  ```cpp
  void asyncLog();
  ```

### 6. **文件日志**
- 日志记录支持文件输出，日志文件名包含日期，每天生成一个新日志文件。
- 检查日志文件大小并自动轮换：
  ```cpp
  void checkFileSize();
  ```

### 7. **日期和时间**
- 获取当前时间和日期用于日志记录和文件名：
  ```cpp
  std::string getCurrentTime();
  std::string getCurrentDate();
  ```

### 8. **线程安全**
- 使用互斥锁（`std::mutex`）确保多线程环境下的日志记录操作是线程安全的。

### 9. **格式化**
- 使用模板函数和正则表达式实现日志消息的格式化：
  ```cpp
  template <typename... Args>
  std::string format(const std::string &fmt, Args &&... args);
  ```

### 10. **控制台颜色**
- 不同的日志级别使用不同的颜色在控制台输出：
  ```cpp
  std::string getColor(Level level);
  ```

### 详细实现

#### Logger.h
- 声明了Logger类及其成员函数和变量，包括日志级别、配置方法、日志记录方法等。

#### Logger.tpp
- 实现了Logger类的模板方法，包括`log`方法、`format`方法等。

#### Logger.cpp
- 实现了Logger类的非模板方法和构造函数、析构函数、异步日志线程等。
