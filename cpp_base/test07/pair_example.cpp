#include <iostream>
#include <utility>   // pair定义在<utility>中
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>     // 用于tuple比较
#include <set>

using namespace std;

// 打印pair的辅助函数
template<typename T1, typename T2>
void printPair(const pair<T1, T2>& p, const string& description = "") {
    if (!description.empty()) {
        cout << description << ": ";
    }
    cout << "(" << p.first << ", " << p.second << ")";
}

int main() {
    cout << "=== C++ std::pair 对组示例 ===" << endl << endl;
    
    // 1. 创建和初始化pair
    cout << "1. 创建和初始化pair:" << endl;
    
    // 方法1: 直接初始化
    pair<int, string> p1(1, "Alice");
    printPair(p1, "p1");
    cout << endl;
    
    // 方法2: 使用make_pair函数
    auto p2 = make_pair(2, "Bob");
    printPair(p2, "p2");
    cout << endl;
    
    // 方法3: 使用花括号初始化
    pair<int, string> p3 = {3, "Charlie"};
    printPair(p3, "p3");
    cout << endl;
    
    // 方法4: 默认构造函数
    pair<int, string> p4;
    p4.first = 4;
    p4.second = "David";
    printPair(p4, "p4");
    cout << endl;
    
    // 方法5: 拷贝构造函数
    pair<int, string> p5(p1);
    printPair(p5, "p5 (复制p1)");
    cout << endl;
    
    // 方法6: 赋值操作
    pair<int, string> p6;
    p6 = p2;
    printPair(p6, "p6 (赋值p2)");
    cout << endl << endl;
    
    // 2. 访问pair元素
    cout << "2. 访问pair元素:" << endl;
    pair<string, double> product = {"Apple", 3.99};
    
    cout << "商品名称: " << product.first << endl;
    cout << "商品价格: " << product.second << endl;
    
    // 使用结构化绑定 (C++17)
    cout << "使用结构化绑定: ";
    auto [name, price] = product;
    cout << name << " - $" << price << endl;
    cout << endl;
    
    // 3. pair比较操作
    cout << "3. pair比较操作 (按字典序):" << endl;
    pair<int, int> a = {1, 2};
    pair<int, int> b = {1, 3};
    pair<int, int> c = {2, 1};
    pair<int, int> d = {1, 2};
    
    printPair(a, "a");
    cout << " < ";
    printPair(b, "");
    cout << ": " << (a < b) << endl;
    
    printPair(a, "a");
    cout << " < ";
    printPair(c, "");
    cout << ": " << (a < c) << endl;
    
    printPair(a, "a");
    cout << " == ";
    printPair(d, "");
    cout << ": " << (a == d) << endl;
    
    printPair(b, "b");
    cout << " > ";
    printPair(c, "");
    cout << ": " << (b > c) << endl;
    cout << endl;
    
    // 4. 不同类型元素的pair
    cout << "4. 不同类型元素的pair:" << endl;
    
    // 整数和浮点数
    pair<int, double> numericPair = {10, 3.14159};
    cout << "整数: " << numericPair.first << ", 浮点数: " << numericPair.second << endl;
    
    // 字符串和布尔值
    pair<string, bool> statusPair = {"连接成功", true};
    cout << "状态: " << statusPair.first << ", 结果: " << (statusPair.second ? "是" : "否") << endl;
    
    // 嵌套pair
    pair<pair<int, int>, string> nestedPair = {{10, 20}, "坐标"};
    cout << "嵌套pair: ((" << nestedPair.first.first << ", " << nestedPair.first.second 
         << "), " << nestedPair.second << ")" << endl;
    
    // pair的pair
    pair<pair<string, int>, pair<double, bool>> complexPair = {{"年龄", 25}, {98.5, true}};
    cout << "复杂pair: ";
    printPair(complexPair.first, "");
    cout << " + ";
    printPair(complexPair.second, "");
    cout << endl << endl;
    
    // 5. pair与容器的结合使用
    cout << "5. pair与容器的结合使用:" << endl;
    
    // vector of pairs
    cout << "a) vector<pair<int, string>>:" << endl;
    vector<pair<int, string>> students = {
        {101, "Alice"},
        {102, "Bob"},
        {103, "Charlie"},
        {104, "David"}
    };
    
    for (const auto& student : students) {
        printPair(student);
        cout << " ";
    }
    cout << endl << endl;
    
    // map本质上就是pair的集合
    cout << "b) map<int, string> (存储为pair):" << endl;
    map<int, string> studentMap;
    studentMap.insert({201, "Emma"});
    studentMap.insert(make_pair(202, "Frank"));
    studentMap.insert(pair<int, string>(203, "Grace"));
    studentMap[204] = "Henry";
    
    for (const auto& entry : studentMap) {
        // map中的元素就是pair
        cout << "学号: " << entry.first << ", 姓名: " << entry.second << endl;
    }
    cout << endl;
    
    // set of pairs (需要自定义比较函数或pair已经支持比较)
    cout << "c) set<pair<int, string>>:" << endl;
    set<pair<int, string>> studentSet;
    studentSet.insert({301, "Ivy"});
    studentSet.insert({302, "Jack"});
    studentSet.insert({301, "Ivy"}); // 重复，不会被插入
    studentSet.insert({300, "Zoe"});
    
    for (const auto& student : studentSet) {
        printPair(student);
        cout << " ";
    }
    cout << endl << endl;
    
    // 6. pair作为函数返回值
    cout << "6. pair作为函数返回值:" << endl;
    
    // 函数返回两个值的最小值和最大值
    auto findMinMax = [](const vector<int>& nums) -> pair<int, int> {
        if (nums.empty()) return {0, 0};
        int minVal = nums[0], maxVal = nums[0];
        for (int num : nums) {
            if (num < minVal) minVal = num;
            if (num > maxVal) maxVal = num;
        }
        return {minVal, maxVal};
    };
    
    vector<int> numbers = {5, 2, 8, 1, 9, 3, 7};
    auto [minNum, maxNum] = findMinMax(numbers);
    cout << "数组: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    cout << "最小值: " << minNum << ", 最大值: " << maxNum << endl;
    cout << endl;
    
    // 7. pair与算法结合
    cout << "7. pair与算法结合:" << endl;
    
    // 使用pair存储索引和值
    vector<int> values = {10, 30, 20, 50, 40};
    vector<pair<int, int>> indexedValues;
    
    for (int i = 0; i < values.size(); ++i) {
        indexedValues.emplace_back(i, values[i]);
    }
    
    cout << "索引-值对: ";
    for (const auto& iv : indexedValues) {
        printPair(iv);
        cout << " ";
    }
    cout << endl;
    
    // 按值排序（保持索引信息）
    sort(indexedValues.begin(), indexedValues.end(), 
         [](const pair<int, int>& a, const pair<int, int>& b) {
             return a.second < b.second; // 按值升序排序
         });
    
    cout << "按值排序后: ";
    for (const auto& iv : indexedValues) {
        printPair(iv);
        cout << " ";
    }
    cout << endl;
    
    // 查找特定值
    auto it = find_if(indexedValues.begin(), indexedValues.end(),
                      [](const pair<int, int>& p) { return p.second == 30; });
    if (it != indexedValues.end()) {
        cout << "找到值30，在原数组中的索引: " << it->first << endl;
    }
    cout << endl;
    
    // 8. pair的高级操作
    cout << "8. pair的高级操作:" << endl;
    
    // tie (C++11) - 将pair解包到多个变量
    pair<string, int> person = {"John", 30};
    string personName;
    int personAge;
    tie(personName, personAge) = person;
    cout << "使用tie解包: 姓名=" << personName << ", 年龄=" << personAge << endl;
    
    // pair交换
    pair<int, string> pairA = {1, "A"};
    pair<int, string> pairB = {2, "B"};
    cout << "交换前: ";
    printPair(pairA);
    cout << ", ";
    printPair(pairB);
    cout << endl;
    
    swap(pairA, pairB);
    cout << "交换后: ";
    printPair(pairA);
    cout << ", ";
    printPair(pairB);
    cout << endl;
    
    // pair与tuple的互操作
    tuple<int, string> t = {100, "Tuple"};
    pair<int, string> pFromTuple = {get<0>(t), get<1>(t)};
    cout << "从tuple创建pair: ";
    printPair(pFromTuple);
    cout << endl;
    
    // 9. 实际应用案例
    cout << endl << "9. 实际应用案例:" << endl;
    
    // 案例1: 学生成绩管理系统
    cout << "案例1: 学生成绩管理系统" << endl;
    vector<pair<string, pair<double, double>>> studentGrades = {
        {"Alice", {85.5, 90.0}},
        {"Bob", {78.0, 82.5}},
        {"Charlie", {92.0, 88.5}}
    };
    
    for (const auto& record : studentGrades) {
        cout << "学生: " << record.first 
             << ", 成绩1: " << record.second.first 
             << ", 成绩2: " << record.second.second 
             << ", 平均: " << (record.second.first + record.second.second) / 2 
             << endl;
    }
    cout << endl;
    
    // 案例2: 坐标系统
    cout << "案例2: 坐标系统" << endl;
    using Point = pair<int, int>;
    Point origin = {0, 0};
    Point pA = {3, 4};
    Point pB = {-2, 5};
    
    auto distanceSquared = [](const Point& a, const Point& b) {
        int dx = a.first - b.first;
        int dy = a.second - b.second;
        return dx*dx + dy*dy;
    };
    
    cout << "点A: ";
    printPair(pA);
    cout << endl;
    cout << "点B: ";
    printPair(pB);
    cout << endl;
    cout << "A到原点的距离平方: " << distanceSquared(pA, origin) << endl;
    cout << "A到B的距离平方: " << distanceSquared(pA, pB) << endl;
    cout << endl;
    
    // 案例3: 键值对解析
    cout << "案例3: 键值对解析" << endl;
    vector<pair<string, string>> config = {
        {"host", "localhost"},
        {"port", "8080"},
        {"timeout", "30"},
        {"debug", "true"}
    };
    
    cout << "配置参数:" << endl;
    for (const auto& [key, value] : config) {
        cout << "  " << key << " = " << value << endl;
    }
    
    // 查找特定配置
    string searchKey = "port";
    auto configIt = find_if(config.begin(), config.end(),
                           [&searchKey](const pair<string, string>& item) {
                               return item.first == searchKey;
                           });
    if (configIt != config.end()) {
        cout << "找到配置项 " << searchKey << ": " << configIt->second << endl;
    }
    
    cout << endl << "=== 示例结束 ===" << endl;
    
    return 0;
}