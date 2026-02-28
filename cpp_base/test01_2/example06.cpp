#include <iostream>

using namespace std;

int main() {
    int i = 1;
    
    // 嵌套 while 循环实现九九乘法表
    while (i <= 9) {
        int j = 1;
        while (j <= i) {
            cout << j << "*" << i << "=" << i * j << "\t";
            j++;
        }
        cout << endl;
        i++;
    }
    
    return 0;
}
