# test01 叶子层CMakeLists.txt
# 设计模式练习 - 为每个模式创建独立的可执行文件

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 为每个设计模式创建独立的可执行文件
add_executable(chain_pattern chain.cpp)
add_executable(mediator_pattern mediator.cpp)
add_executable(policy_pattern policy.cpp)
add_executable(prototype_pattern prototype.cpp)

# 设置输出目录（可选）
set_target_properties(chain_pattern mediator_pattern policy_pattern prototype_pattern
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
