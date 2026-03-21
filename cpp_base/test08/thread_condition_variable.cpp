#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;
//condition_variable是一个同步原语，允许线程等待某个条件的发生。它通常与互斥锁一起使用，
//以保护共享数据并协调线程之间的通信。当一个线程需要等待某个条件时，它会调用wait()方法，
///并传入一个unique_lock对象，该对象会自动释放互斥锁并进入等待状态。当另一个线程满足条件时，
//它会调用notify_one()或notify_all()方法来唤醒等待的线程。被唤醒的线程会重新获取互斥锁，并
//继续执行后续代码。
// 生产者线程
void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "生产: " << i << std::endl;
        }
        cv.notify_one();  // 通知消费者
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_one();  // 最后再通知一次
}

// 消费者线程
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [] {
            return !dataQueue.empty() || finished;
        });

        if (!dataQueue.empty()) {
            int value = dataQueue.front();
            dataQueue.pop();
            std::cout << "消费: " << value << std::endl;
        }
        else if (finished) {
            break;
        }
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}