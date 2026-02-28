#include <iostream>
#include <vector>
#include <string>
using namespace std;
//vextor本质上就是一个动态数组，底层通过连续的内存块来存储元素。当需要添加新元素时，如果当前容量不足，vector会自动分配更大的内存块，并将原有元素复制到新的内存位置。这种动态扩展机制使得vector非常灵活，能够适应不同大小的数据集合。
// 自定义类型
class Person {
public:
	string name;
	int age;
	Person(string n, int a) : name(n), age(a) {}
};

int main() {
	

	// assign 用法（内置类型）
	vector<int> v1;
	v1.assign(5, 100); // 5个100
	cout << "\nassign(5, 100) 后 v1: ";
	for (int n : v1) cout << n << ' ';
	cout << endl;
	// assign 用法（区间赋值）
	int arr[] = {1, 2, 3, 4};
	v1.assign(arr, arr + 4);
	cout << "assign(arr, arr+4) 后 v1: ";
	for (int n : v1) cout << n << ' ';
	cout << endl;
	// assign 用法（自定义类型）
	vector<Person> vpeople;
	Person p("Tom", 30);
	vpeople.assign(3, p); // 3个Tom
	cout << "\nassign(3, Person) 后 vpeople:\n";
	for (const auto& per : vpeople) {
		cout << "姓名: " << per.name << ", 年龄: " << per.age << endl;
	}
	
	// 1. vector 存放内置数据类型
	vector<int> nums;
	nums.push_back(10);
	nums.push_back(20);
	nums.push_back(30);

	cout << "vector<int> 内容: ";
	for (size_t i = 0; i < nums.size(); ++i) {
		cout << nums[i] << " ";
	}
	cout << endl;

	// 2. vector 存放自定义类型
	vector<Person> people;
	people.push_back(Person("Alice", 18));
	people.push_back(Person("Bob", 20));
	people.push_back(Person("Carol", 22));

	cout << "vector<Person> 内容:\n";
	for (const auto& p : people) {
		cout << "姓名: " << p.name << ", 年龄: " << p.age << endl;
	}

	// 3. vector 的常用操作
	cout << "\nvector<int> 的常用操作演示:" << endl;
	cout << "size(): " << nums.size() << endl;
	cout<<"capacity(): " << nums.capacity() << endl;
	cout << "front(): " << nums.front() << endl;
	cout << "back(): " << nums.back() << endl;
	cout<<"是否为空: " << (nums.empty() ? "true" : "false") << endl;
	nums.pop_back();
	cout << "pop_back() 后 size(): " << nums.size() << endl;

	// 4. 迭代器遍历
	cout << "\n用迭代器遍历 vector<int>: ";
	for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	// 访问 vector 指定位置元素
		cout << "\n访问 vector 指定位置元素:" << endl;
		if (!nums.empty()) {
			cout << "nums[1]: " << nums[1] << endl;
			cout << "nums.at(2): " << nums.at(2) << endl;
			cout << "nums.front(): " << nums.front() << endl;
			cout << "nums.back(): " << nums.back() << endl;
		}
		// 注意：at() 会检查越界，若访问非法位置会抛出异常
	return 0;
}
