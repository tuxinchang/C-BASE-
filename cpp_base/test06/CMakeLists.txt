# test06 叶子层CMakeLists.txt
# 模板编程示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test06_template template_example.cpp)
add_executable(base_test06_template_plus template_plus_example.cpp)
add_executable(base_test06_template_pro template_pro_example.cpp)

# 设置输出目录
set_target_properties(
    base_test06_template
    base_test06_template_plus
    base_test06_template_pro
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)