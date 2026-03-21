#include <iostream>
#include <string>
// 类模板
using namespace std;

template<typename T>
class Box {
public:
	T value;
	Box(T v) : value(v) {}
	void print() const { cout << "Box(" << value << ")" << endl; }
};

// 1. 指定传入类型
void showIntBox(Box<int> b) {
	cout << "指定类型参数：";
	b.print();
}

// 2. 参数模板化
template<typename T>
void showTemplateBox(Box<T> b) {
	cout << "参数模板化：";
	b.print();
}

// 3. 整个类模板化
template<typename C>
void showAnyBox(C b) {
	cout << "整个类模板：";
	b.print();
}
#include <iostream>
#include <cstring>
using namespace std;

// 通用函数模板：比较两个值的大小
template<typename T>
T myMax(T a, T b) {
	cout << "通用模板被调用\n";
	return (a > b) ? a : b;
}

// 针对 const char* 的具体化（特化）template<>表示优先调用
template<>
const char* myMax<const char*>(const char* a, const char* b) {
	cout << "const char* 特化被调用\n";
	return strcmp(a, b) > 0 ? a : b;
}

int main() {
	Box<int> ibox(123);
	Box<double> dbox(3.14);
	Box<string> sbox("hello");
	showIntBox(ibox);           // 指定类型
	showTemplateBox(dbox);      // 参数模板化
	showAnyBox(sbox);           // 整个类模板
	cout << myMax(10, 20) << endl; // 通用模板
	cout << myMax(3.14, 2.71) << endl; // 通用模板
	const char* s1 = "apple";
	const char* s2 = "banana";
	cout << myMax(s1, s2) << endl; // const char* 特化
	return 0;
}
