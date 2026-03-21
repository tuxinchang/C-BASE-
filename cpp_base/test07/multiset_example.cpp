#include <iostream>
#include <set>       // multiset定义在<set>中
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//multiset是C++标准库中的一个关联容器，属于set家族的一员。与set不同的是，multiset允许存储重复的元素，并且元素会自动按照一定的顺序进行排序（默认是升序）。
//multiset底层通常使用红黑树实现，因此插入、删除和查找操作的时间复杂度为O(log n)。multiset提供了丰富的成员函数来管理和访问其中的元素，
//例如insert()、erase()、find()、count()等。由于multiset允许重复元素，因此在使用时需要注意元素的唯一性问题。
//打印multiset的辅助函数
template<typename T>
void printMultiSet(const multiset<T>& ms, const string& description) {
    cout << description << ": ";
    if (ms.empty()) {
        cout << "multiset为空";
    } else {
        for (const auto& elem : ms) {
            cout << elem << " ";
        }
    }
    cout << endl;
}

int main() {
    cout << "=== C++ std::multiset 容器示例 ===" << endl << endl;
    
    // 1. 创建和初始化multiset
    cout << "1. 创建和初始化multiset:" << endl;
    multiset<int> ms1; // 空multiset
    multiset<int> ms2 = {30, 10, 20, 30, 40, 20, 50}; // 允许重复元素
    multiset<int> ms3(ms2); // 复制构造函数
    multiset<int> ms4(ms2.begin(), ms2.end()); // 迭代器范围
    
    printMultiSet(ms2, "ms2 (初始化为 {30,10,20,30,40,20,50}) - 自动排序");
    printMultiSet(ms3, "ms3 (复制ms2)");
    printMultiSet(ms4, "ms4 (使用迭代器构造)");
    
    cout << "ms2的大小: " << ms2.size() << " (注意：包含重复元素)" << endl;
    cout << endl;
    
    // 2. 插入元素（允许重复）
    cout << "2. 插入元素（允许重复）:" << endl;
    multiset<int> myMultiSet;
    
    // 插入单个元素
    myMultiSet.insert(50);
    myMultiSet.insert(30);
    myMultiSet.insert(20);
    myMultiSet.insert(30); // 重复元素
    myMultiSet.insert(30); // 再次重复
    printMultiSet(myMultiSet, "插入 50, 30, 20, 30, 30 后");
    
    // 插入多个元素
    myMultiSet.insert({10, 40, 60, 40}); // 40重复
    printMultiSet(myMultiSet, "插入 {10, 40, 60, 40} 后");
    
    // 使用迭代器插入（提示位置）
    auto hint = myMultiSet.find(30);
    myMultiSet.insert(hint, 35); // 在30附近插入35
    myMultiSet.insert(hint, 30); // 再次插入30
    printMultiSet(myMultiSet, "在30附近插入35和30后");
    
    cout << "当前multiset中元素总数: " << myMultiSet.size() << endl;
    cout << endl;
    
    // 3. 删除元素
    cout << "3. 删除元素:" << endl;
    
    // erase(元素) - 删除所有指定值的元素，返回删除的元素个数
    int count = myMultiSet.erase(30);
    cout << "删除所有30: 删除了 " << count << " 个元素" << endl;
    printMultiSet(myMultiSet, "删除所有30后");
    
    // 恢复一些元素以便后续演示
    myMultiSet.insert({30, 30, 30});
    printMultiSet(myMultiSet, "重新插入3个30后");
    
    // erase(迭代器) - 删除指定位置的单个元素
    auto it = myMultiSet.find(30);
    if (it != myMultiSet.end()) {
        myMultiSet.erase(it);
        cout << "删除第一个找到的30" << endl;
    }
    printMultiSet(myMultiSet, "删除一个30后");
    
    // 统计特定元素的个数
    cout << "元素30的当前个数: " << myMultiSet.count(30) << endl;
    cout << "元素40的当前个数: " << myMultiSet.count(40) << endl;
    cout << "元素99的当前个数: " << myMultiSet.count(99) << endl;
    cout << endl;
    
    // 4. 查找和访问
    cout << "4. 查找和访问元素:" << endl;
    multiset<int> searchMS = {10, 20, 20, 30, 30, 30, 40, 50};
    printMultiSet(searchMS, "searchMS");
    
    // find() - 查找第一个匹配的元素
    auto found = searchMS.find(30);
    if (found != searchMS.end()) {
        cout << "找到第一个元素30: " << *found << endl;
    }
    
    // 查找所有匹配的元素
    cout << "所有30的位置: ";
    auto range = searchMS.equal_range(30);
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // lower_bound() 和 upper_bound()
    auto lb = searchMS.lower_bound(25); // 第一个不小于25的元素
    auto ub = searchMS.upper_bound(35); // 第一个大于35的元素
    
    cout << "lower_bound(25): " << (lb != searchMS.end() ? to_string(*lb) : "end") << endl;
    cout << "upper_bound(35): " << (ub != searchMS.end() ? to_string(*ub) : "end") << endl;
    
    // 使用equal_range()获取范围
    auto range_20 = searchMS.equal_range(20);
    cout << "equal_range(20)范围大小: " << distance(range_20.first, range_20.second) << endl;
    
    cout << endl;
    
    // 5. 容量和大小
    cout << "5. 容量和大小:" << endl;
    cout << "searchMS的大小: " << searchMS.size() << endl;
    cout << "searchMS的最大大小: " << searchMS.max_size() << endl;
    cout << "searchMS是否为空: " << (searchMS.empty() ? "是" : "否") << endl;
    cout << endl;
    
    // 6. 迭代器
    cout << "6. 迭代器操作:" << endl;
    multiset<int> iterMS = {5, 2, 8, 2, 5, 5, 1};
    
    cout << "正向遍历: ";
    for (auto it = iterMS.begin(); it != iterMS.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "反向遍历: ";
    for (auto rit = iterMS.rbegin(); rit != iterMS.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;
    
    // 使用迭代器删除特定范围的元素
    auto first = iterMS.lower_bound(2);
    auto last = iterMS.upper_bound(5);
    iterMS.erase(first, last);
    printMultiSet(iterMS, "删除[2, 5]范围内的所有元素后");
    
    cout << endl;
    
    // 7. 自定义比较函数
    cout << "7. 自定义比较函数（降序multiset）:" << endl;
    multiset<int, greater<int>> descendingMS = {50, 10, 40, 20, 30, 20, 10};
    
    cout << "降序multiset: ";
    for (int n : descendingMS) cout << n << " ";
    cout << endl;
    cout << "元素10的个数: " << descendingMS.count(10) << endl;
    cout << endl;
    
    // 8. multiset与vector的交互
    cout << "8. multiset与vector的交互:" << endl;
    vector<int> vec = {7, 3, 5, 3, 7, 2, 9, 3};
    multiset<int> msFromVec(vec.begin(), vec.end());
    
    printMultiSet(msFromVec, "从vector构造的multiset");
    
    // 将multiset复制到vector
    vector<int> vecFromMS(msFromVec.begin(), msFromVec.end());
    cout << "从multiset构造的vector: ";
    for (int n : vecFromMS) cout << n << " ";
    cout << endl;
    
    // 使用算法处理multiset
    cout << "最小值: " << *msFromVec.begin() << endl;
    cout << "最大值: " << *(--msFromVec.end()) << endl;
    
    cout << endl;
    
    cout << "=== 示例结束 ===" << endl;
    
    return 0;
}