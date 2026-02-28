#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>  // 内置仿函数所在头文件

// ========== 1. 自定义仿函数示例 ==========

// 示例1：简单的仿函数 - 平方计算
class SquareFunctor {
public:
    int operator()(int x) const {
        return x * x;
    }
};

// 示例2：带状态的仿函数 - 累加器
class Accumulator {
private:
    int total;
public:
    Accumulator() : total(0) {}
    
    int operator()(int value) {
        total += value;
        return total;
    }
    
    int getTotal() const {
        return total;
    }
};

// 示例3：模板仿函数 - 比较器
template<typename T>
class IsGreaterThan {
private:
    T threshold;
public:
    IsGreaterThan(T t) : threshold(t) {}
    
    bool operator()(T value) const {
        return value > threshold;
    }
};

// 示例4：仿函数作为排序规则
class Person {
public:
    std::string name;
    int age;
    
    Person(std::string n, int a) : name(n), age(a) {}
};

// 按年龄升序排序的仿函数
class SortByAge {
public:
    bool operator()(const Person& p1, const Person& p2) const {
        return p1.age < p2.age;
    }
};

// ========== 2. 内置仿函数使用 ==========

void demonstrateBuiltinFunctors() {
    std::cout << "\n=== 内置仿函数示例 ===" << std::endl;
    
    // 算术运算仿函数
    std::plus<int> add;
    std::minus<int> subtract;
    std::multiplies<int> multiply;
    std::divides<int> divide;
    std::modulus<int> mod;
    
    std::cout << "plus(10, 5) = " << add(10, 5) << std::endl;
    std::cout << "minus(10, 5) = " << subtract(10, 5) << std::endl;
    std::cout << "multiplies(10, 5) = " << multiply(10, 5) << std::endl;
    std::cout << "divides(10, 5) = " << divide(10, 5) << std::endl;
    std::cout << "modulus(10, 3) = " << mod(10, 3) << std::endl;
    
    // 比较运算仿函数
    std::equal_to<int> equal;
    std::not_equal_to<int> not_equal;
    std::greater<int> greater;
    std::less<int> less;
    std::greater_equal<int> greater_equal;
    std::less_equal<int> less_equal;
    
    std::cout << "\n比较运算:" << std::endl;
    std::cout << "equal_to(5, 5) = " << equal(5, 5) << std::endl;
    std::cout << "greater(10, 5) = " << greater(10, 5) << std::endl;
    std::cout << "less(5, 10) = " << less(5, 10) << std::endl;
    
    // 逻辑运算仿函数
    std::logical_and<bool> logical_and;
    std::logical_or<bool> logical_or;
    std::logical_not<bool> logical_not;
    
    std::cout << "\n逻辑运算:" << std::endl;
    std::cout << "logical_and(true, false) = " << logical_and(true, false) << std::endl;
    std::cout << "logical_or(true, false) = " << logical_or(true, false) << std::endl;
    std::cout << "logical_not(true) = " << logical_not(true) << std::endl;
}

// ========== 3. 仿函数在STL算法中的应用 ==========

void demonstrateSTLAlgorithms() {
    std::cout << "\n=== STL算法中的仿函数应用 ===" << std::endl;
    
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // 使用内置仿函数排序（降序）
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    std::cout << "降序排序: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // 使用内置仿函数排序（升序）
    std::sort(numbers.begin(), numbers.end(), std::less<int>());
    std::cout << "升序排序: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // 使用自定义仿函数查找
    IsGreaterThan<int> isGreaterThan5(5);
    auto it = std::find_if(numbers.begin(), numbers.end(), isGreaterThan5);
    if (it != numbers.end()) {
        std::cout << "第一个大于5的元素: " << *it << std::endl;
    }
    
    // 使用内置算术仿函数进行转换
    std::vector<int> doubled(numbers.size());
    std::transform(numbers.begin(), numbers.end(), doubled.begin(),
                  std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    
    std::cout << "所有元素乘以2: ";
    for (int n : doubled) std::cout << n << " ";
    std::cout << std::endl;
}

// ========== 4. 综合示例 ==========

int main() {
    std::cout << "=== 自定义仿函数示例 ===" << std::endl;
    
    // 1. 基本仿函数使用
    SquareFunctor square;
    std::cout << "平方计算: square(5) = " << square(5) << std::endl;
    
    // 2. 带状态的仿函数
    Accumulator acc;
    std::vector<int> values = {1, 2, 3, 4, 5};
    for (int v : values) {
        acc(v);
    }
    std::cout << "累加总和: " << acc.getTotal() << std::endl;
    
    // 3. 模板仿函数
    IsGreaterThan<int> greaterThan3(3);
    std::cout << "greaterThan3(5): " << greaterThan3(5) << std::endl;
    std::cout << "greaterThan3(2): " << greaterThan3(2) << std::endl;
    
    // 4. 仿函数作为排序规则
    std::vector<Person> people = {
        Person("Alice", 25),
        Person("Bob", 30),
        Person("Charlie", 20),
        Person("David", 35)
    };
    
    std::sort(people.begin(), people.end(), SortByAge());
    
    std::cout << "\n按年龄排序的人员列表:" << std::endl;
    for (const auto& p : people) {
        std::cout << p.name << " (" << p.age << "岁)" << std::endl;
    }
    
    // 5. 演示内置仿函数
    demonstrateBuiltinFunctors();
    
    // 6. 演示STL算法中的仿函数
    demonstrateSTLAlgorithms();
    
    // 7. Lambda表达式作为仿函数的替代（C++11+）
    std::cout << "\n=== Lambda表达式示例 ===" << std::endl;
    auto cube = [](int x) { return x * x * x; };
    std::cout << "Lambda计算立方: cube(3) = " << cube(3) << std::endl;
    
    // 使用Lambda进行排序
    std::sort(people.begin(), people.end(), 
             [](const Person& a, const Person& b) {
                 return a.name < b.name;  // 按姓名排序
             });
    
    std::cout << "\n按姓名排序的人员列表:" << std::endl;
    for (const auto& p : people) {
        std::cout << p.name << " (" << p.age << "岁)" << std::endl;
    }
    
    return 0;
}