#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <iomanip>

// 显示删除操作的详细信息
void displayDeleteInfo(int record_id, const std::string& algo_name, const std::string& env_name, double score) {
    std::cout << "🗑️  删除记录 #" << record_id << std::endl;
    std::cout << "   算法: " << algo_name << std::endl;
    std::cout << "   环境: " << env_name << std::endl;
    std::cout << "   分数: " << std::fixed << std::setprecision(2) << score << std::endl;
    std::cout << std::endl;
}

// 获取用户确认
bool getUserConfirmation(const std::string& message) {
    std::cout << message << " (y/n): ";
    std::string input;
    std::getline(std::cin, input);
    
    return (input == "y" || input == "Y" || input == "yes" || input == "YES");
}

// 删除分数低于特定阈值的记录
int deleteLowScoreRecords(MYSQL* conn, double score_threshold) {
    std::cout << "\n🔍 查找分数低于 " << score_threshold << " 的记录..." << std::endl;
    
    // 先查询要删除的记录
    std::string select_query = 
        "SELECT id, algo_name, env_name, normalized_score, notes "
        "FROM experiments_log "
        "WHERE normalized_score < " + std::to_string(score_threshold) + " "
        "ORDER BY normalized_score ASC";
    
    if (mysql_query(conn, select_query.c_str())) {
        std::cerr << "❌ 查询失败: " << mysql_error(conn) << std::endl;
        return 0;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "❌ 获取结果失败: " << mysql_error(conn) << std::endl;
        return 0;
    }
    
    int num_rows = mysql_num_rows(result);
    
    if (num_rows == 0) {
        std::cout << "✅ 没有找到分数低于 " << score_threshold << " 的记录" << std::endl;
        mysql_free_result(result);
        return 0;
    }
    
    std::cout << "⚠️  找到 " << num_rows << " 条分数低于 " << score_threshold << " 的记录" << std::endl;
    
    // 显示要删除的记录
    std::cout << "\n📋 将要删除的记录:" << std::endl;
    std::cout << "==================" << std::endl;
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int record_id = row[0] ? std::stoi(row[0]) : 0;
        std::string algo_name = row[1] ? row[1] : "N/A";
        std::string env_name = row[2] ? row[2] : "N/A";
        double score = row[3] ? std::stod(row[3]) : 0.0;
        std::string notes = row[4] ? row[4] : "N/A";
        
        std::cout << "ID: " << record_id << " | " << algo_name << " | " << env_name 
                  << " | 分数: " << std::fixed << std::setprecision(2) << score << std::endl;
        if (notes.length() > 50) {
            std::cout << "备注: " << notes.substr(0, 50) << "..." << std::endl;
        } else {
            std::cout << "备注: " << notes << std::endl;
        }
        std::cout << std::endl;
    }
    
    mysql_free_result(result);
    
    // 获取用户确认
    if (!getUserConfirmation("确认删除以上记录")) {
        std::cout << "❌ 删除操作已取消" << std::endl;
        return 0;
    }
    
    // 执行删除操作
    std::string delete_query = 
        "DELETE FROM experiments_log "
        "WHERE normalized_score < " + std::to_string(score_threshold);
    
    if (mysql_query(conn, delete_query.c_str())) {
        std::cerr << "❌ 删除失败: " << mysql_error(conn) << std::endl;
        return 0;
    }
    
    int affected_rows = mysql_affected_rows(conn);
    std::cout << "✅ 成功删除 " << affected_rows << " 条记录" << std::endl;
    
    return affected_rows;
}

// 删除特定算法的所有记录
int deleteAlgorithmRecords(MYSQL* conn, const std::string& algorithm) {
    std::cout << "\n🔍 查找 " << algorithm << " 算法的所有记录..." << std::endl;
    
    // 先查询要删除的记录
    std::string select_query = 
        "SELECT id, algo_name, env_name, normalized_score "
        "FROM experiments_log "
        "WHERE algo_name = '" + algorithm + "' "
        "ORDER BY env_name, normalized_score DESC";
    
    if (mysql_query(conn, select_query.c_str())) {
        std::cerr << "❌ 查询失败: " << mysql_error(conn) << std::endl;
        return 0;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "❌ 获取结果失败: " << mysql_error(conn) << std::endl;
        return 0;
    }
    
    int num_rows = mysql_num_rows(result);
    
    if (num_rows == 0) {
        std::cout << "✅ 没有找到 " << algorithm << " 算法的记录" << std::endl;
        mysql_free_result(result);
        return 0;
    }
    
    std::cout << "⚠️  找到 " << num_rows << " 条 " << algorithm << " 算法的记录" << std::endl;
    
    // 显示要删除的记录统计
    std::cout << "\n📊 " << algorithm << " 算法记录统计:" << std::endl;
    std::cout << "==================" << std::endl;
    
    MYSQL_ROW row;
    int display_count = 0;
    while ((row = mysql_fetch_row(result)) && display_count < 5) {
        int record_id = row[0] ? std::stoi(row[0]) : 0;
        std::string algo_name = row[1] ? row[1] : "N/A";
        std::string env_name = row[2] ? row[2] : "N/A";
        double score = row[3] ? std::stod(row[3]) : 0.0;
        
        std::cout << "ID: " << record_id << " | " << env_name 
                  << " | 分数: " << std::fixed << std::setprecision(2) << score << std::endl;
        display_count++;
    }
    
    if (num_rows > 5) {
        std::cout << "... 还有 " << (num_rows - 5) << " 条记录" << std::endl;
    }
    
    mysql_free_result(result);
    
    // 获取用户确认
    if (!getUserConfirmation("确认删除以上所有 " + algorithm + " 记录")) {
        std::cout << "❌ 删除操作已取消" << std::endl;
        return 0;
    }
    
    // 执行删除操作
    std::string delete_query = 
        "DELETE FROM experiments_log "
        "WHERE algo_name = '" + algorithm + "'";
    
    if (mysql_query(conn, delete_query.c_str())) {
        std::cerr << "❌ 删除失败: " << mysql_error(conn) << std::endl;
        return 0;
    }
    
    int affected_rows = mysql_affected_rows(conn);
    std::cout << "✅ 成功删除 " << affected_rows << " 条 " << algorithm << " 记录" << std::endl;
    
    return affected_rows;
}

int main() {
    std::cout << "===== MySQL 实验数据删除操作 =====" << std::endl;
    std::cout << "⚠️  警告: 删除操作不可逆，请谨慎操作！" << std::endl;
    
    // 1. 初始化连接句柄
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "❌ MySQL 初始化失败" << std::endl;
        return 1;
    }

    // 2. 连接到主机数据库
    if (!mysql_real_connect(conn, "192.168.152.1", "ubuntu_txc", "303148Tu@", 
                            "ubuntu_test", 3306, nullptr, 0)) {
        std::cerr << "❌ 连接错误: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    std::cout << "✅ 成功连接到 MySQL 数据库" << std::endl;
    
    // 3. 显示当前数据统计
    std::cout << "\n📊 当前数据表统计:" << std::endl;
    std::cout << "==================" << std::endl;
    
    std::string count_query = "SELECT COUNT(*) FROM experiments_log";
    if (mysql_query(conn, count_query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row) {
                std::cout << "总记录数: " << row[0] << " 条" << std::endl;
            }
            mysql_free_result(result);
        }
    }
    
    // 算法统计
    std::string algo_stats_query = 
        "SELECT algo_name, COUNT(*) as count, AVG(normalized_score) as avg_score "
        "FROM experiments_log "
        "GROUP BY algo_name "
        "ORDER BY count DESC";
    
    if (mysql_query(conn, algo_stats_query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            std::cout << "\n算法分布:" << std::endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                std::string algo = row[0] ? row[0] : "N/A";
                int count = row[1] ? std::stoi(row[1]) : 0;
                double avg = row[2] ? std::stod(row[2]) : 0.0;
                
                std::cout << "  " << algo << ": " << count << " 条记录，平均分: " 
                          << std::fixed << std::setprecision(2) << avg << std::endl;
            }
            mysql_free_result(result);
        }
    }
    
    // 4. 执行删除操作
    int total_deleted = 0;
    
    // 选项1: 删除低分记录
    std::cout << "\n1️⃣  删除低分记录 (分数 < 40)" << std::endl;
    total_deleted += deleteLowScoreRecords(conn, 40.0);
    
    // 选项2: 删除特定算法记录
    std::cout << "\n2️⃣  删除特定算法记录" << std::endl;
    std::cout << "请输入要删除的算法名称 (例如: DQN, PPO, 或输入'skip'跳过): ";
    std::string algorithm;
    std::getline(std::cin, algorithm);
    
    if (algorithm != "skip" && !algorithm.empty()) {
        total_deleted += deleteAlgorithmRecords(conn, algorithm);
    }
    
    // 5. 显示最终统计
    std::cout << "\n===== 删除操作结果统计 =====" << std::endl;
    std::cout << "🗑️  总共删除: " << total_deleted << " 条记录" << std::endl;
    
    // 验证删除后的数据
    std::cout << "\n🔍 验证删除结果..." << std::endl;
    
    std::string final_count_query = "SELECT COUNT(*) FROM experiments_log";
    if (mysql_query(conn, final_count_query.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row) {
                std::cout << "📊 删除后总记录数: " << row[0] << " 条" << std::endl;
            }
            mysql_free_result(result);
        }
    }
    
    // 6. 关闭连接
    mysql_close(conn);
    
    std::cout << "\n🎉 MySQL 数据删除操作完成！" << std::endl;
    return 0;
}