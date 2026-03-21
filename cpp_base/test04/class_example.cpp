#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>  // 用于 strcpy_s/strncpy 和 strlen

#ifdef _WIN32
#define COPY_STR(dest, size, src) strcpy_s(dest, size, src)
#else
#define COPY_STR(dest, size, src) strncpy(dest, src, size), dest[size-1] = '\0'
#endif
using namespace std;

// 简单的类示例：Person
class Person {
    //属性成员默认是 private 的
private:
    string name;
    int age;
    char* bio;  // 指针成员：存储个人介绍
    static int instanceCount; // 静态成员：记录创建的Person数量

public:
    // 构造函数
    Person(const string& n, int a, const string& b = "") : name(n), age(a) {
        // 深拷贝示例：为指针分配内存
        if (!b.empty()) {
            bio = new char[b.length() + 1];
            COPY_STR(bio, b.length() + 1, b.c_str());  // 安全复制字符串
        } else {
            bio = new char[1];
            COPY_STR(bio, 1, "");
        }
        ++instanceCount;
        cout << "构造 Person(" << name << ", " << age << ", \"" << bio << "\")\n";
    }

    // 默认构造
    Person() : name("unknown"), age(0) {
        bio = new char[1];
        COPY_STR(bio, 1, "");
        ++instanceCount;
    }

    // 拷贝构造（深拷贝）- 这是深拷贝的关键，适用于变量存储在堆上的情况
    Person(const Person& other) : name(other.name), age(other.age) {
        // 深拷贝指针成员：不是简单复制指针，而是分配新内存并复制数据
        int len = strlen(other.bio);
        bio = new char[len + 1];
        COPY_STR(bio, len + 1, other.bio);
        
        ++instanceCount;
        cout << "拷贝构造 Person(" << name << ") - 深拷贝bio指针\n";
    }

    // 移动构造
    Person(Person&& other) noexcept : name(move(other.name)), age(other.age), bio(other.bio) {
        other.bio = nullptr;  // 移动后清空源对象的指针
        ++instanceCount;
        cout << "移动构造 Person - 移动bio所有权\n";
    }

    // 析构函数
    ~Person() {
        --instanceCount;
        cout << "析构 Person(" << name << ")\n";
        if (bio != nullptr) {
            delete[] bio;  // 释放动态分配的内存
            bio = nullptr;
        }
    }

    // const 成员函数（不会修改对象）
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

    // 静态成员函数，无法区分对象实例，只能访问静态成员变量
    static int getInstanceCount() { return instanceCount; }
    
    // 友元函数：允许非成员函数访问私有成员，除此之外，还有友元类、友元成员函数等不同类型的友元关系
    friend ostream& operator<<(ostream& os, const Person& p);
    friend void clearBio(Person& p);
};

int Person::instanceCount = 0; // 共有与私有静态成员初始化，若是public static成员，可以在主函数被直接访问到

// 友元函数定义：可以访问 Person 的私有成员
ostream& operator<<(ostream& os, const Person& p) {
    os << "Person(" << p.name << ", " << p.age << ", bio: " << (p.bio ? p.bio : "") << ")";
    return os;
}

void clearBio(Person& p) {
    if (p.bio != nullptr) {
        delete[] p.bio;
    }
    p.bio = new char[1];
    COPY_STR(p.bio, 1, "");
    cout << "clearBio: 已清空 " << p.name << " 的 bio\n";
}

// 运算符重载示例：Point
struct Point {
    double x, y;
    Point(double _x=0, double _y=0) : x(_x), y(_y) {}
};

Point operator+(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// 继承与多态示例：基类 Vehicle
class Vehicle {
public:
    virtual ~Vehicle() {}
    virtual void start() const {
        cout << "Vehicle 启动" << endl;
    }
    virtual void info() const {
        cout << "通用车辆" << endl;
    }
};

class Car : public Vehicle {
private:
    string model;
public:
    Car(const string& m) : model(m) {}
    void start() const override {
        cout << "Car(" << model << ") 启动发动机" << endl;
    }
    void info() const override {
        cout << "这是汽车，型号: " << model << endl;
    }
};

class Bicycle : public Vehicle {
public:
    void start() const override {
        cout << "Bicycle 用脚踏启动" << endl;
    }
    void info() const override {
        cout << "这是自行车" << endl;
    }
};

// 接收 const 引用并调用常成员函数的示例，
void printPersonInfo(const Person& p) {
    cout << "printPersonInfo: " << p.getName() << " " << p.getAge() << "岁, bio: " << p.getBio() << endl;
}
int main() {
    cout << "===== 类与对象示例 =====" << endl;

    // Person 使用 - 深拷贝演示
    {
        cout << "\n--- 深拷贝构造函数演示 ---\n";
        Person p1("Alice", 30, "喜欢编程");
        Person p2("Bob", 25, "热爱运动");
        cout << "当前 Person 实例数: " << Person::getInstanceCount() << "\n";

        // 拷贝与移动
        Person p3 = p1;              // 拷贝构造 - 深拷贝指针成员
        Person p4 = std::move(p2);   // 移动构造

        cout << "\n--- 修改原对象，拷贝对象不受影响 ---\n";
        cout << "p1 原始bio: " << p1.getBio() << "\n";
        cout << "p3 拷贝bio: " << p3.getBio() << "\n";
        
        p1.setBio("改变了bio内容");  // 修改原对象
        cout << "修改p1后:\n";
        cout << "p1 的bio: " << p1.getBio() << "\n";
        cout << "p3 的bio: " << p3.getBio() << " (不受影响 - 深拷贝!)\n";
        
        cout << "\np3 的信息: " << p3.getName() << " " << p3.getAge() << "岁 " << p3.getBio() << "\n";
        p3.setAge(31);
        cout << "修改后: " << p3.getName() << " " << p3.getAge() << "岁\n";
    } // 块结束，Person 对象被析构

    // 友元函数示例：非成员函数直接访问私有成员
    cout << "\n--- 友元函数示例 ---\n";
    Person p5("Dave", 40, "喜欢旅行");
    cout << p5 << "\n"; // 调用友元 operator<<
    clearBio(p5);          // 友元函数直接操作私有成员 bio
    cout << "clearBio 后: " << p5 << "\n";

    // 常函数示例：const 对象只能调用常成员函数
    cout << "\n--- 常函数（const 成员函数）示例 ---\n";
    const Person pc("Carol", 22, "喜欢音乐");
    printPersonInfo(pc); // 通过 const 引用调用常成员函数
    cout << "const 对象调用 getName(): " << pc.getName() << "\n";
    // pc.setAge(23); // 若取消注释，此行会编译错误：不能在 const 对象上调用非 const 成员函数

    cout << "离开作用域后 Person 实例数: " << Person::getInstanceCount() << "\n";

    // Point 运算符重载
    Point a{1.5, 2.5}, b{3.0, 4.0};
    Point c = a + b;
    cout << "Point 相加: " << a << " + " << b << " = " << c << "\n";

    // 继承与多态
    cout << "\n===== 继承与多态 =====" << endl;
    vector<unique_ptr<Vehicle>> park;
    park.push_back(unique_ptr<Car>(new Car("Model-X")));
    park.push_back(unique_ptr<Bicycle>(new Bicycle()));

    for(const auto& v : park) {
        v->info();
        v->start();
    }

    // 智能指针与多态示例：共享所有权
    shared_ptr<Vehicle> vcar = make_shared<Car>("SharedModel");
    vcar->info();

    cout << "\n===== 示例结束 =====" << endl;
    return 0;
}
