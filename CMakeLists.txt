cmake_minimum_required(VERSION 3.31) # 指定最低 CMake 版本
project(SmartRoute VERSION 1.0) # 指定项目名称和版本

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置默认的 CMAKE_BUILD_TYPE 为 Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 添加外部库路径
set(ASIO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/asio/include")
set(CROW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/crow/include")
set(JSON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/nlohmann/include")
set(FKYAML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/fkYAML/include")

# 定义 ASIO_STANDALONE 宏，确保 ASIO 使用独立版配置
add_definitions(-DASIO_STANDALONE)

# 添加可执行文件
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/*.hpp
    src/*.h
)

add_executable(SmartRoute
    ${SRC_FILES}
)

# 为目标设置包含目录
target_include_directories(SmartRoute PRIVATE
    ${ASIO_INCLUDE_DIR}
    ${CROW_INCLUDE_DIR}
    ${JSON_INCLUDE_DIR}
    ${FKYAML_INCLUDE_DIR}
)

target_compile_options(SmartRoute 
    PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/bigobj> 
	$<$<CXX_COMPILER_ID:GNU>:-Wa,-mbig-obj>
)

# 链接 Windows Socket 库
target_link_libraries(SmartRoute PRIVATE ws2_32 mswsock)

# 添加自定义命令
# 将配置文件config.yaml复制到输出目录
add_custom_command(TARGET SmartRoute POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:SmartRoute>/config
)

# 将数据文件json复制到输出目录
add_custom_command(TARGET SmartRoute POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:SmartRoute>/data
)