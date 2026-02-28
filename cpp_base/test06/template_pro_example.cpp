#include <iostream>
using namespace std;

// 基类模板
template<typename T>
class Base {
protected:
	T data;
public:
	Base(T d) : data(d) {}
	void show() const { cout << "Base: " << data << endl; }
	// 声明友元函数模板
	template<typename U>
	friend void printBase(const Base<U>&);
};

/*派生类模板，继承基类模板  也能指定父类模板参数，
例如 class Derived : public Base<int> { ... }，这样Derived就固定继承自Base<int>，
而不是Base<T>，这时Derived就不再是一个模板类，而是一个普通类。*/
template<typename T>  //泛型名称与父类模板相同，但不影响父类模板参数的使用
class Derived : public Base<T> {
public:
	Derived(T d) : Base<T>(d) {}
	void show() const { cout << "Derived: " << this->data << endl; }
	// 声明友元函数
	friend void printDerived(const Derived<T>&);
};

// 友元函数模板实现
template<typename U>
void printBase(const Base<U>& b) {
	cout << "友元Base: " << b.data << endl;
}

// 友元函数实现
void printDerived(const Derived<int>& d) {
	cout << "友元Derived<int>: " << d.data << endl;
}

int main() {
	Base<double> b(3.14);
	Derived<int> d(42);
	b.show();
	d.show();
	printBase(b);         // 友元函数模板
	printDerived(d);      // 友元函数
	return 0;
}
