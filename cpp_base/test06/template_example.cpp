#include <iostream>
using namespace std;
/*
普通函数与函数模板调用规则
1、如果函数模板和普通函数都可以调用，优先调用普通函数
2、可以通过空模板参数列表强制调用函数模板  例如1：myMax<>(3, 7) 强制调用函数模板 myMax<int>(3, 7)，而不是普通函数 myMax(int, int)；
3、函数模板可以发生函数重载，例如参数不同的同名函数模板，编译器会根据传入参数类型选择最合适的函数模板进行实例化；
4、如果函数模板可以产生更好的匹配，优先调用函数模板

函数模版的局限性：
1、函数模板不能直接部分特化，但可以通过重载来实现类似效果。
2、函数模板不能有默认模板参数，但可以通过重载来实现类似效果。
3、函数模板不能直接访问类的私有成员，但可以通过友元函数模板来实现。
4、函数模板的错误信息可能较为复杂，尤其是在模板参数推导失败时，编译器可能会产生大量的错误信息，难以理解和调试。
5、函数模板的编译时间可能较长，尤其是在大量实例化时，可能会导致编译时间显著增加。
6、函数模板不能直接使用非类型模板参数，但可以通过类模板来实现类似效果。
7、函数模板不能直接使用模板模板参数，但可以通过类模板来实现类似效果。
8、函数模板不能直接使用模板参数作为返回类型，但可以通过 trailing return type 或者 decltype 来实现类似效果。
*/
// 示例类：Box
class Box {
public:
	int value;
	Box(int v) : value(v) {}
	bool operator>(const Box& other) const { return this->value > other.value; }
	friend ostream& operator<<(ostream& os, const Box& b) {
		os << "Box(" << b.value << ")";
		return os;
	}
};
// 针对类对象的函数模板：返回较大Box
template<typename T>
T getBigger(const T& a, const T& b) {
	return (a > b) ? a : b;
}
// 函数模板：求最大值
template<typename T>
T myMax(T a, T b) {
	return (a > b) ? a : b;
}

// 类模板：通用数组容器   泛型T的名称随便取，可以将T换成G,R等任意标识符，编译器会根据使用时传入的类型进行替换
//类模版没有自动推导功能（除非给了默认参数），必须在使用时显式指定类型参数，例如 MyArray<int, 5> arr; 其中 int 是类型参数，5 是非类型参数
//类模版可以有默认参数，例如 template<typename T = int, int N = 10> class MyArray { ... }，这样在使用时如果不指定类型参数和非类型参数，就会使用默认值 MyArray<> arr; 等价于 MyArray<int, 10> arr;
template<typename T, int N>
class MyArray {
private:
	T data[N];
	int size;
public:
	MyArray() : size(0) {}
	void push(const T& value) {
		if (size < N) {
			data[size++] = value;
		} else {
			cout << "数组已满，无法添加" << endl;
		}
	}
	T& operator[](int idx) {
		return data[idx];
	}
	int getSize() const { return size; }
	void print() const {
		cout << "MyArray 内容: ";
		for (int i = 0; i < size; ++i) {
			cout << data[i] << " ";
		}
		cout << endl;
	}
};

int main() {

	// 函数模板对类的应用
	Box box1(100), box2(200);
	Box biggerBox = getBigger(box1, box2);
	cout << "较大的Box: " << biggerBox << endl;
	// 函数模板演示
    
    //自动类型推导 两个变量要一致才能推导成功，否则需要显式指定类型
	cout << "int 最大值: " << myMax(3, 7) << endl;
	cout << "double 最大值: " << myMax(3.14, 2.71) << endl;
    // 显式指定模板参数类型，当传入的参数类型不一致时需要显式指定模板参数类型，否则会编
    cout << "int 最大值: " << myMax<int>(3,'a') << endl;
	cout << "char 最大值: " << myMax('a', 'z') << endl;

	// 类模板演示
	MyArray<int, 5> arr;
	arr.push(10);
	arr.push(20);
	arr.push(30);
	arr.print();
	cout << "第2个元素: " << arr[1] << endl;

	MyArray<string, 3> strArr;
	strArr.push("hello");
	strArr.push("world");
	strArr.print();

	return 0;
}
