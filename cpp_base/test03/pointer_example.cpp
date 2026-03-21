#include <iostream>
using namespace std;

int main()
{
    // ===== 1. 基本指针声明和初始化 =====
    int num = 42;
    int* ptr = &num;  // 声明一个指向int的指针，初始化为num的地址
    
    cout << "===== 基本指针操作 =====" << endl;
    cout << "变量值: " << num << endl;
    cout << "指针指向的值: " << *ptr << endl;  // 解引用：获取指针指向的值
    cout << "变量的地址: " << &num << endl;
    cout << "指针本身的值(地址): " << ptr << endl;
    
    // ===== 2. 通过指针修改值 =====
    cout << "\n===== 通过指针修改值 =====" << endl;
    *ptr = 100;  // 通过指针修改num的值
    cout << "修改后的num: " << num << endl;
    cout << "指针指向的值: " << *ptr << endl;
    
    // ===== 3. 指针的地址 =====
    cout << "\n===== 指针本身的地址 =====" << endl;
    cout << "指针的地址: " << &ptr << endl;
    
    // ===== 4. 多个指针指向同一个变量 =====
    cout << "\n===== 多个指针指向同一个变量 =====" << endl;
    int* ptr2 = &num;
    *ptr2 = 200;
    cout << "通过ptr修改: num = " << *ptr << endl;
    cout << "通过ptr2修改: num = " << *ptr2 << endl;
    cout << "num的实际值: " << num << endl;
    
    // ===== 5. 动态内存分配 =====
    cout << "\n===== 动态内存分配 =====" << endl;
    int* dynamicPtr = new int;        // 动态分配内存
    *dynamicPtr = 88;
    cout << "动态分配的值: " << *dynamicPtr << endl;
    cout << "动态分配的地址: " << dynamicPtr << endl;
    delete dynamicPtr;                // 释放内存，很重要！
    dynamicPtr = nullptr;             // 养成好习惯：释放后置空
    
    // ===== 6. 指针数组 =====
    cout << "\n===== 指针数组 =====" << endl;
    int a = 10, b = 20, c = 30;
    int* ptrArr[3] = {&a, &b, &c};    // 存储多个指针
    
    for(int i = 0; i < 3; i++)
    {
        cout << "第" << i << "个指针指向的值: " << *ptrArr[i] << endl;
    }
    
    // ===== 7. 指针作为函数参数 =====
    cout << "\n===== 指针作为函数参数 =====" << endl;
    int value = 5;
    cout << "函数调用前: value = " << value << endl;
    
    // 简单的指针传递示例
    int* printPtr = &value;
    cout << "通过指针访问: " << *printPtr << endl;
    
    // ===== 8. 空指针（NULL指针）=====
    cout << "\n===== 空指针的使用 =====" << endl;
    int* nullPtr = nullptr;           // 正确的初始化方式
    cout << "空指针初始化: " << nullPtr << endl;
    
    // 检查指针是否为空 - 这是非常重要的习惯
    if(nullPtr == nullptr)
    {
        cout << "警告：指针为空，不能解引用！" << endl;
    }
    
    // 错误做法示例（注释掉，避免程序崩溃）
    // if(nullPtr != nullptr)
    // {
    //     cout << *nullPtr << endl;  // 这会导致程序崩溃！
    // }
    
    // ===== 9. 野指针（Dangling Pointer）=====
    cout << "\n===== 野指针的危害 =====" << endl;
    
    // 情况1：释放后仍然使用指针
    int* wildPtr1 = new int(55);
    cout << "释放前: " << *wildPtr1 << endl;
    delete wildPtr1;
    // wildPtr1现在是野指针，指向已释放的内存
    cout << "指针地址（释放后）: " << wildPtr1 << endl;
    // 不要这样做：cout << *wildPtr1 << endl;  // 危险！
    wildPtr1 = nullptr;  // 释放后立即置空是好习惯
    
    // 情况2：未初始化的指针（最常见的错误）
    int* uninitPtr;  // 这是一个野指针，包含随机地址
    cout << "\n未初始化指针的地址（随机值）: " << uninitPtr << endl;
    // 不要这样做：*uninitPtr = 100;  // 危险！可能写入任意内存
    
    // 情况3：指针指向超出作用域的变量
    cout << "\n情况3：作用域问题" << endl;
    int* scopePtr;
    {
        int tempVar = 99;
        scopePtr = &tempVar;  // 指向局部变量
        cout << "在作用域内: " << *scopePtr << endl;
    }  // tempVar被销毁，scopePtr成为野指针  也称指针悬空（Dangling Pointer）
    // 不要这样做：cout << *scopePtr << endl;  // 危险！
    cout << "超出作用域后的指针地址: " << scopePtr << endl;
    
    // ===== 10. 正确的指针使用习惯 =====
    cout << "\n===== 正确的指针使用习惯 =====" << endl;
    int* safePtr = nullptr;  // 1. 始终初始化为nullptr
    
    safePtr = new int(777);  // 2. 分配内存
    
    if(safePtr != nullptr)   // 3. 使用前检查
    {
        cout << "安全的指针使用: " << *safePtr << endl;
        delete safePtr;      // 4. 及时释放
        safePtr = nullptr;   // 5. 释放后置空
    }
    
    cout << "\n===== 总结：避免野指针的方法 =====" << endl;
    cout << "1. 声明指针时立即初始化为nullptr" << endl;
    cout << "2. 使用指针前检查是否为nullptr" << endl;
    cout << "3. 释放动态内存后立即置空" << endl;
    cout << "4. 避免返回局部变量的地址" << endl;
    cout << "5. 避免访问已经释放的内存" << endl;
    cout << "6. 考虑使用智能指针（C++11及以后）" << endl;

    // ===== 11. 使用指针操作数组 =====
    cout << "\n===== 指针操作数组 =====" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 指针指向数组的第一个元素（数组名即为首元素地址）
    int* p = arr; // 等价于 &arr[0]
    cout << "通过指针遍历数组（指针算术）: ";
    for(int i = 0; i < n; ++i)
    {
        cout << *(p + i) << " "; // 使用指针偏移访问元素，+1等于4字节
    }
    cout << endl;

    // 使用指针作为迭代器的风格
    cout << "通过指针区间遍历并修改（把第三个元素改为100）: ";
    int* begin = arr;
    int* end = arr + n; // 指向数组末尾的下一位置
    for(int* it = begin; it != end; ++it)
    {
        if(it == arr + 2) *it = 100; // 修改第3个元素
        cout << *it << " ";
    }
    cout << endl;

    // 指针与动态数组结合
    cout << "动态数组 + 指针: ";
    int* dyn = new int[n];
    for(int i = 0; i < n; ++i) dyn[i] = arr[i] * 2; // 通过下标或指针都可以
    for(int i = 0; i < n; ++i) cout << dyn[i] << " ";
    cout << endl;
    delete[] dyn;

    // 注意：不能对数组名做 ++ 操作（数组名不是普通指针）
    cout << "注意：数组名不可自增，尝试 arr++ 会编译错误" << endl;

    // ===== 12. const 与指针的两种用法 =====
    cout << "\n===== const 与指针的两种用法 =====" << endl;

    // 1) 指向常量的指针（pointer to const）: "const int*"
    //    不能通过此指针修改被指向的数据，但可以修改指针本身，让它指向别处
    const int* ptr_to_const = arr; // 等价于: int const* ptr_to_const
    cout << "ptr_to_const 指向的值: " << *ptr_to_const << endl;
    // *ptr_to_const = 999; // 错误：不能通过 ptr_to_const 修改值（会编译失败）
    ptr_to_const = arr + 1; // 可以改变指针指向
    cout << "ptr_to_const 重新指向后: " << *ptr_to_const << endl;

    // 2) 常量指针（const pointer）: "int* const"
    //    指针本身不可改变（不能指向别处），但可以通过它修改所指向的数据
    int* const const_ptr = arr; // 指针自身不可被赋新地址
    cout << "const_ptr 指向的值(原arr[0]): " << *const_ptr << endl;
    *const_ptr = 7; // 允许：修改指针指向的数据
    cout << "通过 const_ptr 修改后 arr[0]: " << arr[0] << endl;
    // const_ptr = arr + 2; // 错误：不能改变 const_ptr 本身（会编译失败）

    // 3) 指向常量的常量指针（const int* const）
    const int* const both_const = arr;
    cout << "both_const 指向的值: " << *both_const << endl;
    // both_const = arr + 1; // 错误：指针不可变
    // *both_const = 1;      // 错误：所指数据也不可变

    return 0;
}
