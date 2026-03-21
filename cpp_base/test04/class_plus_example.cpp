#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>

#ifdef _WIN32
#define COPY_STR(dest, size, src) strcpy_s(dest, size, src)
#else
#define COPY_STR(dest, size, src) strncpy(dest, src, size), dest[size-1] = '\0'
#endif
using namespace std;

class Person {
private:
    string name;
    int age;
    char* bio;
    static int instanceCount;

public:
    Person(const string& n, int a, const string& b = "") : name(n), age(a) {
        if (!b.empty()) {
            bio = new char[b.length() + 1];
            COPY_STR(bio, b.length() + 1, b.c_str());
        } else {
            bio = new char[1];
            COPY_STR(bio, 1, "");
        }
        ++instanceCount;
        cout << "构造 Person(" << name << ", " << age << ", \"" << bio << "\")\n";
    }

    Person() : name("unknown"), age(0) {
        bio = new char[1];
        COPY_STR(bio, 1, "");
        ++instanceCount;
    }

    Person(const Person& other) : name(other.name), age(other.age) {
        int len = strlen(other.bio);
        bio = new char[len + 1];
        COPY_STR(bio, len + 1, other.bio);
        ++instanceCount;
        cout << "拷贝构造 Person(" << name << ") - 深拷贝bio指针\n";
    }

    Person(Person&& other) noexcept : name(move(other.name)), age(other.age), bio(other.bio) {
        other.bio = nullptr;
        ++instanceCount;
        cout << "移动构造 Person - 移动bio所有权\n";
    }

    ~Person() {
        --instanceCount;
        cout << "析构 Person(" << name << ")\n";
        if (bio != nullptr) {
            delete[] bio;
            bio = nullptr;
        }
    }

    string getName() const { return name; }
    int getAge() const { return age; }
    string getBio() const { return bio ? string(bio) : ""; }

    void setAge(int a) { this->age = a; }
    
    void setBio(const string& b) {
        if (bio != nullptr) {
            delete[] bio;
        }
        bio = new char[b.length() + 1];
        COPY_STR(bio, b.length() + 1, b.c_str());
    }

    static int getInstanceCount() { return instanceCount; }

    // ============ 运算符重载 ============
    
    // 重载 == 运算符：比较两个 Person 对象是否相同
    bool operator==(const Person& other) const {
        return this->name == other.name && this->age == other.age;
    }

    // 重载 != 运算符
    bool operator!=(const Person& other) const {
        return !(*this == other);
    }

    // 重载 < 运算符：按年龄比较
    bool operator<(const Person& other) const {
        return this->age < other.age;
    }

    // 重载 > 运算符：按年龄比较
    bool operator>(const Person& other) const {
        return this->age > other.age;
    }

    // 重载 <= 运算符
    bool operator<=(const Person& other) const {
        return this->age <= other.age;
    }

    // 重载 >= 运算符
    bool operator>=(const Person& other) const {
        return this->age >= other.age;
    }

    // 重载 = 赋值运算符（深拷贝）
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            
            // 释放原有的动态内存
            if (bio != nullptr) {
                delete[] bio;
            }
            
            // 深拷贝 bio
            int len = strlen(other.bio);
            bio = new char[len + 1];
            COPY_STR(bio, len + 1, other.bio);
            
            cout << "赋值运算符: " << name << " 被赋值\n";
        }
        return *this;
    }

    // 重载 + 运算符：创建一个新 Person，年龄为原年龄加上指定年数
    Person operator+(int years) const {
        Person temp(name, age + years, bio);
        return temp;
    }

    // 重载 ++ 运算符（前置）：年龄增加1
    Person& operator++() {
        ++age;
        return *this;
    }

    // 重载 ++ 运算符（后置）：年龄增加1，返回修改前的值
    Person operator++(int) {
        Person temp = *this;
        age++;
        return temp;
    }

    // 重载 [] 运算符：访问 name 字符串中的第 i 个字符
    char operator[](int index) const {
        if (index >= 0 && index < (int)name.length()) {
            return name[index];
        }
        return '\0';
    }
};

int Person::instanceCount = 0;

// ============ 友元函数：重载输出流运算符 ============
ostream& operator<<(ostream& os, const Person& p) {
    os << "Person{name: " << p.getName() << ", age: " << p.getAge() << ", bio: " << p.getBio() << "}";
    return os;
}

// ============ 友元函数：重载输入流运算符 ============
istream& operator>>(istream& is, Person& p) {
    string name, bio;
    int age;
    
    cout << "输入姓名: ";
    is >> name;
    cout << "输入年龄: ";
    is >> age;
    cout << "输入个人介绍: ";
    is >> bio;
    
    p = Person(name, age, bio);
    return is;
}

int main() {
    cout << "===== 类中运算符重载示例 =====" << endl;

    Person p1("Alice", 30, "喜欢编程");
    Person p2("Bob", 25, "热爱运动");
    Person p3("Alice", 30, "喜欢编程");

    // 演示 == 和 != 运算符
    cout << "\n--- 重载 == 和 != 运算符 ---\n";
    cout << "p1 == p3: " << (p1 == p3 ? "true" : "false") << "\n";
    cout << "p1 != p2: " << (p1 != p2 ? "true" : "false") << "\n";

    // 演示比较运算符 <, >, <=, >=
    cout << "\n--- 重载比较运算符（按年龄比较）---\n";
    cout << "p1(" << p1.getAge() << "岁) < p2(" << p2.getAge() << "岁): " << (p1 < p2 ? "true" : "false") << "\n";
    cout << "p1 > p2: " << (p1 > p2 ? "true" : "false") << "\n";
    cout << "p2 <= p1: " << (p2 <= p1 ? "true" : "false") << "\n";

    // 演示 + 运算符：年龄加上指定的年数
    cout << "\n--- 重载 + 运算符 ---\n";
    cout << "p1 原年龄: " << p1.getAge() << "\n";
    Person p4 = p1 + 5;  // 创建一个年龄增加 5 岁的新 Person
    cout << "p1 + 5 后（新对象 p4）: " << p4.getAge() << "\n";
    cout << "p1 本身未改变: " << p1.getAge() << "\n";

    // 演示 = 赋值运算符（深拷贝）
    cout << "\n--- 重载 = 赋值运算符 ---\n";
    Person p5;
    p5 = p1;  // 调用赋值运算符
    cout << "赋值后 p5: " << p5 << "\n";

    // 演示前置 ++ 和后置 ++
    cout << "\n--- 重载 ++ 运算符 ---\n";
    cout << "p2 原年龄: " << p2.getAge() << "\n";
    Person p6 = p2++;  // 后置++：先返回旧值，再递增
    cout << "p6 = p2++（后置）: p6 年龄 = " << p6.getAge() << ", p2 年龄 = " << p2.getAge() << "\n";
    
    Person p7 = ++p2;  // 前置++：递增后再返回
    cout << "p7 = ++p2（前置）: p7 年龄 = " << p7.getAge() << ", p2 年龄 = " << p2.getAge() << "\n";

    // 演示 [] 运算符：访问名字中的字符
    cout << "\n--- 重载 [] 运算符 ---\n";
    cout << "p1 的名字: " << p1.getName() << "\n";
    cout << "p1[0] = " << p1[0] << "\n";
    cout << "p1[1] = " << p1[1] << "\n";
    cout << "p1[5] = " << (p1[5] == '\0' ? "\\0(越界)" : "有效") << "\n";

    // 演示重载的 << 运算符（输出）
    cout << "\n--- 重载 << 运算符 ---\n";
    cout << "p1 的信息: " << p1 << "\n";
    cout << "p2 的信息: " << p2 << "\n";

    cout << "\n===== 示例结束 =====" << endl;
    return 0;
}
