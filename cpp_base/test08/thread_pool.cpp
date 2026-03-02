#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

// 线程池类
class ThreadPool {
    
private:
    std::vector<std::thread> workers;      // 工作线程集合
    std::queue<std::function<void()>> tasks; // 任务队列

    std::mutex mtx;                        // 保护任务队列
    std::condition_variable cv;            // 线程等待机制
    bool stop;                             // 是否停止

public:

    // 构造函数：创建指定数量的工作线程
    ThreadPool(size_t threadCount) : stop(false) {

        // 创建 threadCount 个线程
        for (size_t i = 0; i < threadCount; ++i) {

            // 向 workers 容器中“就地构造”一个线程
            workers.emplace_back([this] {

                // 每个线程都会执行这个无限循环
                while (true) {

                    std::function<void()> task; // 用来存放取出的任务

                    {
                        // 加锁（必须用 unique_lock，因为 wait 需要）
                        std::unique_lock<std::mutex> lock(mtx);

                        // 等待条件成立
                        cv.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });

                        // 如果线程池被要求停止，并且没有任务了
                        if (stop && tasks.empty())
                            return;  // 线程退出

                        // 从任务队列取出一个任务
                        task = std::move(tasks.front());
                        tasks.pop();
                    } // 离开作用域自动解锁

                    // 执行任务（在锁外执行！）
                    task();
                }
            });
        }
    }

    // 添加任务到队列
    void enqueue(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mtx); // 加锁
            tasks.push(std::move(task));           // 放入队列
        } // 自动解锁

        cv.notify_one(); // 通知一个线程有新任务
    }

    // 析构函数：安全关闭线程池
    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true; // 设置停止标志
        }

        cv.notify_all(); // 唤醒所有线程

        // 等待所有线程结束
        for (std::thread& t : workers)
            t.join();
    }

};

int main() {
    ThreadPool pool(3);  // 3个线程
    //加入十个任务
    for (int i = 1; i <= 10; ++i) {
        pool.enqueue([i] {
            std::cout << "任务 " << i
                      << " 在线程 "
                      << std::this_thread::get_id()
                      << " 执行\n";
        });
    }

    return 0;
}