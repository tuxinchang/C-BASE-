# test01 叶子层CMakeLists.txt
# Qt登录界面项目

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt5库
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# 设置自动处理MOC、UIC、RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 添加可执行文件
add_executable(test01_qt_login
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    widget.cpp
    widget.h
    widget_plus.cpp
    widget_plus.h
)

# 链接Qt库
target_link_libraries(test01_qt_login Qt5::Core Qt5::Widgets)

# 设置输出目录
set_target_properties(test01_qt_login
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)