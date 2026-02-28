#include <iostream>
using namespace std;

// 类模板声明
template<typename T>
class MyBox {
private:
	T value;
public:
	MyBox(T v);
	void show() const;
	T getValue() const;
};

// 类模板成员函数类外实现
template<typename T>
MyBox<T>::MyBox(T v) : value(v) {}

template<typename T>
void MyBox<T>::show() const {
	cout << "MyBox value: " << value << endl;
}

template<typename T>
T MyBox<T>::getValue() const {
	return value;
}

int main() {
	MyBox<int> ibox(123);
	ibox.show();
	cout << "ibox.getValue(): " << ibox.getValue() << endl;

	MyBox<string> sbox("hello");
	sbox.show();
	cout << "sbox.getValue(): " << sbox.getValue() << endl;
	return 0;
}
