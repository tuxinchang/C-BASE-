#include <iostream>
#include <string>
using namespace std;

// 虚基类示例
class Animal {
public:
    Animal(const string& n) : name(n) {}
    virtual ~Animal() {}
    virtual void speak() const = 0; // 纯虚函数
    string getName() const { return name; }
protected:
    string name;
};

class Dog : public Animal {
public:
    Dog(const string& n) : Animal(n) {}
    void speak() const override {
        cout << name << ": 汪汪!" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(const string& n) : Animal(n) {}
    void speak() const override {
        cout << name << ": 喵喵!" << endl;
    }
};

int main() {
    Animal* a1 = new Dog("小黑");
    Animal* a2 = new Cat("小花");

    cout << "虚基类指针调用虚函数：" << endl;
    a1->speak();
    a2->speak();

    delete a1;
    delete a2;
    return 0;
}


// ================= 虚继承案例 =================
class Base {
public:
    Base() { cout << "Base 构造\n"; }
    void show() { cout << "Base::show()\n"; }
    int value = 42;
};

class A : virtual public Base {
public:
    A() { cout << "A 构造\n"; }
    void showA() { cout << "A::showA()\n"; }
};

class B : virtual public Base {
public:
    B() { cout << "B 构造\n"; }
    void showB() { cout << "B::showB()\n"; }
};

class C : public A, public B {
public:
    C() { cout << "C 构造\n"; }
    void showC() { cout << "C::showC()\n"; }
};

void virtualInheritanceDemo() {
    cout << "\n===== 虚继承演示 =====\n";
    C obj;
    obj.show(); // 只继承一份 Base::show()
    cout << "obj.value = " << obj.value << endl; // 只继承一份 Base::value
    obj.showA();
    obj.showB();
    obj.showC();
}

int main_virtual() {
    virtualInheritanceDemo();
    return 0;
}


// ================= 多态虚函数案例 =================
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() const = 0; // 纯虚函数
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "画一个圆形" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "画一个矩形" << endl;
    }
};

void polymorphismDemo() {
    cout << "\n===== 多态虚函数演示 =====\n";
    Shape* shapes[2];
    shapes[0] = new Circle();
    shapes[1] = new Rectangle();
    for (int i = 0; i < 2; ++i) {
        shapes[i]->draw(); // 多态调用
        delete shapes[i];
    }
}

int main_poly() {
    polymorphismDemo();
    return 0;
}


// ================= 纯虚函数与抽象类案例 =================
class Device {
public:
    virtual ~Device() {}
    virtual void run() const = 0; // 纯虚函数，有一个纯虚函数的类称为抽象类，抽象类无法实例化
};

class Phone : public Device {
public:
    void run() const override {
        cout << "手机正在运行" << endl;
    }
};

class Computer : public Device {
public:
    void run() const override {
        cout << "电脑正在运行" << endl;
    }
};

void abstractClassDemo() {
    cout << "\n===== 抽象类与纯虚函数演示 =====\n";
    // Device d; // 错误：抽象类不能实例化
    Device* dev1 = new Phone();
    Device* dev2 = new Computer();
    dev1->run();
    dev2->run();
    delete dev1;
    delete dev2;
}

int main_abstract() {
    abstractClassDemo();
    return 0;
}


// ================= 虚析构与纯虚析构案例 =================
class BaseVirtual {
public:
    BaseVirtual() { cout << "BaseVirtual 构造\n"; }
    virtual ~BaseVirtual() { cout << "BaseVirtual 析构\n"; }
};

class DerivedVirtual : public BaseVirtual {
public:
    DerivedVirtual() { cout << "DerivedVirtual 构造\n"; }
    ~DerivedVirtual() override { cout << "DerivedVirtual 析构\n"; }
};

void virtualDestructorDemo() {
    cout << "\n===== 虚析构演示 =====\n";
    BaseVirtual* ptr = new DerivedVirtual();
    delete ptr; // 会先调用 DerivedVirtual 析构，再调用 BaseVirtual 析构
}

// 纯虚析构案例
class AbstractBase {
public:
    AbstractBase() { cout << "AbstractBase 构造\n"; }
    virtual ~AbstractBase() = 0; // 纯虚析构
};

AbstractBase::~AbstractBase() { cout << "AbstractBase 纯虚析构实现\n"; }

class Concrete : public AbstractBase {
public:
    Concrete() { cout << "Concrete 构造\n"; }
    ~Concrete() override { cout << "Concrete 析构\n"; }
};

void pureVirtualDestructorDemo() {
    cout << "\n===== 纯虚析构演示 =====\n";
    AbstractBase* ptr = new Concrete();
    delete ptr; // 会先调用 Concrete 析构，再调用 AbstractBase 纯虚析构
}

int main_destructor() {
    virtualDestructorDemo();
    pureVirtualDestructorDemo();
    return 0;
}
