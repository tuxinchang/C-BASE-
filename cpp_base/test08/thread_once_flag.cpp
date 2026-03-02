#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag;   // 标记

void init() {
    std::cout << "初始化函数只执行一次\n";
}

void worker() {
    std::call_once(flag, init);
    std::cout << "线程继续执行\n";
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}