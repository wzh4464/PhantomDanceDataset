cmake_minimum_required(VERSION 3.0)
project(PrintBone)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 包含 FBX SDK 头文件
include_directories(/usr/fbxsdk/include)

# 添加库文件的搜索路径
link_directories(/usr/fbxsdk/lib)

# 指定可执行文件输出目录为上级目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

# 指定要编译的源文件和生成的可执行文件
add_executable(printBone printBone.cpp)

# 链接 FBX SDK 和其他所需库
target_link_libraries(printBone fbxsdk xml2 z dl)