#include <iostream>
//必须传入右值引用才能调用这个函数
void test(int&& x) {
    std::cout << "使用移动拷贝" << std::endl;
}
int main() {
    int a;
    test(std::move(a)); // 使用 std::move 将 a 转换为右值引用
    return 0;
}