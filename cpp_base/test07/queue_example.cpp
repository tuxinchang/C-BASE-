#include <iostream>
#include <queue>
using namespace std;

int main() {
	// 1. 构造函数
	queue<int> q1; // 默认构造
	q1.push(10);
	q1.push(20);
	q1.push(30);

	queue<int> q2(q1); // 拷贝构造

	// 2. 赋值操作
	queue<int> q3;
	q3 = q1; // 赋值

	// 3. 数据存取
	cout << "q1队首元素: " << q1.front() << endl;
	cout << "q1队尾元素: " << q1.back() << endl;
	q1.pop();
	cout << "pop后q1队首: " << q1.front() << endl;
	q1.push(40);
	cout << "push(40)后q1队尾: " << q1.back() << endl;

	// 4. 大小操作
	cout << "q1是否为空: " << (q1.empty() ? "true" : "false") << endl;
	cout << "q1大小: " << q1.size() << endl;

	// 5. 遍历（只能通过不断pop访问）
	cout << "\nq3出队顺序: ";
	while (!q3.empty()) {
		cout << q3.front() << ' ';
		q3.pop();
	}
	cout << endl;

	return 0;
}
