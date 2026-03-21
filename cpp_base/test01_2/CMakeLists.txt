# test01_2 叶子层CMakeLists.txt
# 基础语法和输入输出示例

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置包含路径
include_directories(${CMAKE_SOURCE_DIR}/cpp_utils/include)

# 为每个cpp文件创建独立的可执行文件
add_executable(base_test01_2_enmu enmu_example.cpp)
add_executable(base_test01_2_example01 example01.cpp)
add_executable(base_test01_2_example02 example02.cpp)
add_executable(base_test01_2_example04 example04.cpp)
add_executable(base_test01_2_example06 example06.cpp)
add_executable(base_test01_2_goto goto_example.cpp)
add_executable(base_test01_2_input input_example.cpp)
add_executable(base_test01_2_random random_example.cpp)

# 设置输出目录
set_target_properties(
    base_test01_2_enmu 
    base_test01_2_example01 
    base_test01_2_example02 
    base_test01_2_example04 
    base_test01_2_example06 
    base_test01_2_goto 
    base_test01_2_input 
    base_test01_2_random
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)