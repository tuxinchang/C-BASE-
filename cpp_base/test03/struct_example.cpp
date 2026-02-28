#include <iostream>
#include <string>
using namespace std;

// 简单的结构体定义
struct Person
{
	string name;
	int age;
};

// 通过值传递（会拷贝）
void printByValue(Person p)
{
	cout << "ByValue - Name: " << p.name << ", Age: " << p.age << endl;
}

// 通过指针传递（不拷贝，可修改）
void increaseAge(Person* p)
{
	if(p) ++(p->age);
}

// 通过常量引用传递（不拷贝，不可修改）
void printConstRef(const Person& p)
{
	cout << "ConstRef - Name: " << p.name << ", Age: " << p.age << endl;
}

int main()
{
	cout << "===== 结构体 基本用法 =====" << endl;

	// 1. 直接初始化
	Person alice{"Alice", 30};
	cout << "姓名: " << alice.name << ", 年龄: " << alice.age << endl;

	// 2. 拷贝与传参
	printByValue(alice);       // 传值（会拷贝）
	printConstRef(alice);      // 传常量引用（无拷贝）

	// 3. 指针操作结构体
	Person* p = &alice;
	increaseAge(p);            // 通过指针修改
	cout << "increaseAge 后: " << alice.age << endl;

	// 4. 动态分配结构体
	Person* bob = new Person{"Bob", 25};
	cout << "动态分配: " << bob->name << ", " << bob->age << endl;
	delete bob;
	bob = nullptr;

	// 5. 结构体数组与指针遍历
	Person team[] = { {"Tom",20}, {"Jerry",22}, {"Mia",19} };
	int n = sizeof(team)/sizeof(team[0]);
	Person* it = team; // 指向首元素
	cout << "团队成员: ";
	for(int i = 0; i < n; ++i)
	{
		cout << (it + i)->name << "(" << (it + i)->age << ") ";
	}
	cout << endl;

	// 6. const 与结构体的两种常见用法示例
	const Person carol{"Carol", 28};
	// carol.age = 29; // 错误：不可修改
	printConstRef(carol); // 可以传入 const 引用

	// const 指针 -- 指针本身可变，但不能通过它修改指向的数据
	Person dave{"Dave", 40};
	const Person* pc = &dave; // 指向常量的指针
	// pc->age = 41; // 错误：不能修改 *pc
	pc = &alice; // 指针可变，能指向别处

	// 指向指针本身不可变，但可以修改指向的数据
	Person* const cp = &dave; // 常量指针（pointer is const）
	cp->age = 41; // 允许
	// cp = &alice; // 错误：不能改变指针本身

	cout << "pc 指向: " << pc->name << ", cp 指向: " << cp->name << ", cp.age=" << cp->age << endl;

	// 7. 结构体指针数组 - 存储指向多个结构体的指针
	cout << "\n===== 结构体指针数组 =====" << endl;
	
	// 动态创建结构体对象
	Person* pArr[3];
	pArr[0] = new Person{"张三", 28};
	pArr[1] = new Person{"李四", 32};
	pArr[2] = new Person{"王五", 26};
	
	// 遍历结构体指针数组
	cout << "遍历结构体指针数组: " << endl;
	for(int i = 0; i < 3; ++i)
	{
		cout << "  [" << i << "] " << pArr[i]->name << ", 年龄: " << pArr[i]->age << endl;
	}
	
	// 通过指针数组修改数据
	cout << "\n将所有人年龄增加1:" << endl;
	for(int i = 0; i < 3; ++i)
	{
		pArr[i]->age++;
		cout << "  " << pArr[i]->name << " -> " << pArr[i]->age << endl;
	}
	
	// 使用指向指针数组的指针遍历
	cout << "\n使用指针遍历指针数组:" << endl;
	Person** ppArr = pArr;  // 指向指针数组的指针
	for(int i = 0; i < 3; ++i)
	{
		cout << "  " << ppArr[i]->name << " (" << ppArr[i]->age << ")" << endl;
	}
	
	// 释放动态分配的内存
	cout << "\n释放结构体指针数组的内存:" << endl;
	for(int i = 0; i < 3; ++i)
	{
		delete pArr[i];
		pArr[i] = nullptr;
	}
	cout << "内存已释放" << endl;

	cout << "\n===== 结构体 示例 结束 =====" << endl;
	return 0;
}

