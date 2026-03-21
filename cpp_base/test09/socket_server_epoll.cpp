#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <sys/epoll.h>

// ⭐ 设置非阻塞
int set_nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    // ① 创建监听 socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listenfd, (sockaddr*)&addr, sizeof(addr));
    listen(listenfd, 128);

    // ⭐⭐⭐ 必须：监听 fd 也要非阻塞（epoll 标配）
    set_nonblock(listenfd);

    // ================================
    // ⭐ 1. 创建 epoll 实例
    // ================================
    int epfd = epoll_create1(0);

    // 准备事件结构
    epoll_event ev{};
    ev.events = EPOLLIN;     // 关心“可读事件”
    ev.data.fd = listenfd;   // 用户数据：存 fd

    // ================================
    // ⭐ 2. 注册监听 fd
    // ================================
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    std::cout << "epoll server start...\n";

    // ⭐ 就绪事件数组（内核会填充）
    std::vector<epoll_event> events(1024);

    while (true) {
        // ================================
        // ⭐ 3. 等待事件（真正的事件驱动）
        // ================================
        int nready = epoll_wait(epfd, events.data(), events.size(), -1);

        // 遍历所有就绪事件（注意：只遍历就绪的！）
        for (int i = 0; i < nready; ++i) {
            int fd = events[i].data.fd;

            // ============================
            // 新连接到来
            // ============================
            if (fd == listenfd) {
                while (true) {
                    int connfd = accept(listenfd, nullptr, nullptr);

                    // ⭐ 非阻塞 accept 必须判断
                    if (connfd < 0) break;

                    set_nonblock(connfd);

                    epoll_event cev{};
                    cev.events = EPOLLIN;
                    cev.data.fd = connfd;

                    // 注册客户端 fd
                    epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &cev);

                    std::cout << "new client: " << connfd << std::endl;
                }
            }
            // ============================
            // 客户端数据
            // ============================
            else {
                char buf[1024];
                int n = read(fd, buf, sizeof(buf));

                if (n <= 0) {
                    // 客户端关闭
                    std::cout << "client closed: " << fd << std::endl;
                    close(fd);

                    // ⭐⭐⭐ 必须从 epoll 移除
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                } else {
                    // echo
                    write(fd, buf, n);
                }
            }
        }
    }

    close(listenfd);
}