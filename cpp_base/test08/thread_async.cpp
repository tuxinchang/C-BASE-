#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int work(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return x * 2;
}

int main() {
    // 强制新线程执行（避免 deferred 延迟执行）
    std::future<int> fut = std::async(std::launch::async, work, 21);

    std::cout << "main doing other things...\n";

    int ans = fut.get(); // 等待并拿结果
    std::cout << "ans = " << ans << "\n";
    return 0;
}