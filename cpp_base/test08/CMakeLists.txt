# test08 叶子层CMakeLists.txt
# 多线程编程示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找线程库（现代C++通常不需要额外链接）
find_package(Threads REQUIRED)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test08_thread_async thread_async.cpp)
add_executable(base_test08_thread_atomic thread_atomic.cpp)
add_executable(base_test08_thread_condition_variable thread_condition_variable.cpp)
add_executable(base_test08_thread_example thread_example.cpp)
add_executable(base_test08_thread_mutex thread_mutex.cpp)
add_executable(base_test08_thread_once_flag thread_once_flag.cpp)
add_executable(base_test08_thread_package_task thread_package_task.cpp)
add_executable(base_test08_thread_pool thread_pool.cpp)
add_executable(base_test08_thread_pormise thread_pormise.cpp)
add_executable(base_test08_thread_shared_prt thread_shared_prt.cpp)

# 链接线程库
target_link_libraries(base_test08_thread_async Threads::Threads)
target_link_libraries(base_test08_thread_atomic Threads::Threads)
target_link_libraries(base_test08_thread_condition_variable Threads::Threads)
target_link_libraries(base_test08_thread_example Threads::Threads)
target_link_libraries(base_test08_thread_mutex Threads::Threads)
target_link_libraries(base_test08_thread_once_flag Threads::Threads)
target_link_libraries(base_test08_thread_package_task Threads::Threads)
target_link_libraries(base_test08_thread_pool Threads::Threads)
target_link_libraries(base_test08_thread_pormise Threads::Threads)
target_link_libraries(base_test08_thread_shared_prt Threads::Threads)

# 设置输出目录
set_target_properties(
    base_test08_thread_async
    base_test08_thread_atomic
    base_test08_thread_condition_variable
    base_test08_thread_example
    base_test08_thread_mutex
    base_test08_thread_once_flag
    base_test08_thread_package_task
    base_test08_thread_pool
    base_test08_thread_pormise
    base_test08_thread_shared_prt
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)