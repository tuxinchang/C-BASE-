#include<iostream>
#include<string>
#include<cstdlib>
#include "utf8_console.hpp"

int main() {
    utf8::init_console_utf8();
    
    // 定义一个整数类型的变量（1-10范围的随机数）
    int secret_number = (rand() % 10) + 1;
    int guess_count = 0;
    const int max_guesses = 5;
    
    std::cout << "===== 欢迎来到数字猜谜游戏 =====" << std::endl;
    std::cout << "我已经想好了一个1到10之间的数字，你有" << max_guesses << "次猜测机会。" << std::endl << std::endl;
    
    while (guess_count < max_guesses) {
        std::cout << "请输入你的第" << (guess_count + 1) << "次猜测：";
        std::string input = utf8::read_word();
        
        // 检验输入是否为有效数字
        int guess = 0;
        try {
            guess = std::stoi(input);
        } catch (...) {
            std::cout << "输入无效，请输入一个整数！" << std::endl << std::endl;
            continue;
        }
        
        guess_count++;
        
        if (guess == secret_number) {
            std::cout << "恭喜！你猜对了！答案就是" << secret_number << "！" << std::endl;
            return 0;
        } else if (guess < secret_number) {
            std::cout << "你的猜测太小了，再试试！" << std::endl;
        } else {
            std::cout << "你的猜测太大了，再试试！" << std::endl;
        }
        
        if (guess_count < max_guesses) {
            std::cout << "你还有" << (max_guesses - guess_count) << "次机会。" << std::endl << std::endl;
        }
    }
    
    std::cout << std::endl << "很遗憾，你已经用完了所有猜测机会。答案是：" << secret_number << std::endl;
    return 0;
}