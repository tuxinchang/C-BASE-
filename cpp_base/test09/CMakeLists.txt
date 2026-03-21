# test09 叶子层CMakeLists.txt
# 网络编程示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找网络库（在Linux上通常不需要额外链接）

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test09_socket_example socket_example.cpp)
add_executable(base_test09_socket_server_epoll socket_server_epoll.cpp)
add_executable(base_test09_socket_server_nonblock socket_server_nonblock.cpp)
add_executable(base_test09_socket_server_select socket_server_select.cpp)

# 设置输出目录
set_target_properties(
    base_test09_socket_example
    base_test09_socket_server_epoll
    base_test09_socket_server_nonblock
    base_test09_socket_server_select
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)