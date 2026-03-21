#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "========== 多维数组案例 ==========" << endl << endl;
    
    // 【1】二维数组 - 整型矩阵
    cout << "【1】二维数组（整型矩阵）：" << endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},      // 第 0 行
        {5, 6, 7, 8},      // 第 1 行
        {9, 10, 11, 12}    // 第 2 行
    };
    
    cout << "矩阵内容（逐行打印）：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // 访问二维数组中的单个元素
    cout << "访问元素：matrix[1][2] = " << matrix[1][2] << endl;
    cout << "访问元素：matrix[2][3] = " << matrix[2][3] << endl << endl;
    
    // 【2】二维数组 - 浮点型矩阵
    cout << "【2】二维数组（浮点型矩阵）：" << endl;
    double floatMatrix[2][3] = {
        {1.1, 2.2, 3.3},
        {4.4, 5.5, 6.6}
    };
    
    cout << "浮点矩阵内容：" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << floatMatrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // 【3】二维数组 - 字符类型矩阵
    cout << "【3】二维数组（字符类型矩阵）：" << endl;
    char charMatrix[3][3] = {
        {'A', 'B', 'C'},
        {'D', 'E', 'F'},
        {'G', 'H', 'I'}
    };
    
    cout << "字符矩阵内容：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << charMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // 【4】三维数组
    cout << "【4】三维数组：" << endl;
    int cube[2][2][3] = {
        {
            {1, 2, 3},
            {4, 5, 6}
        },
        {
            {7, 8, 9},
            {10, 11, 12}
        }
    };
    
    cout << "三维数组内容（[第一维][行][列]）：" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "第 " << i << " 个二维平面：" << endl;
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                cout << cube[i][j][k] << "\t";
            }
            cout << endl;
        }
    }
    
    // 访问三维数组元素
    cout << "访问元素：cube[1][1][2] = " << cube[1][1][2] << endl << endl;
    
    // 【5】二维 vector（动态二维数组）
    cout << "【5】二维 vector（动态二维数组）：" << endl;
    
    // 创建 3 行 4 列的二维 vector，初始值为 0
    vector<vector<int>> matrix2d(3, vector<int>(4, 0));
    
    // 赋值
    int value = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrix2d[i][j] = value++;
        }
    }
    
    cout << "二维 vector 内容：" << endl;
    for (int i = 0; i < matrix2d.size(); i++) {
        for (int j = 0; j < matrix2d[i].size(); j++) {
            cout << matrix2d[i][j] << "\t";
        }
        cout << endl;
    }
    
    // vector 的灵活操作
    cout << "\nvector 的灵活操作：" << endl;
    cout << "矩阵行数：" << matrix2d.size() << endl;
    cout << "矩阵列数：" << matrix2d[0].size() << endl;
    cout << "访问元素：matrix2d[2][3] = " << matrix2d[2][3] << endl << endl;
    
    // 【6】三维 vector（动态三维数组）
    cout << "【6】三维 vector（动态三维数组）：" << endl;
    
    // 创建 2 个 2x3 的二维矩阵（动态三维数组）
    vector<vector<vector<int>>> cube2(2, vector<vector<int>>(2, vector<int>(3, 0)));
    
    // 赋值
    value = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                cube2[i][j][k] = value++;
            }
        }
    }
    
    cout << "三维 vector 内容：" << endl;
    for (int i = 0; i < cube2.size(); i++) {
        cout << "第 " << i << " 个平面：" << endl;
        for (int j = 0; j < cube2[i].size(); j++) {
            for (int k = 0; k < cube2[i][j].size(); k++) {
                cout << cube2[i][j][k] << "\t";
            }
            cout << endl;
        }
    }
    cout << endl;
    
    // 【7】不规则二维数组（每行列数不同）
    cout << "【7】不规则二维数组（vector 支持）：" << endl;
    vector<vector<int>> irregular;
    irregular.push_back({1, 2, 3});           // 第 0 行：3 列
    irregular.push_back({4, 5});              // 第 1 行：2 列
    irregular.push_back({6, 7, 8, 9});        // 第 2 行：4 列
    
    cout << "不规则数组内容：" << endl;
    for (int i = 0; i < irregular.size(); i++) {
        cout << "第 " << i << " 行（" << irregular[i].size() << " 列）：";
        for (int j = 0; j < irregular[i].size(); j++) {
            cout << irregular[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // 【8】多维数组的遍历方式对比
    cout << "【8】多维数组的遍历方式：" << endl;
    int arr2d[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    cout << "方法1（传统嵌套 for）：";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr2d[i][j] << " ";
        }
    }
    cout << endl;
    
    cout << "方法2（范围 for）：";
    for (auto& row : arr2d) {
        for (auto val : row) {
            cout << val << " ";
        }
    }
    cout << endl;
    
    return 0;
}
