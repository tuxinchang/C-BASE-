# test 叶子层CMakeLists.txt
# 基础测试示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test_example example.cpp)
add_executable(base_test_main main.cpp)

# 设置输出目录
set_target_properties(base_test_example base_test_main
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)