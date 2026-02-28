#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// 打印map的辅助函数 - C++11兼容版本
template<typename K, typename V>
void printMap(const map<K, V>& m, const string& description) {
    cout << description << ":" << endl;
    if (m.empty()) {
        cout << "  map为空" << endl;
    } else {
        for (typename map<K, V>::const_iterator it = m.begin(); it != m.end(); ++it) {
            cout << "  " << it->first << " => " << it->second << endl;
        }
    }
    cout << endl;
}

// 打印multimap的辅助函数 - C++11兼容版本
template<typename K, typename V>
void printMultiMap(const multimap<K, V>& mm, const string& description) {
    cout << description << ":" << endl;
    if (mm.empty()) {
        cout << "  multimap为空" << endl;
    } else {
        for (typename multimap<K, V>::const_iterator it = mm.begin(); it != mm.end(); ++it) {
            cout << "  " << it->first << " => " << it->second << endl;
        }
    }
    cout << endl;
}

int main() {
    cout << "=== C++ std::map 容器示例 ===" << endl << endl;
    
    // 1. 创建和初始化map
    cout << "1. 创建和初始化map:" << endl;
    
    // 空map
    map<string, int> map1;
    
    // 使用初始化列表
    map<string, int> map2;
    map2["Alice"] = 85;
    map2["Bob"] = 92;
    map2["Charlie"] = 78;
    map2["David"] = 95;
    printMap(map2, "map2 (初始化后)");
    
    // 拷贝构造函数
    map<string, int> map3(map2);
    printMap(map3, "map3 (拷贝map2)");
    
    // 使用迭代器范围构造
    map<string, int> map4(map2.begin(), map2.end());
    printMap(map4, "map4 (使用迭代器构造)");
    
    // 使用pair数组构造
    pair<string, int> pairs[3];
    pairs[0] = make_pair("Emma", 88);
    pairs[1] = make_pair("Frank", 79);
    pairs[2] = make_pair("Grace", 91);
    map<string, int> map5(pairs, pairs + 3);
    printMap(map5, "map5 (使用pair数组构造)");
    
    // 2. 插入元素
    cout << "2. 插入元素:" << endl;
    map<string, int> studentScores;
    
    // 方法1: insert + make_pair
    studentScores.insert(make_pair("Alice", 85));
    studentScores.insert(make_pair("Bob", 92));
    
    // 方法2: insert + pair构造函数
    studentScores.insert(pair<string, int>("Charlie", 78));
    
    // 方法3: operator[] (如果键不存在则插入，存在则修改值)
    studentScores["David"] = 95;
    studentScores["Emma"] = 88;
    studentScores["Frank"] = 79;
    studentScores["Alice"] = 90;  // 修改已存在的键
    
    printMap(studentScores, "studentScores (插入元素后)");
    
    // 插入返回值
    cout << "insert() 返回值测试:" << endl;
    pair<map<string, int>::iterator, bool> result = studentScores.insert(make_pair("Bob", 100));
    if (!result.second) {
        cout << "  插入失败，键 'Bob' 已存在，值为: " << result.first->second << endl;
    }
    
    result = studentScores.insert(make_pair("George", 87));
    if (result.second) {
        cout << "  插入成功，键 'George' 值为: " << result.first->second << endl;
    }
    
    printMap(studentScores, "studentScores (插入后最终状态)");
    
    // 3. 访问元素
    cout << "3. 访问元素:" << endl;
    
    // 使用operator[]
    cout << "Alice的分数: " << studentScores["Alice"] << endl;
    
    // 使用at() (会进行边界检查)
    try {
        cout << "Bob的分数: " << studentScores.at("Bob") << endl;
        cout << "不存在的键Tom: ";
        cout << studentScores.at("Tom") << endl;  // 抛出异常
    } catch (const out_of_range& e) {
        cout << "异常: " << e.what() << endl;
    }
    
    // 使用find()安全访问
    map<string, int>::iterator it = studentScores.find("Charlie");
    if (it != studentScores.end()) {
        cout << "Charlie的分数: " << it->second << endl;
    } else {
        cout << "未找到Charlie" << endl;
    }
    
    // 使用count()检查键是否存在
    cout << "David是否存在: " << (studentScores.count("David") > 0 ? "是" : "否") << endl;
    cout << "Tom是否存在: " << (studentScores.count("Tom") > 0 ? "是" : "否") << endl;
    cout << endl;
    
    // 4. 修改元素
    cout << "4. 修改元素:" << endl;
    
    // 方法1: 使用operator[]
    studentScores["Alice"] = 95;  // 修改已有键的值
    studentScores["Isaac"] = 82;  // 如果键不存在则插入
    
    // 方法2: 使用迭代器
    it = studentScores.find("Bob");
    if (it != studentScores.end()) {
        it->second = 98;  // 通过迭代器修改值
    }
    
    printMap(studentScores, "修改元素后");
    
    // 5. 删除元素
    cout << "5. 删除元素:" << endl;
    
    cout << "删除前大小: " << studentScores.size() << endl;
    
    // 方法1: 通过键删除
    size_t count = studentScores.erase("Frank");
    cout << "删除键'Frank': " << (count > 0 ? "成功" : "失败(键不存在)") << endl;
    
    // 方法2: 通过迭代器删除
    it = studentScores.find("George");
    if (it != studentScores.end()) {
        studentScores.erase(it);
        cout << "删除迭代器指向的元素" << endl;
    }
    
    // 方法3: 删除范围
    map<string, int>::iterator it1 = studentScores.find("Charlie");
    map<string, int>::iterator it2 = studentScores.find("Emma");
    if (it1 != studentScores.end() && it2 != studentScores.end()) {
        // 删除[Charlie, Emma)区间的元素
        studentScores.erase(it1, ++it2);
        cout << "删除[Charlie, Emma]区间的元素" << endl;
    }
    
    cout << "删除后大小: " << studentScores.size() << endl;
    printMap(studentScores, "删除元素后");
    
    // 清空map
    studentScores.clear();
    cout << "清空后大小: " << studentScores.size() << endl;
    cout << "map是否为空: " << (studentScores.empty() ? "是" : "否") << endl;
    cout << endl;
    
    // 6. 遍历map
    cout << "6. 遍历map:" << endl;
    
    // 重新填充数据
    map<string, int> scores;
    scores["Alice"] = 85;
    scores["Bob"] = 92;
    scores["Charlie"] = 78;
    scores["David"] = 95;
    scores["Emma"] = 88;
    scores["Frank"] = 79;
    
    cout << "方法1: 使用迭代器" << endl;
    for (map<string, int>::iterator it = scores.begin(); it != scores.end(); ++it) {
        cout << "  " << it->first << ": " << it->second << endl;
    }
    cout << endl;
    
    cout << "方法2: 使用基于范围的for循环" << endl;
    for (const pair<string, int>& item : scores) {
        cout << "  " << item.first << ": " << item.second << endl;
    }
    cout << endl;
    
    cout << "方法3: 使用const迭代器" << endl;
    for (map<string, int>::const_iterator cit = scores.begin(); cit != scores.end(); ++cit) {
        cout << "  " << cit->first << ": " << cit->second << endl;
    }
    cout << endl;
    
    cout << "方法4: 反向遍历" << endl;
    for (map<string, int>::reverse_iterator rit = scores.rbegin(); rit != scores.rend(); ++rit) {
        cout << "  " << rit->first << ": " << rit->second << endl;
    }
    cout << endl;
    
    // 7. 查找操作
    cout << "7. 查找操作:" << endl;
    printMap(scores, "原始数据");
    
    // find() - 查找特定键
    it = scores.find("David");
    if (it != scores.end()) {
        cout << "找到David: " << it->second << endl;
    }
    
    // lower_bound() - 第一个不小于给定键的元素
    map<string, int>::iterator lb = scores.lower_bound("C");
    if (lb != scores.end()) {
        cout << "lower_bound('C'): " << lb->first << " => " << lb->second << endl;
    }
    
    // upper_bound() - 第一个大于给定键的元素
    map<string, int>::iterator ub = scores.upper_bound("C");
    if (ub != scores.end()) {
        cout << "upper_bound('C'): " << ub->first << " => " << ub->second << endl;
    }
    
    // equal_range() - 返回匹配键的范围（对于map，键唯一，范围最多一个元素）
    pair<map<string, int>::iterator, map<string, int>::iterator> range = scores.equal_range("Emma");
    if (range.first != scores.end()) {
        cout << "equal_range('Emma'): ";
        for (map<string, int>::iterator r = range.first; r != range.second; ++r) {
            cout << r->first << " => " << r->second << " ";
        }
        cout << endl;
    }
    
    // 查找不存在的键
    it = scores.find("Zoe");
    if (it == scores.end()) {
        cout << "未找到Zoe" << endl;
    }
    cout << endl;
    
    // 8. 容量和大小
    cout << "8. 容量和大小:" << endl;
    cout << "scores大小: " << scores.size() << endl;
    cout << "scores最大大小: " << scores.max_size() << endl;
    cout << "scores是否为空: " << (scores.empty() ? "是" : "否") << endl;
    cout << endl;
    
    // 9. 自定义排序规则
    cout << "9. 自定义排序规则:" << endl;
    
    // 降序排序的map
    map<string, int, greater<string> > descendingMap;
    descendingMap["Apple"] = 10;
    descendingMap["Banana"] = 5;
    descendingMap["Cherry"] = 8;
    descendingMap["Date"] = 3;
    
    cout << "按键降序排序的map:" << endl;
    for (map<string, int, greater<string> >::iterator it = descendingMap.begin(); it != descendingMap.end(); ++it) {
        cout << "  " << it->first << " => " << it->second << endl;
    }
    cout << endl;
    
    // 10. 使用pair作为键的map
    cout << "10. 使用pair作为键的map:" << endl;
    
    // 使用pair作为键，需要提供比较函数
    map<pair<int, int>, string> coordinateMap;
    
    coordinateMap[make_pair(1, 1)] = "点A";
    coordinateMap[make_pair(2, 3)] = "点B";
    coordinateMap[make_pair(3, 2)] = "点C";
    coordinateMap[make_pair(1, 2)] = "点D";
    
    cout << "坐标点映射:" << endl;
    for (map<pair<int, int>, string>::iterator it = coordinateMap.begin(); it != coordinateMap.end(); ++it) {
        cout << "  (" << it->first.first << ", " << it->first.second << ") => " << it->second << endl;
    }
    
    // 查找坐标点
    pair<int, int> searchCoord = make_pair(2, 3);
    map<pair<int, int>, string>::iterator coordIt = coordinateMap.find(searchCoord);
    if (coordIt != coordinateMap.end()) {
        cout << "找到坐标(2, 3): " << coordIt->second << endl;
    }
    cout << endl;
    
    // 11. multimap示例（允许重复键）
    cout << "11. multimap示例 (允许重复键):" << endl;
    
    multimap<string, int> studentScoresMulti;
    studentScoresMulti.insert(make_pair("Alice", 85));
    studentScoresMulti.insert(make_pair("Bob", 92));
    studentScoresMulti.insert(make_pair("Alice", 90));  // 允许重复键
    studentScoresMulti.insert(make_pair("Alice", 88));  // 允许重复键
    studentScoresMulti.insert(make_pair("Charlie", 78));
    
    printMultiMap(studentScoresMulti, "studentScoresMulti (允许多个Alice)");
    
    // 查找所有"Alice"的记录
    cout << "查找所有Alice的成绩:" << endl;
    pair<multimap<string, int>::iterator, multimap<string, int>::iterator> rangeAlice = 
        studentScoresMulti.equal_range("Alice");
    for (multimap<string, int>::iterator it = rangeAlice.first; it != rangeAlice.second; ++it) {
        cout << "  " << it->first << ": " << it->second << endl;
    }
    
    // 统计特定键的数量
    cout << "Alice的记录数: " << studentScoresMulti.count("Alice") << endl;
    cout << endl;
    
    // 12. 实际应用案例
    cout << "12. 实际应用案例:" << endl;
    
    // 案例1: 单词频率统计
    cout << "案例1: 单词频率统计" << endl;
    vector<string> words;
    words.push_back("apple");
    words.push_back("banana");
    words.push_back("apple");
    words.push_back("orange");
    words.push_back("banana");
    words.push_back("apple");
    words.push_back("grape");
    
    map<string, int> wordCount;
    
    for (vector<string>::size_type i = 0; i < words.size(); ++i) {
        wordCount[words[i]]++;  // 如果键不存在，会自动插入并初始化为0，然后递增
    }
    
    cout << "单词频率:" << endl;
    for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it) {
        cout << "  " << it->first << ": " << it->second << " 次" << endl;
    }
    cout << endl;
    
    // 案例2: 电话簿
    cout << "案例2: 电话簿" << endl;
    map<string, string> phonebook;
    phonebook["Alice"] = "123-456-7890";
    phonebook["Bob"] = "234-567-8901";
    phonebook["Charlie"] = "345-678-9012";
    
    // 添加新联系人
    phonebook["David"] = "456-789-0123";
    
    // 查找电话
    string name = "Bob";
    map<string, string>::iterator phoneIt = phonebook.find(name);
    if (phoneIt != phonebook.end()) {
        cout << name << " 的电话是: " << phoneIt->second << endl;
    } else {
        cout << "未找到联系人: " << name << endl;
    }
    
    // 列出所有联系人
    cout << "\n电话簿中的所有联系人:" << endl;
    for (map<string, string>::iterator it = phonebook.begin(); it != phonebook.end(); ++it) {
        cout << "  " << it->first << ": " << it->second << endl;
    }
    cout << endl;
    
    // 案例3: 库存管理系统
    cout << "案例3: 库存管理系统" << endl;
    map<string, pair<int, double> > inventory;  // 商品名 -> (数量, 单价)
    
    // 使用make_pair初始化
    inventory["Apple"] = make_pair(50, 1.20);
    inventory["Banana"] = make_pair(30, 0.80);
    inventory["Orange"] = make_pair(40, 1.50);
    inventory["Grape"] = make_pair(25, 2.50);
    
    // 销售商品
    string product = "Apple";
    int soldQuantity = 10;
    
    map<string, pair<int, double> >::iterator inventoryIt = inventory.find(product);
    if (inventoryIt != inventory.end()) {
        // 不使用结构化绑定
        int& quantity = inventoryIt->second.first;
        double price = inventoryIt->second.second;
        
        if (quantity >= soldQuantity) {
            quantity -= soldQuantity;
            double total = soldQuantity * price;
            cout << "售出 " << soldQuantity << " 个 " << product 
                 << ", 单价: $" << price << ", 总价: $" << total << endl;
        } else {
            cout << "库存不足: " << product << " 只有 " << quantity << " 个" << endl;
        }
    } else {
        cout << "商品不存在: " << product << endl;
    }
    
    // 显示库存
    cout << "\n当前库存:" << endl;
    cout << "商品\t\t数量\t单价\t总价值" << endl;
    cout << "-----------------------------------" << endl;
    double totalValue = 0.0;
    for (map<string, pair<int, double> >::iterator it = inventory.begin(); it != inventory.end(); ++it) {
        const string& productName = it->first;
        int quantity = it->second.first;
        double price = it->second.second;
        double value = quantity * price;
        totalValue += value;
        cout << productName << "\t\t" << quantity << "\t$" << price << "\t$" << value << endl;
    }
    cout << "-----------------------------------" << endl;
    cout << "库存总价值: $" << totalValue << endl;
    
    cout << endl << "=== 示例结束 ===" << endl;
    
    return 0;
}