#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int main() {
    std::promise<int> prom;           // 生产结果的一方
    std::future<int> fut = prom.get_future(); // 消费结果的一方

    std::thread t([p = std::move(prom)]() mutable {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        p.set_value(999);  // 把结果送出去
    });

    std::cout << "waiting...\n";
    std::cout << "value = " << fut.get() << "\n"; // 等待并获取

    t.join();
    return 0;
}