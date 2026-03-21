#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    // 1️⃣ 创建 socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2️⃣ 绑定地址
    sockaddr_in addr{};
    addr.sin_family = AF_INET;   // IPv4协议
    addr.sin_port = htons(8080);  // 端口号，使用 htons 转换为网络字节序
    addr.sin_addr.s_addr = INADDR_ANY;// 监听所有接口

    bind(listenfd, (sockaddr*)&addr, sizeof(addr)); // 绑定地址和端口

    // 3️⃣ 监听
    listen(listenfd, 5);

    std::cout << "Server start...\n";

    // 4️⃣ 接受连接
    int connfd = accept(listenfd, nullptr, nullptr);  // 阻塞等待客户端连接

    // 5️⃣ 收发数据
    char buf[1024] = {0};  // 接收客户端发送的数据
    read(connfd, buf, sizeof(buf));  // 从客户端读取数据  真正的阻塞点。为什么要引入epoll的原因
    std::cout << "recv: " << buf << std::endl;

    const char* msg = "hello client";  // 发送数据给客户端
    write(connfd, msg, strlen(msg));   // 向客户端写入数据

    close(connfd);   // 6️⃣ 关闭连接
    close(listenfd);  // 7️⃣ 关闭监听 socket
}