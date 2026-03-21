#include <mysql/mysql.h>
#include <iostream>
#include <string>

int main() {
    // 1. 初始化连接句柄
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "MySQL 初始化失败" << std::endl;
        return 1;
    }

    // 2. 连接到主机数据库 (使用你之前的配置)
    // 参数：句柄, 主机IP, 用户名, 密码, 数据库名, 端口, socket, 标志
    if (!mysql_real_connect(conn, "192.168.152.1", "ubuntu_txc", "303148Tu@", 
                            "ubuntu_test", 3306, nullptr, 0)) {
        std::cerr << "连接错误: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 3. 准备实验数据 (模拟 LaS-CDE 算法在 hopper 环境的数据)
    std::string algo = "LaS-CDE";
    std::string env = "hopper-medium-v2";
    double score = 54.2;
    std::string notes = "Updated density estimation logic";

    // 4. 构建 SQL 语句
    std::string query = "INSERT INTO experiments_log (algo_name, env_name, normalized_score, notes) VALUES ('" 
                        + algo + "', '" + env + "', " + std::to_string(score) + ", '" + notes + "')";

    // 5. 执行插入
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "插入失败: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "🎉 实验数据已成功同步至主机 MySQL！" << std::endl;
    }

    // 6. 关闭连接
    mysql_close(conn);
    return 0;
}