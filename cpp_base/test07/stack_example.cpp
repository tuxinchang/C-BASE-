#include <iostream>
#include <stack>
using namespace std;

int main() {
	// 1. 构造函数
	stack<int> s1; // 默认构造
	s1.push(10);
	s1.push(20);
	s1.push(30);

	stack<int> s2(s1); // 拷贝构造

	// 2. 赋值操作
	stack<int> s3;
	s3 = s1; // 赋值

	// 3. 数据存取
	cout << "s1栈顶元素: " << s1.top() << endl;
	s1.pop();
	cout << "pop后s1栈顶: " << s1.top() << endl;
	s1.push(40);
	cout << "push(40)后s1栈顶: " << s1.top() << endl;

	// 4. 大小操作
	cout << "s1是否为空: " << (s1.empty() ? "true" : "false") << endl;
	cout << "s1大小: " << s1.size() << endl;

	// 5. 遍历（只能通过不断pop访问）
	cout << "\ns3出栈顺序: ";
	while (!s3.empty()) {
		cout << s3.top() << ' ';
		s3.pop();
	}
	cout << endl;

	return 0;
}
