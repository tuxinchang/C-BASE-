#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <iomanip>

// 显示更新操作的详细信息
void displayUpdateInfo(int record_id, const std::string& old_notes, const std::string& new_notes) {
    std::cout << "🔄 更新记录 #" << record_id << std::endl;
    std::cout << "   原备注: " << old_notes << std::endl;
    std::cout << "   新备注: " << new_notes << std::endl;
    std::cout << std::endl;
}

// 检查备注中是否包含seed信息并提取当前seed值
bool extractSeedFromNotes(const std::string& notes, int& current_seed) {
    // 查找"seed"或"Seed"关键词
    size_t seed_pos = notes.find("seed=");
    if (seed_pos == std::string::npos) {
        seed_pos = notes.find("Seed=");
    }
    
    if (seed_pos != std::string::npos) {
        // 提取seed值
        size_t value_start = seed_pos + 5; // "seed=" 后面
        size_t value_end = notes.find_first_not_of("0123456789", value_start);
        
        if (value_end == std::string::npos) {
            value_end = notes.length();
        }
        
        std::string seed_str = notes.substr(value_start, value_end - value_start);
        if (!seed_str.empty()) {
            current_seed = std::stoi(seed_str);
            return true;
        }
    }
    
    return false;
}

// 更新备注中的seed值为2
std::string updateSeedInNotes(const std::string& old_notes, int new_seed = 2) {
    std::string new_notes = old_notes;
    
    // 查找并替换现有的seed值
    size_t seed_pos = new_notes.find("seed=");
    if (seed_pos == std::string::npos) {
        seed_pos = new_notes.find("Seed=");
    }
    
    if (seed_pos != std::string::npos) {
        // 找到现有的seed值位置
        size_t value_start = seed_pos + 5;
        size_t value_end = new_notes.find_first_not_of("0123456789", value_start);
        
        if (value_end == std::string::npos) {
            value_end = new_notes.length();
        }
        
        // 替换seed值
        new_notes.replace(value_start, value_end - value_start, std::to_string(new_seed));
    } else {
        // 如果没有seed信息，在备注末尾添加
        if (!new_notes.empty() && new_notes.back() != ' ') {
            new_notes += " ";
        }
        new_notes += "[seed=" + std::to_string(new_seed) + "]";
    }
    
    return new_notes;
}

int main() {
    std::cout << "===== MySQL LaS-CDE 实验数据更新 =====" << std::endl;
    std::cout << "目标: 将所有 LaS-CDE 算法的 seed 修改为 2" << std::endl;
    
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

    // 3. 查询所有LaS-CDE记录
    std::cout << "\n🔍 查询所有 LaS-CDE 实验记录..." << std::endl;
    
    std::string select_query = 
        "SELECT id, algo_name, env_name, normalized_score, notes "
        "FROM experiments_log "
        "WHERE algo_name = 'LaS-CDE' "
        "ORDER BY id";
    
    if (mysql_query(conn, select_query.c_str())) {
        std::cerr << "❌ 查询失败: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "❌ 获取结果失败: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }
    
    int num_rows = mysql_num_rows(result);
    
    if (num_rows == 0) {
        std::cout << "⚠️  未找到 LaS-CDE 算法的实验记录" << std::endl;
        mysql_free_result(result);
        mysql_close(conn);
        return 0;
    }
    
    std::cout << "✅ 找到 " << num_rows << " 条 LaS-CDE 实验记录" << std::endl;
    
    // 4. 分析并更新记录
    int updated_count = 0;
    int skipped_count = 0;
    int error_count = 0;
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int record_id = row[0] ? std::stoi(row[0]) : 0;
        std::string algo_name = row[1] ? row[1] : "N/A";
        std::string env_name = row[2] ? row[2] : "N/A";
        double score = row[3] ? std::stod(row[3]) : 0.0;
        std::string old_notes = row[4] ? row[4] : "";
        
        // 检查当前seed值
        int current_seed = 0;
        bool has_seed = extractSeedFromNotes(old_notes, current_seed);
        
        // 如果当前seed已经是2，跳过更新
        if (has_seed && current_seed == 2) {
            std::cout << "⏭️  记录 #" << record_id << " 的seed已经是2，跳过更新" << std::endl;
            skipped_count++;
            continue;
        }
        
        // 生成新的备注（seed=2）
        std::string new_notes = updateSeedInNotes(old_notes, 2);
        
        // 构建更新SQL语句
        std::string update_query = 
            "UPDATE experiments_log SET notes = '" + new_notes + "' "
            "WHERE id = " + std::to_string(record_id);
        
        // 执行更新
        if (mysql_query(conn, update_query.c_str())) {
            std::cerr << "❌ 更新记录 #" << record_id << " 失败: " << mysql_error(conn) << std::endl;
            error_count++;
        } else {
            displayUpdateInfo(record_id, old_notes, new_notes);
            updated_count++;
        }
    }
    
    mysql_free_result(result);
    
    // 5. 显示更新结果统计
    std::cout << "\n===== 更新结果统计 =====" << std::endl;
    std::cout << "✅ 成功更新: " << updated_count << " 条记录" << std::endl;
    std::cout << "⏭️  跳过更新: " << skipped_count << " 条记录" << std::endl;
    std::cout << "❌ 更新失败: " << error_count << " 条记录" << std::endl;
    std::cout << "📊 总记录数: " << num_rows << " 条" << std::endl;
    
    // 6. 验证更新结果
    if (updated_count > 0) {
        std::cout << "\n🔍 验证更新结果..." << std::endl;
        
        std::string verify_query = 
            "SELECT id, algo_name, env_name, notes "
            "FROM experiments_log "
            "WHERE algo_name = 'LaS-CDE' AND notes LIKE '%seed=2%' "
            "ORDER BY id";
        
        if (mysql_query(conn, verify_query.c_str()) == 0) {
            MYSQL_RES* verify_result = mysql_store_result(conn);
            if (verify_result) {
                int verified_count = mysql_num_rows(verify_result);
                std::cout << "✅ 验证成功: " << verified_count << " 条记录已更新为seed=2" << std::endl;
                
                // 显示部分更新后的记录
                if (verified_count > 0) {
                    std::cout << "\n📋 更新后的记录示例:" << std::endl;
                    std::cout << "==================" << std::endl;
                    
                    MYSQL_ROW verify_row;
                    int display_count = 0;
                    while ((verify_row = mysql_fetch_row(verify_result)) && display_count < 3) {
                        int id = verify_row[0] ? std::stoi(verify_row[0]) : 0;
                        std::string algo = verify_row[1] ? verify_row[1] : "N/A";
                        std::string env = verify_row[2] ? verify_row[2] : "N/A";
                        std::string notes = verify_row[3] ? verify_row[3] : "N/A";
                        
                        std::cout << "ID: " << id << " | " << algo << " | " << env << std::endl;
                        std::cout << "备注: " << notes << std::endl;
                        std::cout << std::endl;
                        display_count++;
                    }
                }
                mysql_free_result(verify_result);
            }
        }
    }
    
    // 7. 关闭连接
    mysql_close(conn);
    
    std::cout << "\n🎉 LaS-CDE 数据更新操作完成！" << std::endl;
    return 0;
}