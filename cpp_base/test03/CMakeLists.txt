# test03 叶子层CMakeLists.txt
# 函数、指针和结构体示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test03_function_call_plus faunction_call_plus_example.cpp)
add_executable(base_test03_function_call function_call_example.cpp)
add_executable(base_test03_num2d num2d_example.cpp)
add_executable(base_test03_num num_example.cpp)
add_executable(base_test03_pointer pointer_example.cpp)
add_executable(base_test03_struct struct_example.cpp)

# 设置输出目录
set_target_properties(
    base_test03_function_call_plus
    base_test03_function_call
    base_test03_num2d
    base_test03_num
    base_test03_pointer
    base_test03_struct
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)