#include <arpa/inet.h>   // sockaddr_in、htons、inet 相关
#include <unistd.h>      // read、write、close
#include <fcntl.h>       // fcntl、O_NONBLOCK
#include <errno.h>       // errno、EAGAIN
#include <cstring>
#include <iostream>

// ⭐ 把 fd 设置为非阻塞
int set_nonblock(int fd) {
    // 先获取当前 flag（非常重要，不能直接覆盖）
    int flags = fcntl(fd, F_GETFL, 0);

    // 在原有 flag 基础上 OR 上 O_NONBLOCK
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    // ① 创建监听 socket（TCP）
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // ⭐ 防止 Address already in use（TIME_WAIT 常见）
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // ② 准备地址结构
    sockaddr_in addr{};
    addr.sin_family = AF_INET;           // IPv4
    addr.sin_port = htons(8080);         // 端口必须转网络序
    addr.sin_addr.s_addr = INADDR_ANY;   // 监听所有网卡

    // ③ 绑定
    bind(listenfd, (sockaddr*)&addr, sizeof(addr));

    // ④ 进入监听状态（此时内核建立 accept 队列）
    listen(listenfd, 5);

    std::cout << "server start...\n";

    // ⚠️ 阻塞 accept（这里只是为了演示 read 非阻塞）
    int connfd = accept(listenfd, nullptr, nullptr);

    // ⭐⭐⭐关键：把连接 fd 设为非阻塞
    set_nonblock(connfd);

    char buf[1024];

    // 主循环
    while (true) {
        // ⭐ 非阻塞 read
        int n = read(connfd, buf, sizeof(buf));

        if (n > 0) {
            // 收到数据
            buf[n] = 0;  // 补 '\0' 方便打印
            std::cout << "recv: " << buf << std::endl;
        } 
        else if (n == 0) {
            // ⭐⭐⭐ 对端优雅关闭（FIN）
            std::cout << "client closed\n";
            break;
        } 
        else {
            // n < 0 出错，需要看 errno
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // ⭐⭐⭐ 非阻塞最重要场景：现在没数据
                std::cout << "no data yet (EAGAIN)\n";

                // 防止 while 死循环打满 CPU（演示用）
                usleep(500000);
                continue;
            } else {
                // 真正错误
                perror("read error");
                break;
            }
        }
    }

    close(connfd);
    close(listenfd);
    return 0;
}