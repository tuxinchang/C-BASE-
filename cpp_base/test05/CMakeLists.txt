# test05 叶子层CMakeLists.txt
# 文件操作示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test05_file_example file_example.cpp)
add_executable(base_test05_file_test file_test.cpp)

# 设置输出目录
set_target_properties(
    base_test05_file_example
    base_test05_file_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)