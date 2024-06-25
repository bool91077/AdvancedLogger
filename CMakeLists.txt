cmake_minimum_required(VERSION 3.16)
# 项目名称和版本
project(AdvancedLogger VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 生成可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 包含当前目录的头文件
include_directories(${CMAKE_SOURCE_DIR})

# 查找当前目录下的所有源文件并将其存储在变量中
file(GLOB SOURCES
    "*.cpp"
)

# 添加可执行文件
add_executable(AdvancedLogger ${SOURCES})

# 线程库（如果需要异步日志记录）
find_package(Threads REQUIRED)
target_link_libraries(AdvancedLogger PRIVATE Threads::Threads)
