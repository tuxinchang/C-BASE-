#include <iostream>
#include <future>
#include <thread>

int work(int x) {
    return x + 100;
}

int main() {
    // 1) 把函数打包成一个“可执行任务”
    std::packaged_task<int(int)> task(work);

    // 2) 从 task 拿到 future（用来取结果）
    std::future<int> fut = task.get_future();

    // 3) 把 task 交给线程执行（必须 std::move，因为 packaged_task 不可拷贝）
    std::thread t(std::move(task), 23);

    // 4) 等待结果
    std::cout << "result = " << fut.get() << "\n";

    t.join();
    return 0;
}