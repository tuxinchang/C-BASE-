# test02 叶子层CMakeLists.txt
# MySQL连接练习 - 创建数据库连接示例程序

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找MySQL开发库
find_package(PkgConfig REQUIRED)
pkg_check_modules(MYSQL REQUIRED mysqlclient)

# 添加MySQL连接示例程序
add_executable(test02_mysql_connect mysql_connect.cpp)
add_executable(test02_mysql_insert mysql_insert.cpp)
add_executable(test02_mysql_select mysql_select.cpp)
add_executable(test02_mysql_edit mysql_edit.cpp)
add_executable(test02_mysql_delete mysql_delete.cpp)

# 链接MySQL库
target_link_libraries(test02_mysql_connect ${MYSQL_LIBRARIES})
target_link_libraries(test02_mysql_insert ${MYSQL_LIBRARIES})
target_link_libraries(test02_mysql_select ${MYSQL_LIBRARIES})
target_link_libraries(test02_mysql_edit ${MYSQL_LIBRARIES})
target_link_libraries(test02_mysql_delete ${MYSQL_LIBRARIES})
target_include_directories(test02_mysql_connect PRIVATE ${MYSQL_INCLUDE_DIRS})
target_include_directories(test02_mysql_insert PRIVATE ${MYSQL_INCLUDE_DIRS})
target_include_directories(test02_mysql_select PRIVATE ${MYSQL_INCLUDE_DIRS})
target_include_directories(test02_mysql_edit PRIVATE ${MYSQL_INCLUDE_DIRS})
target_include_directories(test02_mysql_delete PRIVATE ${MYSQL_INCLUDE_DIRS})
target_compile_options(test02_mysql_connect PRIVATE ${MYSQL_CFLAGS_OTHER})
target_compile_options(test02_mysql_insert PRIVATE ${MYSQL_CFLAGS_OTHER})
target_compile_options(test02_mysql_select PRIVATE ${MYSQL_CFLAGS_OTHER})
target_compile_options(test02_mysql_edit PRIVATE ${MYSQL_CFLAGS_OTHER})
target_compile_options(test02_mysql_delete PRIVATE ${MYSQL_CFLAGS_OTHER})

# 设置输出目录
set_target_properties(test02_mysql_connect test02_mysql_insert test02_mysql_select test02_mysql_edit test02_mysql_delete
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)