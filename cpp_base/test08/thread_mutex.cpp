#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

std::mutex mtx;         // 互斥锁

void add(int& counter) {
    for (int i = 0; i < 100000; ++i) {
        //除了lock_guard之外，还可以使用std::unique_lock<std::mutex> lock(mtx);，它提供了更多的功能，如手动锁定和延迟锁（阻塞是会等待一段时间线再报错），以及条件变量的支持
        std::lock_guard<std::mutex> lock(mtx);  // 自动加锁和解锁,出作用域即最内层{}，自动释放锁
        //mtx.lock()
        counter++;                               // 临界区
        //mtx.unlock()
    }
}

int main() {
    int counter = 0;        // 共享数据
    std::thread t1(add, std::ref(counter));  // 传递引用
    std::thread t2(add, std::ref(counter));  // 传递引用

    t1.join();
    t2.join();

    std::cout << "counter = " << counter << std::endl;
    return 0;
}