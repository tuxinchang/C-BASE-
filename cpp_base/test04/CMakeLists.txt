# test04 叶子层CMakeLists.txt
# 类和模板示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test04_class class_example.cpp)
add_executable(base_test04_class_plus class_plus_example.cpp)
add_executable(base_test04_class_pro class_pro_example.cpp)
add_executable(base_test04_class_template class_template_example.cpp)

# 设置输出目录
set_target_properties(
    base_test04_class
    base_test04_class_plus
    base_test04_class_pro
    base_test04_class_template
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)