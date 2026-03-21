# test07 叶子层CMakeLists.txt
# STL容器和算法示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test07_dequeue dequeue_example.cpp)
add_executable(base_test07_functor functor_example.cpp)
add_executable(base_test07_list list_example.cpp)
add_executable(base_test07_many_functions many_functions_eaxmple.cpp)
add_executable(base_test07_map map_example.cpp)
add_executable(base_test07_multiset multiset_example.cpp)
add_executable(base_test07_pair pair_example.cpp)
add_executable(base_test07_queue queue_example.cpp)
add_executable(base_test07_set set_example.cpp)
add_executable(base_test07_set_plus set_plus_example.cpp)
add_executable(base_test07_stack stack_example.cpp)
add_executable(base_test07_string string_example.cpp)
add_executable(base_test07_vector vector_example.cpp)
add_executable(base_test07_vector_plus vector_plus_example.cpp)

# 设置输出目录
set_target_properties(
    base_test07_dequeue
    base_test07_functor
    base_test07_list
    base_test07_many_functions
    base_test07_map
    base_test07_multiset
    base_test07_pair
    base_test07_queue
    base_test07_set
    base_test07_set_plus
    base_test07_stack
    base_test07_string
    base_test07_vector
    base_test07_vector_plus
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)