#include <iostream>
using namespace std;

// ===== 1. 基本函数定义与调用 =====
int add(int a, int b)
{
    return a + b;
}

// ===== 2. 函数的参数传递方式 =====

// 值传递：函数获得参数的拷贝
void modifyByValue(int x)
{
    x = 100;  // 只修改函数内的拷贝
}

// 指针传递：可以修改原数据
void modifyByPointer(int* p)
{
    if(p)
    {
        *p = 200;  // 修改指针指向的数据
    }
}

// 引用传递：通过引用修改原数据
void modifyByReference(int& ref)
{
    ref = 300;  // 修改引用所关联的变量
}

// ===== 3. 函数的返回值 =====
// 返回值为指针（需要谨慎，避免野指针）
int* createArray(int size)
{
    int* arr = new int[size];
    for(int i = 0; i < size; ++i)
    {
        arr[i] = i * 10;
    }
    return arr;
}

// 返回引用（需要确保引用对象有效期足够长）
const int& findMax(const int& a, const int& b)
{
    return a > b ? a : b;
}

// ===== 4. 函数重载 =====
// 同名函数，但参数不同
void print(int x)
{
    cout << "整数: " << x << endl;
}

void print(double x)
{
    cout << "浮点数: " << x << endl;
}

void print(const char* str)
{
    cout << "字符串: " << str << endl;
}

// ===== 5. 默认参数 =====
void greet(const char* name = "Guest", int times = 1)
{
    for(int i = 0; i < times; ++i)
    {
        cout << "Hello, " << name << "!" << endl;
    }
}

// ===== 6. 递归函数 =====
int factorial(int n)
{
    if(n <= 1) return 1;
    return n * factorial(n - 1);
}

// 斐波那契数列
int fibonacci(int n)
{
    if(n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ===== 7. 指向函数的指针 =====
int multiply(int a, int b)
{
    return a * b;
}

// 使用函数指针作为参数
int operate(int a, int b, int (*op)(int, int))
{
    if(op)
    {
        return op(a, b);
    }
    return 0;
}

// ===== 8. 函数模板 =====
template<typename T>
T max_value(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    cout << "===== 函数调用示例 =====" << endl;

    // 1. 基本函数调用
    cout << "\n===== 1. 基本函数调用 =====" << endl;
    int result = add(10, 20);
    cout << "add(10, 20) = " << result << endl;

    // 2. 参数传递方式的区别
    cout << "\n===== 2. 三种参数传递方式 =====" << endl;
    int num = 50;
    cout << "原始值: " << num << endl;

    modifyByValue(num);
    cout << "值传递后: " << num << " (未改变)" << endl;

    modifyByPointer(&num);
    cout << "指针传递后: " << num << " (改为200)" << endl;

    modifyByReference(num);
    cout << "引用传递后: " << num << " (改为300)" << endl;

    // 3. 返回值和指针
    cout << "\n===== 3. 返回指针与引用 =====" << endl;
    int* dynArr = createArray(5);
    cout << "动态数组内容: ";
    for(int i = 0; i < 5; ++i)
    {
        cout << dynArr[i] << " ";
    }
    cout << endl;
    delete[] dynArr;
    dynArr = nullptr;

    // 返回引用
    int a = 100, b = 200;
    const int& maxVal = findMax(a, b);
    cout << "max(" << a << ", " << b << ") = " << maxVal << endl;

    // 4. 函数重载
    cout << "\n===== 4. 函数重载 =====" << endl;
    print(42);           // 调用 print(int)
    print(3.14);         // 调用 print(double)
    print("Hello");      // 调用 print(char*)

    // 5. 默认参数
    cout << "\n===== 5. 默认参数 =====" << endl;
    greet();             // 使用所有默认值
    greet("Alice");      // 使用第二个默认值
    greet("Bob", 3);     // 不使用默认值

    // 6. 递归函数
    cout << "\n===== 6. 递归函数 =====" << endl;
    cout << "5的阶乘: " << factorial(5) << endl;
    cout << "第6个斐波那契数: " << fibonacci(6) << endl;

    // 7. 函数指针
    cout << "\n===== 7. 函数指针 =====" << endl;
    int (*funcPtr)(int, int) = multiply;  // 定义函数指针
    cout << "通过函数指针调用 multiply(7, 8) = " << funcPtr(7, 8) << endl;

    // 使用函数指针作为参数
    cout << "operate(5, 3, add) = " << operate(5, 3, add) << endl;
    cout << "operate(5, 3, multiply) = " << operate(5, 3, multiply) << endl;

    // 8. 函数模板
    cout << "\n===== 8. 函数模板 =====" << endl;
    cout << "max_value(50, 100) = " << max_value(50, 100) << endl;
    cout << "max_value(3.14, 2.71) = " << max_value(3.14, 2.71) << endl;
    cout << "max_value('a', 'z') = " << max_value('a', 'z') << endl;

    // 9. 传入数组作为参数的示例
    cout << "\n===== 9. 传入数组作为参数 =====" << endl;

    // 函数声明放在文件顶部也可；这里直接定义一个简单示例函数（在本文件中）
    auto printArray = [](const int arr[], int size)
    {
        for(int i = 0; i < size; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    };

    auto incrementArray = [](int arr[], int size)
    {
        for(int i = 0; i < size; ++i) arr[i]++;
    };

    int data[] = {10, 20, 30, 40};
    int len = sizeof(data) / sizeof(data[0]);

    cout << "原数组: "; printArray(data, len);
    // 传入数组名，函数接收为指针（数组会退化为指针）
    incrementArray(data, len);
    cout << "incrementArray 后: "; printArray(data, len);

    // 也可以传入数组的指针形式
    cout << "通过 &data[0] 传入: "; printArray(&data[0], len);


        // 10. 栈帧与函数调用链
        cout << "\n===== 10. 函数调用链 =====" << endl;
        cout << "链式调用: add(add(1, 2), add(3, 4)) = " 
            << add(add(1, 2), add(3, 4)) << endl;

        cout << "\n===== 函数调用示例结束 =====" << endl;
        return 0;
}
