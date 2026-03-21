#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

class Worker {
public:
    Worker(const std::string& name)
        : name_(name) {}

    void do_work(int times) {
        for (int i = 1; i <= times; ++i) {
            std::cout << "Worker [" << name_
                      << "] working... step "
                      << i << std::endl;

            std::this_thread::sleep_for(
                std::chrono::milliseconds(5000));
        }
        std::cout << "Worker [" << name_
                  << "] finished." << std::endl;
    }

private:
    std::string name_;
};

int main() {
    // 创建智能指针
    std::shared_ptr<Worker> worker =
        std::make_shared<Worker>("Alpha");

    // 将成员函数作为线程入口,如果是私有成员函数，可以把线程函数声明为友元函数调用其私有成员函数
    std::thread t(&Worker::do_work,
                  worker,   // 智能指针
                  5);       // 参数

    t.join();

    return 0;
}