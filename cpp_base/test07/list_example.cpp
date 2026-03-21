#include <iostream>
#include <list>
using namespace std;
// 打印list内容的辅助函数
void printList(const list<int>& lst, const string& description) {
    cout << description << ": ";
    if (lst.empty()) {
        cout << "list为空";
    } else {
        for (int num : lst) {
            cout << num << " ";
        }
    }
    cout << endl;
}
// list 是一个双向链表容器，适合频繁插入和删除的场景，但不支持随机访问.
int main() {

	// 1. 默认构造
	list<int> l1;

	// 2. n个初值构造
	list<int> l2(5, 100); // 5个100

	// 3. 区间构造
	int arr[] = {1, 2, 3, 4};
	list<int> l3(arr, arr + 4);

	// 4. 拷贝构造
	list<int> l4(l3);

	cout << "l1.size(): " << l1.size() << endl;
	cout << "l2: ";
	for (int n : l2) cout << n << ' ';
	cout << endl;
	cout << "l3: ";
	for (int n : l3) cout << n << ' ';
	cout << endl;
	cout << "l4: ";
	for (int n : l4) cout << n << ' ';
	cout << endl;

	// 5. 赋值操作  assign 用法（内置类型）也可以使用
	list<int> l5;
	l5 = l2; // 赋值
	cout << "l5(赋值自l2): ";
	for (int n : l5) cout << n << ' ';
	cout << endl;

	// 6. 交换操作
	cout << "\n交换前: " << endl;
	cout << "l2: ";
	for (int n : l2) cout << n << ' ';
	cout << endl;
	cout << "l3: ";
	for (int n : l3) cout << n << ' ';
	cout << endl;
	l2.swap(l3);
	cout << "交换后: " << endl;
	cout << "l2: ";
	for (int n : l2) cout << n << ' ';
	cout << endl;
	cout << "l3: ";
	for (int n : l3) cout << n << ' ';
	cout << endl;
	// 7. 大小相关操作
	cout << "\n大小相关操作演示:" << endl;
	cout << "l2.empty(): " << (l2.empty() ? "true" : "false") << endl;
	cout << "l2.size(): " << l2.size() << endl;
	l2.resize(3); // 缩小到3个元素
	cout << "l2.resize(3)后: ";
	for (int n : l2) cout << n << ' ';
	cout << endl;
	l2.resize(6, 7); // 扩大到6个元素，新增元素为7
	cout << "l2.resize(6,7)后: ";
	for (int n : l2) cout << n << ' ';
	cout << endl;
	l2.clear();
	cout << "l2.clear()后size: " << l2.size() << ", empty: " << (l2.empty() ? "true" : "false") << endl;
	 


	/*链表的操作流程*/ 

	 // 1. 创建并初始化一个list
    list<int> myList = {10, 20, 30};
    printList(myList, "初始list");
    cout << endl;
    
    // 2. push_back(elem) - 在容器尾部加入一个元素
    cout << "1. push_back(40):" << endl;
    myList.push_back(40);
    printList(myList, "在尾部添加40后");
    cout << endl;
    
    // 3. push_front(elem) - 在容器开头插入一个元素
    cout << "2. push_front(5):" << endl;
    myList.push_front(5);
    printList(myList, "在开头添加5后");
    cout << endl;
    
    // 4. pop_back() - 删除容器中最后一个元素
    cout << "3. pop_back():" << endl;
    myList.pop_back();
    printList(myList, "删除尾部元素后");
    cout << endl;
    
    // 5. pop_front() - 从容器开头移除第一个元素
    cout << "4. pop_front():" << endl;
    myList.pop_front();
    printList(myList, "删除开头元素后");
    cout << endl;
    
    // 6. insert(pos, elem) - 在pos位置插elem元素的拷贝，返回新数据的位置
    cout << "5. insert(迭代器位置, 50):" << endl;
    auto it = myList.begin();
    advance(it, 1); // 移动到第二个位置
    auto newPos = myList.insert(it, 50);
    printList(myList, "在第二个位置插入50后");
    cout << "新插入元素的位置的值: " << *newPos << endl;
    cout << endl;
    
    // 7. insert(pos, n, elem) - 在pos位置插入n个elem数据
    cout << "6. insert(迭代器位置, 3, 99):" << endl;
    it = myList.begin();
    advance(it, 3); // 移动到第四个位置
    myList.insert(it, 3, 99); // 插入3个99
    printList(myList, "在第四个位置插入3个99后");
    cout << endl;
    
    // 8. insert(pos, beg, end) - 在pos位置插入[beg,end]区间的数据
    cout << "7. insert(迭代器位置, [100, 101, 102]):" << endl;
    list<int> anotherList = {100, 101, 102};
    it = myList.end(); // 准备在末尾插入
    myList.insert(it, anotherList.begin(), anotherList.end());
    printList(myList, "在末尾插入另一个list的内容后");
    cout << endl;
    
    // 9. erase(pos) - 删除pos位置的数据，返回下一个数据的位置
    cout << "8. erase(第三个位置):" << endl;
    it = myList.begin();
    advance(it, 2); // 移动到第三个位置
    it = myList.erase(it); // 删除第三个元素
    printList(myList, "删除第三个元素后");
    cout << "返回的下一个位置的值: " << *it << endl;
    cout << endl;
    
    // 10. erase(beg, end) - 删除[beg,end]区间的数据
    cout << "9. erase(第四个到第七个位置):" << endl;
    auto it1 = myList.begin();
    advance(it1, 3); // 移动到第四个位置
    auto it2 = myList.begin();
    advance(it2, 7); // 移动到第八个位置
    it = myList.erase(it1, it2); // 删除[第四个, 第八个)位置的元素
    printList(myList, "删除第四个到第七个元素后");
    cout << "返回的下一个位置的值: " << *it << endl;
    cout << endl;
    
    // 11. remove(elem) - 删除容器中所有与elem值匹配的元素
    cout << "10. remove(99):" << endl;
    // 先添加一些99以便演示删除
    myList.push_back(99);
    myList.push_front(99);
    printList(myList, "添加两个99后");
    myList.remove(99);
    printList(myList, "删除所有99后");
    cout << endl;
    
    // 12. clear() - 移除容器的所有数据
    cout << "11. clear():" << endl;
    myList.clear();
    printList(myList, "清空list后");
    
    // 13. 重新填充list以进行更多演示
    cout << endl << "--- 重新填充list进行更多演示 ---" << endl;
    for (int i = 1; i <= 10; ++i) {
        myList.push_back(i);
    }
    printList(myList, "重新填充list后");
    
    // 14. 综合示例：使用多种操作
    cout << endl << "--- 综合操作示例 ---" << endl;
    
    // 删除所有偶数
    myList.remove_if([](int n) { return n % 2 == 0; });
    printList(myList, "删除所有偶数后");
    
    // 在特定位置插入
    it = myList.begin();
    advance(it, 1);
    myList.insert(it, 50);
    printList(myList, "在第二个位置插入50后");
    
    // 删除第一个和最后一个元素
    myList.pop_front();
    myList.pop_back();
    printList(myList, "删除首尾元素后");
    
    cout << endl << "=== 示例结束 ===" << endl;
	//list不支持at访问，因为他本质是链表，不能随机访问，
	//迭代器 list<int>::iterator it = l2.begin();  it=it+1 是错误的，必须使用it++表示顺序移动
	myList.reverse(); // 反转list元素顺序
	printList(myList, "反转list后");
	//sort(mylist.begin(),mylist.end()) 错误，list容器没有随机访问迭代器，不能使用标准算法库的sort函数，但list有自己的成员函数sort()可以直接调用
	myList.sort(); // 升序排序
	
	return 0;
}
