#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_CLIENT 1024

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
    listen(listenfd, 5);

    // ⭐ 保存所有客户端 fd
    std::vector<int> clients;

    std::cout << "select server start...\n";

    while (true) {
        fd_set readfds;

        // ⭐ 每次都必须清空（select 会修改它）
        FD_ZERO(&readfds);

        // 把监听 fd 加进去
        FD_SET(listenfd, &readfds);

        // ⭐ select 需要知道最大 fd
        int maxfd = listenfd;

        // 把所有客户端 fd 加入监听集合
        for (int fd : clients) {
            FD_SET(fd, &readfds);
            if (fd > maxfd) maxfd = fd;
        }

        // ⭐⭐⭐ 阻塞等待事件
        int nready = select(maxfd + 1, &readfds, nullptr, nullptr, nullptr);

        if (nready < 0) {
            perror("select");
            break;
        }

        // =============================
        // ① 有新连接？
        // =============================
        if (FD_ISSET(listenfd, &readfds)) {
            int connfd = accept(listenfd, nullptr, nullptr);
            clients.push_back(connfd);
            std::cout << "new client: " << connfd << std::endl;
        }

        // =============================
        // ② 处理已有客户端
        // =============================
        for (auto it = clients.begin(); it != clients.end();) {
            int fd = *it;

            // ⭐ 判断这个 fd 是否就绪
            if (FD_ISSET(fd, &readfds)) {
                char buf[1024];
                int n = read(fd, buf, sizeof(buf));

                if (n <= 0) {
                    // 客户端关闭或出错
                    std::cout << "client closed: " << fd << std::endl;
                    close(fd);

                    // ⭐⭐⭐ 必须从容器删除
                    it = clients.erase(it);
                    continue;
                } else {
                    // echo 回去
                    write(fd, buf, n);
                }
            }
            ++it;
        }
    }

    close(listenfd);
}