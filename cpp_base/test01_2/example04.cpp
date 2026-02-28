#include<iostream>
#include<string>
#include "utf8_console.hpp"

int main() {
    utf8::init_console_utf8();
    
    std::cout << "===== 星期查询程序 =====" << std::endl;
    std::cout << "请输入一个数字（1-7）来查询对应的星期：" << std::endl;
    std::cout << "1=周一，2=周二，3=周三，4=周四，5=周五，6=周六，7=周日" << std::endl << std::endl;
    
    std::cout << "请输入数字：";
    std::string input = utf8::read_word();
    
    // 检验输入是否为有效数字
    int day = 0;
    try {
        day = std::stoi(input);
    } catch (...) {
        std::cout << "输入无效，请输入一个整数！" << std::endl;
        return 1;
    }
    
    // 使用switch语句输出对应的星期
    std::cout << "结果：";
    switch (day) {
        case 1:
            std::cout << "周一（Monday）" << std::endl;
            break;
        case 2:
            std::cout << "周二（Tuesday）" << std::endl;
            break;
        case 3:
            std::cout << "周三（Wednesday）" << std::endl;
            break;
        case 4:
            std::cout << "周四（Thursday）" << std::endl;
            break;
        case 5:
            std::cout << "周五（Friday）" << std::endl;
            break;
        case 6:
            std::cout << "周六（Saturday）" << std::endl;
            break;
        case 7:
            std::cout << "周日（Sunday）" << std::endl;
            break;
        default:
            std::cout << "输入错误，请输入1-7之间的数字！" << std::endl;
            return 1;
    }
    
    return 0;
}