#include <iostream>
#include <array>      // std::array 容器
#include <vector>     // std::vector 动态数组
#include <algorithm>  // 数组算法函数

using namespace std;

int main() {
    cout << "========== 数组定义与操作 ==========" << endl << endl;
    
    // 【1】整型数组
    cout << "【1】整型数组：" << endl;
    int intArr[5] = {10, 20, 30, 40, 50};  // 定义并初始化整型数组
    cout << "整型数组：";
    for (int i = 0; i < 5; i++) {
        cout << intArr[i] << " ";
    }
    cout << endl << endl;
    
    // 【2】浮点型数组
    cout << "【2】浮点型数组：" << endl;
    double doubleArr[4] = {1.5, 2.7, 3.14, 4.89};
    cout << "浮点型数组：";
    for (int i = 0; i < 4; i++) {
        cout << doubleArr[i] << " ";
    }
    cout << endl << endl;
    
    // 【3】字符型数组
    cout << "【3】字符型数组：" << endl;
    char charArr[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // \0 是字符串结束符,***长度为 6 包含结束符***
    cout << "字符型数组（按字符打印）：";
    for (int i = 0; i < 5; i++) {
        cout << charArr[i];
    }
    cout << endl;
    cout << "字符型数组（作为字符串打印）：" << charArr << endl << endl;
    
    // 【4】布尔型数组
    cout << "【4】布尔型数组：" << endl;
    bool boolArr[3] = {true, false, true};
    cout << "布尔型数组：";
    for (int i = 0; i < 3; i++) {
        cout << (boolArr[i] ? "true" : "false") << " ";
    }
    cout << endl << endl;
    
    // 【5】字符串数组（字符数组的数组）
    cout << "【5】字符串数组：" << endl;
    string strArr[3] = {"Hello", "World", "C++"};
    cout << "字符串数组：";
    for (int i = 0; i < 3; i++) {
        cout << strArr[i] << " ";
    }
    cout << endl << endl;
    
    // 【6】std::array - 固定大小的数组容器（C++11）
    cout << "【6】std::array（固定大小容器）：" << endl;
    array<int, 5> arr = {1, 2, 3, 4, 5};
    
    // array 的常用成员函数：
    cout << "size()：获取数组大小 = " << arr.size() << endl;
    cout << "at(i)：安全访问元素 arr.at(2) = " << arr.at(2) << endl;
    cout << "front()：获取首元素 = " << arr.front() << endl;
    cout << "back()：获取末元素 = " << arr.back() << endl;
    
    // fill() 用指定值填充所有元素
    array<int, 3> fillArr;
    fillArr.fill(99);
    cout << "fill(99)：";
    for (auto val : fillArr) {
        cout << val << " ";
    }
    cout << endl << endl;
    
    // 【7】std::vector - 动态数组（可变大小）
    cout << "【7】std::vector（动态数组）：" << endl;
    vector<int> vec;  // 创建空向量
    
    // push_back() 在末尾添加元素
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    cout << "push_back() 后的 vector：";
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    // vector 的常用成员函数：
    cout << "size()：获取元素个数 = " << vec.size() << endl;
    cout << "empty()：是否为空 = " << (vec.empty() ? "true" : "false") << endl;
    cout << "capacity()：容器容量 = " << vec.capacity() << endl;
    
    // pop_back() 删除末尾元素
    cout << "pop_back() 前的大小：" << vec.size() << endl;
    vec.pop_back();
    cout << "pop_back() 后的大小：" << vec.size() << endl;
    
    // insert() 在指定位置插入元素
    vec.insert(vec.begin() + 1, 15);  // 在第二个位置插入 15
    cout << "insert() 后的 vector：";
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    // erase() 删除指定位置的元素
    vec.erase(vec.begin() + 1);  // 删除第二个位置的元素
    cout << "erase() 后的 vector：";
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    // assign() 重新赋值整个向量
    vec.assign(3, 100);  // 用 3 个 100 替换所有元素
    cout << "assign() 后的 vector：";
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    // clear() 清空向量
    cout << "clear() 前的大小：" << vec.size() << endl;
    vec.clear();
    cout << "clear() 后的大小：" << vec.size() << endl << endl;
    
    // 【8】数组遍历方法对比
    cout << "【8】数组遍历方法：" << endl;
    int arr8[5] = {1, 2, 3, 4, 5};
    
    // 方法1：传统 for 循环
    cout << "方法1（传统 for）：";
    for (int i = 0; i < 5; i++) {
        cout << arr8[i] << " ";
    }
    cout << endl;
    
    // 方法2：范围 for 循环（C++11，推荐使用）
    cout << "方法2（范围 for）：";
    for (int val : arr8) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
