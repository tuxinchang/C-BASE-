#include <iostream>
#include <thread>
#include <atomic>
//atomic 是“轻量级锁”，只保护单个变量。它提供了一组原子操作，确保在多线程环境下对该变量的访问是安全的。使用 atomic 可以避免使用 mutex 来保护共享数据，从而提高性能和减少死锁的风险。在上面的代码中，counter 是一个 atomic<int> 类型的变量，多个线程可以同时对它进行递增操作，而不需要担心数据竞争问题。
std::atomic<int> counter(0);

void add() {
    for (int i = 0; i < 100000; ++i) {
        counter++;  // 原子操作
    }
}

int main() {
    std::thread t1(add);
    std::thread t2(add);

    t1.join();
    t2.join();

    std::cout << "counter = " << counter << std::endl;
}