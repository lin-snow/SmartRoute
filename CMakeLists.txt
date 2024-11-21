cmake_minimum_required(VERSION 3.31) # 指定最低 CMake 版本

project(SmartRoute VERSION 1.0) # 指定项目名称和版本

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(SmartRoute
    src/main.cpp
    src/function/main.h
    src/function/main.hpp
)

