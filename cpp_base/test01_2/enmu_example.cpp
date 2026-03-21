#include<iostream>
#include<string>
#include "../../cpp_utils/include/utf8_console.hpp"

/**
 * ================= 枚举（Enum）类型 案例演示 =================
 * 
 * 枚举是一种自定义数据类型，用来定义一组具有相同特征的常数集合
 * 优点：
 *   1. 使代码更易读、更易维护
 *   2. 编译器可以进行类型检查
 *   3. 减少魔法数字，提高代码质量
 *   4. 更清晰地表达业务逻辑
 */

// ==================== 枚举定义示例 1：无作用域枚举 ====================
// 这种枚举的值会直接进入外层作用域
enum GameStatus {
    PLAYING = 0,      // 游戏进行中 (值为 0)
    PAUSED = 1,       // 游戏暂停 (值为 1)
    GAME_OVER = 2     // 游戏结束 (值为 2)
};

// ==================== 枚举定义示例 2：有作用域枚举（C++11） ====================
// 使用 enum class 创建有作用域的枚举，避免名称冲突
// 访问方式：PlayerLevel::NOVICE
enum class PlayerLevel {
    NOVICE = 1,       // 新手 (等级1)
    BEGINNER = 2,     // 初级 (等级2)
    INTERMEDIATE = 3, // 中级 (等级3)
    ADVANCED = 4,     // 高级 (等级4)
    EXPERT = 5        // 专家 (等级5)
};

// ==================== 枚举定义示例 3：带自定义值的枚举 ====================
// 可以为枚举值指定具体的数值
enum Color {
    RED = 0xFF0000,      // 红色 (十六进制RGB值)
    GREEN = 0x00FF00,    // 绿色
    BLUE = 0x0000FF,     // 蓝色
    YELLOW = 0xFFFF00,   // 黄色
    BLACK = 0x000000,    // 黑色
    WHITE = 0xFFFFFF     // 白色
};

// ==================== 辅助函数：用于转换枚举为字符串 ====================

/**
 * 将游戏状态枚举转换为对应的中文字符串
 * @param status 游戏状态枚举值
 * @return 对应的状态描述字符串
 */
std::string statusToString(GameStatus status) {
    switch (status) {
        case PLAYING:
            return "游戏进行中";
        case PAUSED:
            return "游戏暂停";
        case GAME_OVER:
            return "游戏结束";
        default:
            return "未知状态";
    }
}

/**
 * 将玩家等级枚举转换为对应的中文字符串
 * @param level 玩家等级枚举值
 * @return 对应的等级描述字符串
 */
std::string levelToString(PlayerLevel level) {
    switch (level) {
        case PlayerLevel::NOVICE:
            return "新手（等级1）";
        case PlayerLevel::BEGINNER:
            return "初级（等级2）";
        case PlayerLevel::INTERMEDIATE:
            return "中级（等级3）";
        case PlayerLevel::ADVANCED:
            return "高级（等级4）";
        case PlayerLevel::EXPERT:
            return "专家（等级5）";
        default:
            return "未知等级";
    }
}

/**
 * 将颜色枚举转换为对应的中文字符串
 * @param color 颜色枚举值
 * @return 对应的颜色名称
 */
std::string colorToString(Color color) {
    switch (color) {
        case RED:
            return "红色";
        case GREEN:
            return "绿色";
        case BLUE:
            return "蓝色";
        case YELLOW:
            return "黄色";
        case BLACK:
            return "黑色";
        case WHITE:
            return "白色";
        default:
            return "未知颜色";
    }
}

// ==================== 玩家结构体 ====================
// 使用枚举作为成员变量来表示玩家的各种属性
struct Player {
    std::string name;        // 玩家名字
    PlayerLevel level;       // 玩家等级（枚举类型）
    Color favoriteColor;     // 最喜爱的颜色（枚举类型）
    GameStatus status;       // 当前游戏状态（枚举类型）
    
    // 构造函数
    Player(std::string n, PlayerLevel l, Color c, GameStatus s)
        : name(n), level(l), favoriteColor(c), status(s) {}
};

// ==================== 主程序 ====================
int main() {
    utf8::init_console_utf8();
    
    std::cout << "═════════════════════════════════════════════" << std::endl;
    std::cout << "          枚举（Enum）类型 - 案例演示" << std::endl;
    std::cout << "═════════════════════════════════════════════" << std::endl << std::endl;
    
    // -------- 演示 1：基本枚举使用 --------
    std::cout << "【演示1：游戏状态枚举】" << std::endl;
    {
        GameStatus currentStatus = PLAYING;
        std::cout << "当前游戏状态值: " << currentStatus << std::endl;
        std::cout << "当前游戏状态: " << statusToString(currentStatus) << std::endl;
        
        currentStatus = PAUSED;
        std::cout << "修改后游戏状态值: " << currentStatus << std::endl;
        std::cout << "修改后游戏状态: " << statusToString(currentStatus) << std::endl;
    }
    std::cout << std::endl;
    
    // -------- 演示 2：有作用域枚举 --------
    std::cout << "【演示2：玩家等级枚举（有作用域）】" << std::endl;
    {
        // 有作用域枚举必须使用 PlayerLevel:: 前缀访问
        PlayerLevel level1 = PlayerLevel::NOVICE;
        PlayerLevel level2 = PlayerLevel::EXPERT;
        
        std::cout << "等级1: " << levelToString(level1) << std::endl;
        std::cout << "等级1的值: " << static_cast<int>(level1) << std::endl;
        std::cout << "等级5: " << levelToString(level2) << std::endl;
        std::cout << "等级5的值: " << static_cast<int>(level2) << std::endl;
    }
    std::cout << std::endl;
    
    // -------- 演示 3：枚举的比较和判断 --------
    std::cout << "【演示3：枚举值的比较】" << std::endl;
    {
        PlayerLevel myLevel = PlayerLevel::INTERMEDIATE;
        PlayerLevel maxLevel = PlayerLevel::EXPERT;
        
        if (myLevel < maxLevel) {
            std::cout << "你的等级低于专家等级，还需要继续努力！" << std::endl;
        }
        
        if (myLevel == PlayerLevel::INTERMEDIATE) {
            std::cout << "你当前是中级玩家。" << std::endl;
        }
    }
    std::cout << std::endl;
    
    // -------- 演示 4：带自定义值的枚举 --------
    std::cout << "【演示4：颜色枚举（自定义值）】" << std::endl;
    {
        Color myColor = RED;
        std::cout << "选择的颜色: " << colorToString(myColor) << std::endl;
        std::cout << "颜色的RGB值: 0x" << std::hex << myColor << std::dec << std::endl;
        
        myColor = BLUE;
        std::cout << "修改后的颜色: " << colorToString(myColor) << std::endl;
        std::cout << "颜色的RGB值: 0x" << std::hex << myColor << std::dec << std::endl;
    }
    std::cout << std::endl;
    
    // -------- 演示 5：在结构体中使用枚举 --------
    std::cout << "【演示5：在结构体中使用枚举】" << std::endl;
    {
        // 创建玩家对象
        Player player1("张三", PlayerLevel::BEGINNER, GREEN, PLAYING);
        Player player2("李四", PlayerLevel::ADVANCED, BLUE, PAUSED);
        
        std::cout << "玩家1信息:" << std::endl;
        std::cout << "  名字: " << player1.name << std::endl;
        std::cout << "  等级: " << levelToString(player1.level) << std::endl;
        std::cout << "  最喜爱颜色: " << colorToString(player1.favoriteColor) << std::endl;
        std::cout << "  游戏状态: " << statusToString(player1.status) << std::endl;
        std::cout << std::endl;
        
        std::cout << "玩家2信息:" << std::endl;
        std::cout << "  名字: " << player2.name << std::endl;
        std::cout << "  等级: " << levelToString(player2.level) << std::endl;
        std::cout << "  最喜爱颜色: " << colorToString(player2.favoriteColor) << std::endl;
        std::cout << "  游戏状态: " << statusToString(player2.status) << std::endl;
    }
    std::cout << std::endl;
    
    // -------- 演示 6：枚举的遍历 --------
    std::cout << "【演示6：枚举值遍历（等级示例）】" << std::endl;
    {
        std::cout << "所有等级列表:" << std::endl;
        // 注意：遍历需要手动指定范围，因为枚举没有内置的迭代器
        PlayerLevel levels[] = {
            PlayerLevel::NOVICE,
            PlayerLevel::BEGINNER,
            PlayerLevel::INTERMEDIATE,
            PlayerLevel::ADVANCED,
            PlayerLevel::EXPERT
        };
        
        for (int i = 0; i < 5; i++) {
            std::cout << "  " << (i+1) << ". " << levelToString(levels[i]) << std::endl;
        }
    }
    std::cout << std::endl;
    
    // -------- 演示 7：使用enum进行输入处理 --------
    std::cout << "【演示7：交互式枚举选择示例】" << std::endl;
    {
        std::cout << "请选择颜色（输入数字）：" << std::endl;
        std::cout << "1 - 红色(RED)" << std::endl;
        std::cout << "2 - 绿色(GREEN)" << std::endl;
        std::cout << "3 - 蓝色(BLUE)" << std::endl;
        std::cout << "请输入选择: ";
        
        std::string input = utf8::read_word();
        int choice = 0;
        try {
            choice = std::stoi(input);
        } catch (...) {
            choice = 0;
        }
        
        Color selectedColor;
        switch (choice) {
            case 1:
                selectedColor = RED;
                break;
            case 2:
                selectedColor = GREEN;
                break;
            case 3:
                selectedColor = BLUE;
                break;
            default:
                std::cout << "无效的选择！默认选择红色。" << std::endl;
                selectedColor = RED;
                break;
        }
        
        std::cout << "你选择了: " << colorToString(selectedColor) << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "═════════════════════════════════════════════" << std::endl;
    std::cout << "           案例演示完成！" << std::endl;
    std::cout << "═════════════════════════════════════════════" << std::endl;
    
    return 0;
}