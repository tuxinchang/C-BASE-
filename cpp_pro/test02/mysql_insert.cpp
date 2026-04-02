#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

// 实验数据生成器
struct ExperimentData {
    std::string algo_name;
    std::string env_name;
    double score;
    std::string notes;
};

// 生成随机分数
double generateRandomScore(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// 生成20条实验数据
std::vector<ExperimentData> generateExperimentData() {
    std::vector<ExperimentData> data;
    
    // 算法列表
    std::vector<std::string> algorithms = {
        "LaS-CDE", "DQN", "PPO", "SAC", "TD3", 
        "A2C", "TRPO", "DDPG", "CQL", "BC"
    };
    
    // 环境列表
    std::vector<std::string> environments = {
        "hopper-medium-v2", "walker2d-medium-v2", "halfcheetah-medium-v2",
        "ant-medium-v2", "humanoid-medium-v2", "kitchen-complete-v0"
    };
    
    // 备注模板
    std::vector<std::string> notes_templates = {
        "Updated density estimation logic",
        "Improved exploration strategy",
        "Fixed reward calculation bug",
        "Optimized neural network architecture",
        "Enhanced data preprocessing pipeline",
        "Added regularization techniques",
        "Improved training stability",
        "Fixed gradient explosion issue",
        "Optimized hyperparameters",
        "Enhanced replay buffer management"
    };
    
    // 生成20条数据
    for (int i = 0; i < 20; ++i) {
        ExperimentData exp;
        
        // 随机选择算法和环境
        exp.algo_name = algorithms[i % algorithms.size()];
        exp.env_name = environments[i % environments.size()];
        
        // 生成随机分数（不同算法和环境有不同的分数范围）
        if (exp.algo_name == "LaS-CDE") {
            exp.score = generateRandomScore(50.0, 80.0);
        } else if (exp.algo_name == "DQN") {
            exp.score = generateRandomScore(40.0, 70.0);
        } else if (exp.algo_name == "PPO") {
            exp.score = generateRandomScore(45.0, 75.0);
        } else if (exp.algo_name == "SAC") {
            exp.score = generateRandomScore(55.0, 85.0);
        } else {
            exp.score = generateRandomScore(35.0, 65.0);
        }
        
        // 随机选择备注
        exp.notes = notes_templates[i % notes_templates.size()] + " - Batch " + std::to_string(i + 1);
        
        data.push_back(exp);
    }
    
    return data;
}

int main() {
    std::cout << "===== MySQL 批量插入实验数据 =====" << std::endl;
    
    // 1. 初始化连接句柄
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "MySQL 初始化失败" << std::endl;
        return 1;
    }

    // 2. 连接到主机数据库
    if (!mysql_real_connect(conn, "192.168.152.1", "ubuntu_txc", "303148Tu@", 
                            "ubuntu_test", 3306, nullptr, 0)) {
        std::cerr << "连接错误: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    std::cout << "✅ 成功连接到 MySQL 数据库" << std::endl;

    // 3. 生成实验数据
    std::vector<ExperimentData> experiments = generateExperimentData();
    std::cout << "📊 生成 " << experiments.size() << " 条实验数据" << std::endl;

    // 4. 批量插入数据
    int success_count = 0;
    int fail_count = 0;
    
    for (size_t i = 0; i < experiments.size(); ++i) {
        const auto& exp = experiments[i];
        
        // 构建 SQL 插入语句
        std::string query = "INSERT INTO experiments_log (algo_name, env_name, normalized_score, notes) VALUES ('" 
                            + exp.algo_name + "', '" + exp.env_name + "', " 
                            + std::to_string(exp.score) + ", '" + exp.notes + "')";

        // 执行插入
        if (mysql_query(conn, query.c_str())) {
            std::cerr << "❌ 插入失败 (第" << i + 1 << "条): " << mysql_error(conn) << std::endl;
            fail_count++;
        } else {
            std::cout << "✅ 成功插入第" << i + 1 << "条数据: " 
                      << exp.algo_name << " - " << exp.env_name 
                      << " (分数: " << exp.score << ")" << std::endl;
            success_count++;
        }
    }

    // 5. 显示插入结果统计
    std::cout << "\n===== 插入结果统计 =====" << std::endl;
    std::cout << "✅ 成功插入: " << success_count << " 条" << std::endl;
    std::cout << "❌ 插入失败: " << fail_count << " 条" << std::endl;
    std::cout << "📈 成功率: " << (success_count * 100.0 / experiments.size()) << "%" << std::endl;

    // 6. 验证插入的数据
    if (success_count > 0) {
        std::cout << "\n🔍 验证插入的数据..." << std::endl;
        
        std::string count_query = "SELECT COUNT(*) FROM experiments_log";
        if (mysql_query(conn, count_query.c_str()) == 0) {
            MYSQL_RES* result = mysql_store_result(conn);
            if (result) {
                MYSQL_ROW row = mysql_fetch_row(result);
                if (row) {
                    std::cout << "📊 当前数据表总记录数: " << row[0] << " 条" << std::endl;
                }
                mysql_free_result(result);
            }
        }
    }

    // 7. 关闭连接
    mysql_close(conn);
    
    std::cout << "\n🎉 MySQL 批量插入操作完成！" << std::endl;
    return 0;
}