#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <iomanip>

// 实验数据结构体
struct ExperimentRecord {
    int id;
    std::string algo_name;
    std::string env_name;
    double normalized_score;
    std::string notes;
    std::string created_at;
};

// 显示实验记录的详细信息
void displayExperimentRecord(const ExperimentRecord& record, int index = -1) {
    if (index != -1) {
        std::cout << "📊 记录 #" << index << std::endl;
    }
    std::cout << "   ID: " << record.id << std::endl;
    std::cout << "   算法: " << record.algo_name << std::endl;
    std::cout << "   环境: " << record.env_name << std::endl;
    std::cout << "   分数: " << std::fixed << std::setprecision(2) << record.normalized_score << std::endl;
    std::cout << "   备注: " << record.notes << std::endl;
    std::cout << "   创建时间: " << record.created_at << std::endl;
    std::cout << std::endl;
}

// 统计LaS-CDE在不同环境中的表现
void analyzeLaSCDEPerformance(MYSQL* conn) {
    std::cout << "\n📈 LaS-CDE 算法性能分析" << std::endl;
    std::cout << "========================" << std::endl;
    
    std::string analysis_query = 
        "SELECT env_name, COUNT(*) as count, "
        "AVG(normalized_score) as avg_score, "
        "MAX(normalized_score) as max_score, "
        "MIN(normalized_score) as min_score "
        "FROM experiments_log "
        "WHERE algo_name = 'LaS-CDE' "
        "GROUP BY env_name "
        "ORDER BY avg_score DESC";
    
    if (mysql_query(conn, analysis_query.c_str())) {
        std::cerr << "❌ 分析查询失败: " << mysql_error(conn) << std::endl;
        return;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "❌ 获取分析结果失败: " << mysql_error(conn) << std::endl;
        return;
    }
    
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    
    std::cout << std::left << std::setw(20) << "环境" 
              << std::setw(8) << "记录数" 
              << std::setw(10) << "平均分" 
              << std::setw(10) << "最高分" 
              << std::setw(10) << "最低分" << std::endl;
    std::cout << std::string(58, '-') << std::endl;
    
    while ((row = mysql_fetch_row(result))) {
        std::string env_name = row[0] ? row[0] : "N/A";
        int count = row[1] ? std::stoi(row[1]) : 0;
        double avg_score = row[2] ? std::stod(row[2]) : 0.0;
        double max_score = row[3] ? std::stod(row[3]) : 0.0;
        double min_score = row[4] ? std::stod(row[4]) : 0.0;
        
        std::cout << std::left << std::setw(20) << env_name
                  << std::setw(8) << count
                  << std::fixed << std::setprecision(2)
                  << std::setw(10) << avg_score
                  << std::setw(10) << max_score
                  << std::setw(10) << min_score << std::endl;
    }
    
    mysql_free_result(result);
}

int main() {
    std::cout << "===== MySQL LaS-CDE 实验数据查询 =====" << std::endl;
    
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

    // 3. 查询LaS-CDE的所有记录
    std::cout << "\n🔍 查询所有 LaS-CDE 实验记录..." << std::endl;
    
    std::string select_query = 
        "SELECT id, algo_name, env_name, normalized_score, notes, created_at "
        "FROM experiments_log "
        "WHERE algo_name = 'LaS-CDE' "
        "ORDER BY env_name, normalized_score DESC";
    
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
    } else {
        std::cout << "✅ 找到 " << num_rows << " 条 LaS-CDE 实验记录" << std::endl;
        std::cout << "====================================" << std::endl;
        
        // 显示所有记录
        MYSQL_ROW row;
        int record_count = 0;
        
        while ((row = mysql_fetch_row(result))) {
            ExperimentRecord record;
            record.id = row[0] ? std::stoi(row[0]) : 0;
            record.algo_name = row[1] ? row[1] : "N/A";
            record.env_name = row[2] ? row[2] : "N/A";
            record.normalized_score = row[3] ? std::stod(row[3]) : 0.0;
            record.notes = row[4] ? row[4] : "N/A";
            record.created_at = row[5] ? row[5] : "N/A";
            
            displayExperimentRecord(record, ++record_count);
        }
        
        // 性能分析
        analyzeLaSCDEPerformance(conn);
        
        // 总体统计
        std::cout << "\n📊 LaS-CDE 总体统计" << std::endl;
        std::cout << "==================" << std::endl;
        
        std::string stats_query = 
            "SELECT COUNT(*) as total, "
            "AVG(normalized_score) as overall_avg, "
            "MAX(normalized_score) as overall_max, "
            "MIN(normalized_score) as overall_min "
            "FROM experiments_log "
            "WHERE algo_name = 'LaS-CDE'";
        
        if (mysql_query(conn, stats_query.c_str()) == 0) {
            MYSQL_RES* stats_result = mysql_store_result(conn);
            if (stats_result) {
                MYSQL_ROW stats_row = mysql_fetch_row(stats_result);
                if (stats_row) {
                    int total = stats_row[0] ? std::stoi(stats_row[0]) : 0;
                    double avg = stats_row[1] ? std::stod(stats_row[1]) : 0.0;
                    double max = stats_row[2] ? std::stod(stats_row[2]) : 0.0;
                    double min = stats_row[3] ? std::stod(stats_row[3]) : 0.0;
                    
                    std::cout << "总记录数: " << total << " 条" << std::endl;
                    std::cout << "平均分数: " << std::fixed << std::setprecision(2) << avg << std::endl;
                    std::cout << "最高分数: " << max << std::endl;
                    std::cout << "最低分数: " << min << std::endl;
                }
                mysql_free_result(stats_result);
            }
        }
    }
    
    mysql_free_result(result);
    
    // 4. 与其他算法对比
    std::cout << "\n🔬 LaS-CDE 与其他算法对比" << std::endl;
    std::cout << "==========================" << std::endl;
    
    std::string comparison_query = 
        "SELECT algo_name, COUNT(*) as count, AVG(normalized_score) as avg_score "
        "FROM experiments_log "
        "GROUP BY algo_name "
        "ORDER BY avg_score DESC";
    
    if (mysql_query(conn, comparison_query.c_str()) == 0) {
        MYSQL_RES* comp_result = mysql_store_result(conn);
        if (comp_result) {
            std::cout << std::left << std::setw(15) << "算法" 
                      << std::setw(10) << "记录数" 
                      << std::setw(12) << "平均分数" << std::endl;
            std::cout << std::string(37, '-') << std::endl;
            
            MYSQL_ROW comp_row;
            while ((comp_row = mysql_fetch_row(comp_result))) {
                std::string algo = comp_row[0] ? comp_row[0] : "N/A";
                int count = comp_row[1] ? std::stoi(comp_row[1]) : 0;
                double avg = comp_row[2] ? std::stod(comp_row[2]) : 0.0;
                
                // 高亮显示LaS-CDE
                if (algo == "LaS-CDE") {
                    std::cout << "🌟 " << std::left << std::setw(13) << algo
                              << std::setw(10) << count
                              << std::fixed << std::setprecision(2) 
                              << std::setw(12) << avg << std::endl;
                } else {
                    std::cout << "   " << std::left << std::setw(13) << algo
                              << std::setw(10) << count
                              << std::fixed << std::setprecision(2) 
                              << std::setw(12) << avg << std::endl;
                }
            }
            mysql_free_result(comp_result);
        }
    }
    
    // 5. 关闭连接
    mysql_close(conn);
    
    std::cout << "\n🎉 LaS-CDE 数据查询分析完成！" << std::endl;
    return 0;
}