#include <iostream>
#include <string>
using namespace std;

// ===== 1. 返回基本类型 =====
// 返回整数
int addNumbers(int a, int b)
{
    return a + b;
}

// 返回浮点数
double divideNumbers(double a, double b)
{
    if(b == 0) return 0;
    return a / b;
}

// 返回字符
char getFirstChar(const string& str)
{
    return str.empty() ? '\0' : str[0];
}

// 返回布尔值
bool isEven(int num)
{
    return num % 2 == 0;
}

// ===== 2. 返回字符串（引用或值） =====
// 返回字符串的值拷贝
string greetUser(const string& name)
{
    return "Hello, " + name + "!";
}

// 返回字符串的常量引用（更高效）
const string& getConstantMessage()
{
    static const string msg = "This is a constant message";
    return msg;
}

// ===== 3. 返回指针 =====
// 返回指向新分配内存的指针
int* createArray(int size, int initialValue)
{
    int* arr = new int[size];
    for(int i = 0; i < size; ++i)
    {
        arr[i] = initialValue + i;
    }
    return arr;
}

// 返回指向静态变量的指针
const int* getStaticNumbers()
{
    static int numbers[] = {10, 20, 30, 40, 50};
    return numbers;
}

// 返回function pointer
int (*getOperationFunc(char op))(int, int)
{
    static auto add = [](int a, int b) { return a + b; };
    static auto subtract = [](int a, int b) { return a - b; };
    static auto multiply = [](int a, int b) { return a * b; };
    
    switch(op)
    {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        default: return add;
    }
}

// ===== 4. 返回引用 =====
// 返回常量引用（安全，只读）
const int& findMax(const int& a, const int& b)
{
    return a > b ? a : b;
}

// 返回非常量引用（可修改，需谨慎）
int& getGlobalCounter()
{
    static int counter = 0;  // static 保证生命周期足够长
    return counter;
}

// ===== 5. 返回结构体 =====
struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

struct Result
{
    bool success;
    string errorMsg;
    int value;
};

// 返回结构体值（会拷贝）
Point createPoint(double x, double y)
{
    return Point(x, y);
}

// 返回结构体，使用 static 缓存结果
const Point& getOrigin()
{
    static Point origin(0, 0);
    return origin;
}

// 返回带有状态的结构体
Result performDivision(double a, double b)
{
    Result res;
    if(b == 0)
    {
        res.success = false;
        res.errorMsg = "除数不能为零";
        res.value = 0;
    }
    else
    {
        res.success = true;
        res.errorMsg = "";
        res.value = static_cast<int>(a / b);
    }
    return res;
}

// ===== 6. 使用 static 的各种场景 =====

// 场景1：统计函数调用次数
int getCallCount()
{
    static int count = 0;
    return ++count;
}

// 场景2：延迟初始化
const int* getExpensiveResource()
{
    static int* resource = nullptr;
    if(resource == nullptr)
    {
        cout << "  [第一次调用] 初始化昂贵资源..." << endl;
        resource = new int[100];
        for(int i = 0; i < 100; ++i)
        {
            resource[i] = i * i;
        }
    }
    return resource;
}

// 场景3：记录最大值
int recordMaxValue(int value)
{
    static int maxVal = INT_MIN;
    if(value > maxVal)
    {
        maxVal = value;
    }
    return maxVal;
}

// 场景4：返回 static 数组
const int* getSequence(int* size)
{
    static int sequence[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    *size = 10;
    return sequence;
}

// ===== 7. 函数模板返回各种类型 =====
template<typename T>
T getDefault()
{
    return T();  // 调用类型 T 的默认构造函数
}

template<typename T>
T maxValue(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    cout << "===== 函数调用返回各类型值 + static 运用 =====" << endl;

    // 1. 返回基本类型
    cout << "\n===== 1. 返回基本类型 =====" << endl;
    cout << "addNumbers(15, 25) = " << addNumbers(15, 25) << endl;
    cout << "divideNumbers(100, 3) = " << divideNumbers(100, 3) << endl;
    cout << "getFirstChar(\"Hello\") = '" << getFirstChar("Hello") << "'" << endl;
    cout << "isEven(10) = " << (isEven(10) ? "true" : "false") << endl;
    cout << "isEven(11) = " << (isEven(11) ? "true" : "false") << endl;

    // 2. 返回字符串
    cout << "\n===== 2. 返回字符串 =====" << endl;
    cout << greetUser("Alice") << endl;
    cout << getConstantMessage() << endl;

    // 3. 返回指针
    cout << "\n===== 3. 返回指针 =====" << endl;
    int* arr = createArray(5, 10);
    cout << "createArray(5, 10): ";
    for(int i = 0; i < 5; ++i) cout << arr[i] << " ";
    cout << endl;
    delete[] arr;
    arr = nullptr;

    const int* staticNums = getStaticNumbers();
    cout << "getStaticNumbers(): ";
    for(int i = 0; i < 5; ++i) cout << staticNums[i] << " ";
    cout << endl;

    // 返回函数指针并调用
    cout << "getOperationFunc('+'）(10, 5) = " << getOperationFunc('+')(10, 5) << endl;
    cout << "getOperationFunc('-')(10, 5) = " << getOperationFunc('-')(10, 5) << endl;
    cout << "getOperationFunc('*')(10, 5) = " << getOperationFunc('*')(10, 5) << endl;

    // 4. 返回引用
    cout << "\n===== 4. 返回引用 =====" << endl;
    int x = 100, y = 50;
    const int& maxRef = findMax(x, y);
    cout << "findMax(100, 50) = " << maxRef << endl;

    // 通过引用修改 static 变量
    int& counterRef = getGlobalCounter();
    cout << "第1次调用 getGlobalCounter(): " << ++counterRef << endl;
    cout << "第2次调用 getGlobalCounter(): " << ++counterRef << endl;
    cout << "第3次调用 getGlobalCounter(): " << ++counterRef << endl;

    // 5. 返回结构体
    cout << "\n===== 5. 返回结构体 =====" << endl;
    Point p = createPoint(3.5, 4.5);
    cout << "createPoint(3.5, 4.5): (" << p.x << ", " << p.y << ")" << endl;

    const Point& origin = getOrigin();
    cout << "getOrigin(): (" << origin.x << ", " << origin.y << ")" << endl;

    Result res1 = performDivision(20, 4);
    cout << "performDivision(20, 4): success=" << (res1.success ? "true" : "false") 
         << ", value=" << res1.value << endl;

    Result res2 = performDivision(20, 0);
    cout << "performDivision(20, 0): success=" << (res2.success ? "true" : "false") 
         << ", error=" << res2.errorMsg << endl;

    // 6. static 的各种应用场景
    cout << "\n===== 6. static 关键字的应用 =====" << endl;

    // 场景1：调用计数
    cout << "getCallCount 演示：" << endl;
    for(int i = 0; i < 5; ++i)
    {
        cout << "  第 " << getCallCount() << " 次调用" << endl;
    }

    // 场景2：延迟初始化
    cout << "\ngetExpensiveResource 演示（延迟初始化）：" << endl;
    const int* res1_ptr = getExpensiveResource();
    cout << "  第一个元素: " << res1_ptr[0] << endl;
    const int* res2_ptr = getExpensiveResource();  // 不再初始化
    cout << "  第二个元素: " << res2_ptr[1] << endl;

    // 场景3：记录最大值
    cout << "\nrecordMaxValue 演示（记录最大值）：" << endl;
    cout << "  输入5，最大值: " << recordMaxValue(5) << endl;
    cout << "  输入15，最大值: " << recordMaxValue(15) << endl;
    cout << "  输入10，最大值: " << recordMaxValue(10) << endl;
    cout << "  输入20，最大值: " << recordMaxValue(20) << endl;

    // 场景4：返回 static 数组
    cout << "\ngetSequence 演示（static 数组）：" << endl;
    int seqSize = 0;
    const int* seq = getSequence(&seqSize);
    cout << "  偶数序列: ";
    for(int i = 0; i < seqSize; ++i) cout << seq[i] << " ";
    cout << endl;

    // 7. 函数模板
    cout << "\n===== 7. 函数模板返回各种类型 =====" << endl;
    cout << "maxValue(50, 100) = " << maxValue(50, 100) << endl;
    cout << "maxValue(3.14, 2.71) = " << maxValue(3.14, 2.71) << endl;
    cout << "maxValue('a', 'z') = " << maxValue('a', 'z') << endl;
    cout << "getDefault<int>() = " << getDefault<int>() << endl;
    cout << "getDefault<double>() = " << getDefault<double>() << endl;

    cout << "\n===== 示例结束 =====" << endl;
    return 0;
}
