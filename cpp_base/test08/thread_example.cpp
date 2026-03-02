#include<iostream>
#include<thread>
#include<string>
using namespace std;
void printHelloWorld(string msg,int& count){ 
    for(int i=0;i<1000;i++){
        cout << "Hello, World from thread! :" << msg << endl;
        count++;
    }
}
int main() {
    int count = 0;
    //1.创建线程对象，传入要执行的函数,主要线程和子线程共享count变量，
    //使用std::ref传递引用，而线程默认是值传递的,必须显式传递引用，确保子线程能够修改主线程中的count变量
    //当函数中使用带有引用同类型的参数的线程时，要注意函数一旦结束就会释放内存，因此要在变量前面加入staitc或者new分配空间，不然就把变量声明在函数外面
    thread t(printHelloWorld, "程序员", ref(count));
    //2.主程序检查线程是否结束，等待线程执行完成
    t.join();//在join()前，不要释放线程中参数的内存，否则会导致数据未定义行为
    cout << "主线程结束, count = " << count << endl;
    return 0;
}
