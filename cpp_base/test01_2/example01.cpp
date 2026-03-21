#include<iostream>
#include<cstring>
using namespace std;
#define PI 3.1415926
//符号常量：#define PI 3.1415926  字面常量：3.1415926 符号常量：const double PI = 3.1415926;  字面常量：3.1415926 常量
int main() {
    //如果不在vscode中设置json加入终端的utf-8编码配置，输出中文会乱码，也可以使用windows.h库中的SetConsoleOutputCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);
    cout<<"圆周率的值为："<<PI<<endl;
    //变量的声明，赋值和使用
    int a = 10;
    string str = "Hello, World!";
    float f = 3.14f;
    char c = 'A';
    cout<<"c的值为："<<c<<endl;
    cout<<"f的值为："<<f<<endl;
    cout<<"字符串的值为："<<str<<endl;
    cout<<"a的值为："<<a<<endl;
    //整型又可以分为：short int、int、long int、long long int等，分别占用不同的字节数，范围也不同
    short int si = 32767; //占用2字节，范围-32768~32767
    int i = 2147483647; //占用4字节，范围-2147483648~2147483647
    long int li = 22; //占用8字节，范围-~9223372036854775807
    long long int lli = 9223372036854775807; //占用8字节，范围-9223372036854775808~9223372036854775807
    cout<<"short int的值为："<<si<<" "<<"占用的字节为"<<sizeof(si)<<"字节"<<endl;        
    cout<<"int的值为："<<i<<" "<<"占用的字节为"<<sizeof(i)<<"字节"<<endl;
    cout<<"long int的值为："<<li<<" "<<"占用的字节为"<<sizeof(li)<<"字节"<<endl; 
    cout<<"long long int的值为："<<lli<<" "<<"占用的字节为"<<sizeof(lli)<<"字节"<<endl;
    //有符号signed(可选)    无符号unsigned(必选)
    unsigned int ui = -30; 
    cout<<"unsigned int的值为："<<ui<<endl; //无符号数必须为正数，所以赋值为-30，但是输出必为30
    //实型 float占4个字节
    float d = 1234567890;//只提供前7位有效数字，所以有效输出为1234567
    float d1 = 1.23456789;//只提供7位有效数字，所以有效输出为1.234567
    cout<<fixed; //设置输出为定点格式
    cout.width(20); //设置输出宽度为20
    cout<<"float的值为："<<d<<endl; //float的精度为7位有效数字，所以输出为1234567920
    cout<<"float d1的值为："<<d1<<endl;
    //实型 double占8个字节，提供15位有效数字
    double d2 = 12345678901234567890.0; //只提供15位有效数字再加一个小数位，所以有效输出为12345678901234568000
    cout<<"double的值为："<<d2<<endl;
    //字符型占1个字节，存储的是字符的ASCII码值，97对应字符'a'
    char cc ='a'; //字符型占1个字节，存储的是字符的ASCII码值，'
    cout<<"char cc的值为："<<cc+1<<endl;//98
    char ccc = 'A'+1; //字符型占1个字节，存储的是字符的ASCII码值，65对应字符'A',输出为66
    cout<<"char ccc的值为："<<ccc<<endl;//B
    //转义字符：\n换行 \t制表符 \\反斜杠 \'单引号 \"双引号
    cout<<"转义字符：\n换行 \t制表符 \\反斜杠 \'单引号 \"双引号"<<endl;
    //制表符\t可以在输出中对齐文本，一个制表符相当于8个空格，所以输出的文本会在每8个字符的位置对齐
    cout<<"姓名\t年龄\t性别"<<endl;
    cout<<"张三份\t25\t男"<<endl;
    //c语言风格的字符串
    char cstr[] = "Hello, C-style string!";//字符串常量存储在只读数据区，不能修改，所以cstr[0] = 'h';会报错
    char *pcstr = "\"Hello, C-style string!\"";//但是pcstr是一个指针变量，指向字符串常量的首地址，可以修改指针变量的值，但是不能修改字符串常量的内容，所以pcstr[0] = 'h';会报错
    //C++风格的字符串
    string cppstr = "Hello, C++ string!";//但是cppstr是一个string对象，存储在栈区，可以修改，所以cppstr[0] = 'h';是合法的
    cout<<"c风格字符串的值为："<<cstr<<endl;
    cout<<"c风格字符串的值为："<<pcstr<<endl;
    cout<<"c++风格字符串的值为："<<cppstr<<endl;
    string str1="Hello, ";
    string str2="World!";  
    double d3 = 2025.0;

    //double；类型无法直接与字符串进行拼接，所以需要先将double类型转换为字符串类型，再进行拼接

    cout<<"字符串拼接的结果为："<<str1+str2+to_string(d3)<<endl; //字符串拼接
    //strcmp函数用于比较两个字符串的大小，返回值为0表示两个字符串相等，返回值为正数表示第一个字符串大于第二个字符串，返回值为负数表示第一个字符串小于第二个字符串
    cout<<"strcmp函数比较字符串的结果为："<<strcmp(cstr, pcstr)<<endl; //strcmp函数比较字符串的结果为：1

    //布尔型占1个字节，只有两个取值true和false，输出时会被转换为整数，true输出为1，false输出为0
    bool b1 = true;
    bool b2 = false;


    return 0;
}