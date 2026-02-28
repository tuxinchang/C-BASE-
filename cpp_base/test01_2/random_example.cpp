#include <iostream>
#include <cstdlib>  // rand() 和 srand() 函数
#include <ctime>    // time() 函数，用于生成随机种子
#include <random>   // C++11 随机数库

using namespace std;

int main() {
    // 嵌套 for 循环实现九九乘法表
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << "*" << i << "=" << i * j << "\t";
        }
        cout << endl;
    }
     
    cout << "\n========== 随机数生成演示 ==========" << endl << endl;
    
    // 方法1：使用 srand() 和 rand()（传统方法）
    cout << "【方法1】使用 srand() 和 rand()：" << endl;
    srand(time(0));  // 使用当前时间作为随机种子，确保每次运行结果不同
    
    cout << "生成 5 个整型随机数 (0-100)：";
    for (int i = 0; i < 5; i++) {
        int randInt = rand() % 101;  // 生成 0-100 之间的随机整数
        cout << randInt << " ";
    }
    cout << endl;
    
    cout << "生成 5 个浮点型随机数 (0.0-1.0)：";
    for (int i = 0; i < 5; i++) {
        double randDouble = rand() / (double)RAND_MAX;  // 生成 0.0-1.0 之间的随机浮点数
        cout << randDouble << " ";
    }
    cout << endl << endl;
    
    // 方法2：使用 <random> 库（推荐方法，C++11及以上）
    cout << "【方法2】使用 <random> 库（推荐）：" << endl;
    
    // 创建随机数引擎和分布
    mt19937 gen(time(0));  // mt19937 是高质量的随机数生成器，seed 参数为随机种子
    
    // 整数分布：在 1-100 之间生成随机整数
    uniform_int_distribution<int> intDist(1, 100);
    cout << "生成 5 个整型随机数 (1-100)：";
    for (int i = 0; i < 5; i++) {
        cout << intDist(gen) << " ";
    }
    cout << endl;
    
    // 浮点数分布：在 0.0-1.0 之间生成随机浮点数
    uniform_real_distribution<double> doubleDist(0.0, 1.0);
    cout << "生成 5 个浮点型随机数 (0.0-1.0)：";
    for (int i = 0; i < 5; i++) {
        cout << doubleDist(gen) << " ";
    }
    cout << endl;
    
    return 0;
}
