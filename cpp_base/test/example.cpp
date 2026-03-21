#include <iostream>
#include <cstdlib>  // rand() 和 srand() 函数
#include <ctime>    // time() 函数，用于生成随机种子
#include <random>   // C++11 随机数库

using namespace std;
void change(int* a) {
    *a = 10;
}
int main() {
    int i = 6;
    int* j = nullptr;
    int& k= i;
    j = &i;
    int* ss=new int(5);
    change(ss);
    cout << "i的值: " << i << endl;
    cout << "j的值: " << *j << endl;
    cout << "k的值: " << k << endl;
    cout << "ss的值: " << *ss << endl;
}