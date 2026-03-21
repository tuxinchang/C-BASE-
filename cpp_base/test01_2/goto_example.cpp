#include <iostream>

using namespace std;

int main() {
    cout << "========== goto 语句演示 ==========" << endl << endl;
    
    // 案例1：基本的 goto 跳转
    cout << "【案例1】基本 goto 跳转：" << endl;
    int x = 0;
    
    LOOP:  // 定义标签（标签后面必须跟冒号）
    cout << "x = " << x << endl;
    x++;
    if (x < 3) {
        goto LOOP;  // 跳转到 LOOP 标签处执行
    }
    
    cout << endl;
    
    // 案例2：使用 goto 跳过代码段
    cout << "【案例2】使用 goto 跳过代码段：" << endl;
    int choice = 2;
    
    if (choice == 1) {
        cout << "执行选项 1" << endl;
    } else if (choice == 2) {
        cout << "执行选项 2" << endl;
        goto SKIP;  // 跳过后续代码
    }
    
    cout << "这行代码被跳过了" << endl;
    
    SKIP:  // 标签位置
    cout << "跳过后继续执行" << endl << endl;
    
    // 案例3：使用 goto 进行错误处理（goto 的常见用途）
    cout << "【案例3】使用 goto 处理错误：" << endl;
    int num = -5;
    
    if (num < 0) {
        cout << "错误：输入数字为负数！" << endl;
        goto ERROR_HANDLER;  // 跳转到错误处理
    }
    
    cout << "数字处理成功：" << num << endl;
    goto END;  // 正常结束
    
    ERROR_HANDLER:  // 错误处理标签
    cout << "进入错误处理程序..." << endl;
    cout << "错误已被处理！" << endl;
    
    END:  // 结束标签
    cout << "\n程序结束" << endl;
    
    return 0;
}
