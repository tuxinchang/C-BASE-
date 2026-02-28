#include <iostream>
#include <vector>
#include <string>
using namespace std;
//vextor本质上就是一个动态数组，底层通过连续的内存块来存储元素。当需要添加新元素时，如果当前容量不足，vector会自动分配更大的内存块，并将原有元素复制到新的内存位置。这种动态扩展机制使得vector非常灵活，能够适应不同大小的数据集合。
// 自定义类型
int main(){
// vector插入和删除操作案例
	cout << "\nvector插入和删除操作案例:" << endl;
	vector<int> vdel;
	vdel.push_back(1);
	vdel.push_back(2);
	vdel.push_back(3);
	vdel.push_back(4);
	cout << "初始vdel: ";
	for (int n : vdel) cout << n << ' ';
	cout << endl;
	// insert 在指定位置插入元素
	vdel.insert(vdel.begin() + 2, 99); // 在第3个位置插入99
	cout << "insert后: ";
	for (int n : vdel) cout << n << ' ';
	cout << endl;
	// insert 插入多个元素
	vdel.insert(vdel.begin(), 2, 77); // 在开头插入2个77
	cout << "插入多个元素后: ";
	for (int n : vdel) cout << n << ' ';
	cout << endl;
	// erase 删除指定位置元素
	vdel.erase(vdel.begin() + 1); // 删除第2个元素
	cout << "erase后: ";
	for (int n : vdel) cout << n << ' ';
	cout << endl;
	// erase 删除区间
	vdel.erase(vdel.begin(), vdel.begin() + 2); // 删除前两个元素
	cout << "删除区间后: ";
	for (int n : vdel) cout << n << ' ';
	cout << endl;
	// pop_back 删除最后一个元素
	vdel.pop_back();
	cout << "pop_back后: ";
	for (int n : vdel) cout << n << ' ';
	cout << endl;
	// clear 清空所有元素
	vdel.clear();
	cout << "clear后vdel.size(): " << vdel.size() << endl;
	vector<int> v;

	// reserve 只改变容量，不改变实际元素数量
	v.reserve(10); // 预分配10个元素的空间，但size仍为0
	cout << "reserve(10) 后 size: " << v.size() << ", capacity: " << v.capacity() << endl;

	// resize 改变实际元素数量，可能填充默认值
	v.resize(5); // 变为5个元素，默认填充0
	cout << "resize(5) 后 size: " << v.size() << ", capacity: " << v.capacity() << endl;
	cout << "resize后内容: ";
	for (int n : v) cout << n << ' ';
	cout << endl;

	// 再次resize扩大
	v.resize(8, 42); // 扩大到8个元素，新元素填充42
	cout << "resize(8, 42) 后内容: ";
	for (int n : v) cout << n << ' ';
	cout << endl;

	// 注释说明：
	// reserve(n) 只分配空间，不改变size，不初始化元素
	// resize(n) 改变size，若变大则填充默认值或指定值，变小则截断
	return 0;
}