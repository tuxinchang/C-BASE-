#include <iostream>
#include <set>
#include <string>
#include <iterator>  // 用于std::ostream_iterator
#include <algorithm> // 用于std::copy

using namespace std;
//同样可以使用size，empty，swap
// 打印set的辅助函数
template<typename T>
void printSet(const set<T>& s, const string& description) {
    cout << description << ": ";
    if (s.empty()) {
        cout << "set为空";
    } else {
        for (const auto& elem : s) {
            cout << elem << " ";
        }
    }
    cout << endl;
}

int main() {
    cout << "=== C++ std::set 容器示例 ===" << endl << endl;
    
    // 1. 创建和初始化set
    cout << "1. 创建和初始化set:" << endl;
    set<int> set1; // 空set
    set<int> set2 = {30, 10, 20, 40, 50}; // 初始化列表
    set<int> set3(set2); // 复制构造函数
    set<int> set4(set2.begin(), set2.end()); // 迭代器范围
    
    printSet(set2, "set2 (初始化为 {30,10,20,40,50}) - 自动排序去重");
    printSet(set3, "set3 (复制set2)");
    printSet(set4, "set4 (使用迭代器构造)");
    cout << endl;
    
    // 2. 插入元素
    cout << "2. 插入元素:" << endl;
    set<int> mySet;
    
    // 插入单个元素
    mySet.insert(50);
    mySet.insert(30);
    mySet.insert(20);
    printSet(mySet, "插入 50, 30, 20 后");
    
    // 插入重复元素（会被忽略）
    auto result = mySet.insert(30);
    cout << "尝试插入重复元素30: " 
         << (result.second ? "成功" : "失败（已存在）") << endl;
    
    // 插入多个元素
    mySet.insert({10, 40, 60});
    printSet(mySet, "插入 {10, 40, 60} 后");
    
    // 使用迭代器插入（提示位置）
    auto hint = mySet.find(30);
    mySet.insert(hint, 35); // 在30附近插入35
    printSet(mySet, "在30附近插入35后");
    cout << endl;
    
    // 3. 删除元素
    cout << "3. 删除元素:" << endl;
    
    // erase(元素) - 删除指定值，返回删除的元素个数
    int count = mySet.erase(35);
    cout << "删除元素35: " << count << " 个元素被删除" << endl;
    printSet(mySet, "删除35后");
    
    // erase(迭代器) - 删除指定位置的元素
    auto it = mySet.find(20);
    if (it != mySet.end()) {
        mySet.erase(it);
        cout << "删除元素20" << endl;
    }
    printSet(mySet, "删除20后");
    
    // erase(迭代器范围)
    it = mySet.find(30);
    if (it != mySet.end()) {
        auto it_end = mySet.find(60);
        if (it_end != mySet.end()) {
            mySet.erase(it, ++it_end); // 删除[30, 60]范围
            cout << "删除[30, 60]范围内的元素" << endl;
        }
    }
    printSet(mySet, "删除[30, 60]范围后");
    
    // clear() - 清空set
    set<int> tempSet = {1, 2, 3, 4, 5};
    cout << "清空前: ";
    for (int n : tempSet) cout << n << " ";
    cout << endl;
    tempSet.clear();
    cout << "清空后: ";
    for (int n : tempSet) cout << n << " ";
    cout << endl << endl;
    
    // 4. 查找和访问
    cout << "4. 查找和访问元素:" << endl;
    set<int> searchSet = {10, 20, 30, 40, 50, 60};
    
    // find() - 查找元素，返回迭代器，找不到，机会返回set.end();set.end()是一个特殊的迭代器，表示容器的末尾位置，不指向任何元素
    auto found = searchSet.find(30);
    if (found != searchSet.end()) {
        cout << "找到元素30: " << *found << endl;
    } else {
        cout << "未找到元素30" << endl;
    }
    
    // count() - 统计元素出现次数（对于set总是0或1）
    cout << "元素30的出现次数: " << searchSet.count(30) << endl;
    cout << "元素99的出现次数: " << searchSet.count(99) << endl;
    
    // lower_bound() 和 upper_bound()
    auto lb = searchSet.lower_bound(25); // 第一个不小于25的元素
    auto ub = searchSet.upper_bound(45); // 第一个大于45的元素
    
    if (lb != searchSet.end()) {
        cout << "lower_bound(25): " << *lb << endl;
    }
    if (ub != searchSet.end()) {
        cout << "upper_bound(45): " << *ub << endl;
    }
    
    // equal_range() - 返回包含相等元素的范围
    auto range = searchSet.equal_range(30);
    cout << "equal_range(30): [" << *range.first << ", " << *range.second << ")" << endl;
    cout << endl;
    
    // 5. 容量和大小
    cout << "5. 容量和大小:" << endl;
    cout << "searchSet的大小: " << searchSet.size() << endl;
    cout << "searchSet的最大大小: " << searchSet.max_size() << endl;
    cout << "searchSet是否为空: " << (searchSet.empty() ? "是" : "否") << endl;
    cout << endl;
    
    // 6. 迭代器
    cout << "6. 迭代器操作:" << endl;
    cout << "正向遍历: ";
    for (auto it = searchSet.begin(); it != searchSet.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "反向遍历: ";
    for (auto rit = searchSet.rbegin(); rit != searchSet.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;
    
    // 首元素和尾后元素
    if (!searchSet.empty()) {
        cout << "第一个元素: " << *searchSet.begin() << endl;
        cout << "最后一个元素: " << *(--searchSet.end()) << endl;
    }
    cout << endl;
    
    // 7. 自定义比较函数
    cout << "7. 自定义比较函数（降序set）:" << endl;
    set<int, greater<int>> descendingSet = {50, 10, 40, 20, 30};
    
    cout << "降序set: ";
    for (int n : descendingSet) cout << n << " ";
    cout << endl;
    
    // 8. set运算
    cout << endl << "8. set运算:" << endl;
    set<int> setA = {1, 2, 3, 4, 5};
    set<int> setB = {3, 4, 5, 6, 7};
    
    printSet(setA, "setA");
    printSet(setB, "setB");
    
    // 并集
    set<int> unionSet;
    set_union(setA.begin(), setA.end(), setB.begin(), setB.end(), 
              inserter(unionSet, unionSet.begin()));
    printSet(unionSet, "并集 (A ∪ B)");
    
    // 交集
    set<int> intersectionSet;
    set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
                     inserter(intersectionSet, intersectionSet.begin()));
    printSet(intersectionSet, "交集 (A ∩ B)");
    
    // 差集
    set<int> differenceSet;
    set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
                   inserter(differenceSet, differenceSet.begin()));
    printSet(differenceSet, "差集 (A - B)");
    
    // 对称差集
    set<int> symmetricDifferenceSet;
    set_symmetric_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
                            inserter(symmetricDifferenceSet, symmetricDifferenceSet.begin()));
    printSet(symmetricDifferenceSet, "对称差集 (A Δ B)");
    cout << endl;
    
    // 9. 复杂数据类型示例
    cout << "9. 复杂数据类型示例 (自定义结构):" << endl;