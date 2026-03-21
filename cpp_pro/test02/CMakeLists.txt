# test02 叶子层CMakeLists.txt
# MySQL连接练习 - 创建数据库连接示例程序

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找MySQL开发库
find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED mysqlclient)

# 添加MySQL连接示例程序
add_executable(mysql_connect mysql_connect.cpp)

# 链接MySQL库
target_link_libraries(mysql_connect ${MYSQL_LIBRARIES})
target_include_directories(mysql_connect PRIVATE ${MYSQL_INCLUDE_DIRS})
target_compile_options(mysql_connect PRIVATE ${MYSQL_CFLAGS_OTHER})

# 设置输出目录
set_target_properties(mysql_connect
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
