#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
//vector和deque(双端队列)都是C++标准库中提供的容器类，他们方法大部分通用
int main() {
	// 1. 构造方式
	deque<int> dq1; // 默认构造
	deque<int> dq2(5, 10); // 5个10
	int arr[] = {1, 2, 3, 4};
	deque<int> dq3(arr, arr + 4); // 区间构造
	deque<int> dq4(dq3); // 拷贝构造

	cout << "dq1.size(): " << dq1.size() << endl;
	cout << "dq2内容: ";
	for (int n : dq2) cout << n << ' ';
	cout << endl;
	cout << "dq3内容: ";
	for (int n : dq3) cout << n << ' ';
	cout << endl;
	cout << "dq4内容: ";
	for (int n : dq4) cout << n << ' ';
	cout << endl;

	// 2. 内置函数
	dq1.push_back(100);
	dq1.push_front(200);
	dq1.push_back(300);
	dq1.push_front(400);
	cout << "\npush_back/push_front后dq1: ";
	for (int n : dq1) cout << n << ' ';
	cout << endl;

	dq1.pop_back();
	dq1.pop_front();
	cout << "pop_back/pop_front后dq1: ";
	for (int n : dq1) cout << n << ' ';
	cout << endl;

	cout << "front(): " << dq1.front() << ", back(): " << dq1.back() << endl;
	cout << "at(0): " << dq1.at(0) << endl;
	cout << "empty(): " << (dq1.empty() ? "true" : "false") << endl;
	dq1.clear();
	cout << "clear()后dq1.size(): " << dq1.size() << endl;

	// 3. 遍历方式
	cout << "\n遍历dq2（范围for）: ";
	for (int n : dq2) cout << n << ' ';
	cout << endl;

	cout << "遍历dq2（迭代器）: ";
	for (deque<int>::iterator it = dq2.begin(); it != dq2.end(); ++it) cout << *it << ' ';
	cout << endl;
	//使用算法库函数
	cout << "使用算法库函数（sort）对dq3排序: ";
	sort(dq3.begin(), dq3.end(), greater<int>()); // 降序排序
	for (int n : dq3) cout << n << ' ';
	cout << endl;

	return 0;
}
