#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstdlib>
#include <ctime>

// 自定义数据类型
class Person {
public:
    std::string name;
    int age;
    
    Person(std::string n, int a) : name(n), age(a) {}
    
    // 用于排序的比较运算符
    bool operator<(const Person& other) const {
        return age < other.age;
    }
    
    // 用于输出
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << "(" << p.age << ")";
        return os;
    }
};

int main() {
    // 设置随机种子
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // 初始化测试数据
    std::vector<int> nums = {1, 2, 3, 4, 5, 2, 3, 1, 6, 7, 8, 9, 10};
    std::vector<int> nums2 = {10, 11, 12, 13, 14};
    std::vector<int> nums3 = {1, 3, 5, 7, 9};
    std::vector<int> nums4 = {2, 4, 6, 8, 10};
    
    std::cout << "原始数据 nums: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n\n";
    
    // =================== 1. for_each ===================
    // 功能: 对容器中每个元素执行操作
    // 参数: 起始迭代器, 结束迭代器, 操作函数
    std::cout << "1. for_each - 打印元素:\n";
    std::for_each(nums.begin(), nums.end(), [](int n) {
        std::cout << n * 2 << " ";
    });
    std::cout << "\n";
    
    // =================== 2. transform ===================
    // 功能: 将元素转换后存储到新容器
    // 参数: 源起始, 源结束, 目标起始, 转换函数
    std::vector<int> squared(nums.size());
    std::transform(nums.begin(), nums.end(), squared.begin(),
                   [](int n) { return n * n; });
    std::cout << "\n2. transform - 平方运算:\n";
    for (int n : squared) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 3. find ===================
    // 功能: 查找指定值
    // 参数: 起始迭代器, 结束迭代器, 查找值
    auto it = std::find(nums.begin(), nums.end(), 5);
    std::cout << "\n3. find - 查找元素5:\n";
    std::cout << (it != nums.end() ? "找到" : "未找到") << "\n";
    
    // =================== 4. find_if ===================
    // 功能: 按条件查找第一个元素
    // 参数: 起始迭代器, 结束迭代器, 条件函数
    auto it_if = std::find_if(nums.begin(), nums.end(),
                              [](int n) { return n > 7; });
    std::cout << "\n4. find_if - 第一个大于7的元素:\n";
    if (it_if != nums.end()) std::cout << *it_if << "\n";
    
    // =================== 5. adjacent_find ===================
    // 功能: 查找相邻的重复元素
    // 参数: 起始迭代器, 结束迭代器
    std::vector<int> adj_nums = {1, 2, 2, 3, 4, 4, 5};
    auto adj_it = std::adjacent_find(adj_nums.begin(), adj_nums.end());
    std::cout << "\n5. adjacent_find - 查找相邻重复:\n";
    std::cout << "第一个相邻重复: " << (adj_it != adj_nums.end() ? *adj_it : -1) << "\n";
    
    // =================== 6. binary_search ===================
    // 功能: 二分查找(容器必须已排序)
    // 参数: 起始迭代器, 结束迭代器, 查找值
    std::sort(nums.begin(), nums.end());
    bool found = std::binary_search(nums.begin(), nums.end(), 7);
    std::cout << "\n6. binary_search - 查找7:\n";
    std::cout << (found ? "找到" : "未找到") << "\n";
    
    // =================== 7. count ===================
    // 功能: 统计指定值出现次数
    // 参数: 起始迭代器, 结束迭代器, 统计值
    int cnt = std::count(nums.begin(), nums.end(), 2);
    std::cout << "\n7. count - 统计2出现次数:\n";
    std::cout << "出现次数: " << cnt << "\n";
    
    // =================== 8. count_if ===================
    // 功能: 统计满足条件的元素个数
    // 参数: 起始迭代器, 结束迭代器, 条件函数
    int cnt_if = std::count_if(nums.begin(), nums.end(),
                               [](int n) { return n % 2 == 0; });
    std::cout << "\n8. count_if - 统计偶数个数:\n";
    std::cout << "偶数个数: " << cnt_if << "\n";
    
    // =================== 9. sort ===================
    // 功能: 排序(默认升序)
    // 参数: 起始迭代器, 结束迭代器, [比较函数]
    std::vector<int> sort_nums = {5, 2, 8, 1, 9, 3};
    std::sort(sort_nums.begin(), sort_nums.end());
    std::cout << "\n9. sort - 升序排序:\n";
    for (int n : sort_nums) std::cout << n << " ";
    std::cout << "\n";
    
    // 自定义排序 - 降序
    std::sort(sort_nums.begin(), sort_nums.end(), std::greater<int>());
    std::cout << "   降序排序:\n";
    for (int n : sort_nums) std::cout << n << " ";
    std::cout << "\n";
    
    // Person类排序
    std::vector<Person> people = {
        Person("Alice", 25),
        Person("Bob", 20),
        Person("Charlie", 30)
    };
    std::sort(people.begin(), people.end());
    std::cout << "   Person按年龄排序:\n";
    for (auto& p : people) std::cout << p << " ";
    std::cout << "\n";
    
    // =================== 10. random_shuffle ===================
    // 功能: 随机打乱元素顺序(C++14后用shuffle替代)
    // 参数: 起始迭代器, 结束迭代器
    std::vector<int> shuffle_nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::random_shuffle(shuffle_nums.begin(), shuffle_nums.end());
    std::cout << "\n10. random_shuffle - 随机打乱:\n";
    for (int n : shuffle_nums) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 11. merge ===================
    // 功能: 合并两个已排序序列
    // 参数: 序列1起始, 序列1结束, 序列2起始, 序列2结束, 目标起始
    std::vector<int> merged(nums3.size() + nums4.size());
    std::sort(nums3.begin(), nums3.end());
    std::sort(nums4.begin(), nums4.end());
    std::merge(nums3.begin(), nums3.end(),
               nums4.begin(), nums4.end(),
               merged.begin());
    std::cout << "\n11. merge - 合并两个有序数组:\n";
    for (int n : merged) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 12. reverse ===================
    // 功能: 反转容器元素顺序
    // 参数: 起始迭代器, 结束迭代器
    std::vector<int> reverse_nums = {1, 2, 3, 4, 5};
    std::reverse(reverse_nums.begin(), reverse_nums.end());
    std::cout << "\n12. reverse - 反转数组:\n";
    for (int n : reverse_nums) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 13. copy ===================
    // 功能: 复制序列到目标位置
    // 参数: 源起始, 源结束, 目标起始
    std::vector<int> copy_target(5);
    std::copy(reverse_nums.begin(), reverse_nums.begin() + 5, copy_target.begin());
    std::cout << "\n13. copy - 复制前5个元素:\n";
    for (int n : copy_target) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 14. replace ===================
    // 功能: 替换所有等于指定值的元素
    // 参数: 起始迭代器, 结束迭代器, 旧值, 新值
    std::vector<int> replace_nums = {1, 2, 3, 2, 5, 2};
    std::replace(replace_nums.begin(), replace_nums.end(), 2, 99);
    std::cout << "\n14. replace - 替换2为99:\n";
    for (int n : replace_nums) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 15. replace_if ===================
    // 功能: 替换满足条件的元素
    // 参数: 起始迭代器, 结束迭代器, 条件函数, 新值
    std::replace_if(replace_nums.begin(), replace_nums.end(),
                    [](int n) { return n < 10; }, 0);
    std::cout << "\n15. replace_if - 替换小于10的为0:\n";
    for (int n : replace_nums) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 16. swap ===================
    // 功能: 交换两个值或容器
    // 参数: 值1, 值2 或 容器1, 容器2
    int a = 10, b = 20;
    std::swap(a, b);
    std::cout << "\n16. swap - 交换两个值:\n";
    std::cout << "a=" << a << ", b=" << b << "\n";
    
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    std::swap(v1, v2);
    std::cout << "   交换两个向量:\nv1: ";
    for (int n : v1) std::cout << n << " ";
    std::cout << "\nv2: ";
    for (int n : v2) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 17. accumulate ===================
    // 功能: 计算序列累计值(需包含<numeric>)
    // 参数: 起始迭代器, 结束迭代器, 初始值, [操作函数]
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "\n17. accumulate - 计算总和:\n";
    std::cout << "总和: " << sum << "\n";
    
    int product = std::accumulate(nums.begin(), nums.end(), 1,
                                  std::multiplies<int>());
    std::cout << "   计算乘积: " << product << "\n";
    
    // =================== 18. fill ===================
    // 功能: 用指定值填充容器
    // 参数: 起始迭代器, 结束迭代器, 填充值
    std::vector<int> filled(5);
    std::fill(filled.begin(), filled.end(), 42);
    std::cout << "\n18. fill - 填充值为42:\n";
    for (int n : filled) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 19. set_intersection ===================
    // 功能: 求两个有序集合的交集(需包含<algorithm>)
    // 参数: 集合1起始, 集合1结束, 集合2起始, 集合2结束, 目标起始
    std::vector<int> set1 = {1, 2, 3, 4, 5};
    std::vector<int> set2 = {3, 4, 5, 6, 7};
    std::vector<int> intersection(std::max(set1.size(), set2.size()));
    
    auto inter_end = std::set_intersection(set1.begin(), set1.end(),
                                           set2.begin(), set2.end(),
                                           intersection.begin());
    intersection.resize(inter_end - intersection.begin());
    
    std::cout << "\n19. set_intersection - 交集:\n";
    for (int n : intersection) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 20. set_union ===================
    // 功能: 求两个有序集合的并集
    // 参数: 集合1起始, 集合1结束, 集合2起始, 集合2结束, 目标起始
    std::vector<int> union_set(set1.size() + set2.size());
    auto union_end = std::set_union(set1.begin(), set1.end(),
                                    set2.begin(), set2.end(),
                                    union_set.begin());
    union_set.resize(union_end - union_set.begin());
    
    std::cout << "\n20. set_union - 并集:\n";
    for (int n : union_set) std::cout << n << " ";
    std::cout << "\n";
    
    // =================== 21. set_difference ===================
    // 功能: 求两个有序集合的差集(A-B)
    // 参数: 集合1起始, 集合1结束, 集合2起始, 集合2结束, 目标起始
    std::vector<int> difference(set1.size());
    auto diff_end = std::set_difference(set1.begin(), set1.end(),
                                        set2.begin(), set2.end(),
                                        difference.begin());
    difference.resize(diff_end - difference.begin());
    
    std::cout << "\n21. set_difference - 差集(set1-set2):\n";
    for (int n : difference) std::cout << n << " ";
    std::cout << "\n";
    
    return 0;
}