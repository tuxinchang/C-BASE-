#include<fstream>  
#include<string>
#include<iostream>
using namespace std;

// istream::gcount() 用于返回上一次输入操作（如 read、getline、get、ignore 等）实际读取的字符数。
// 常用于二进制或定长读取后，判断实际读取了多少字节。
// 例如：
// ifs.read(buf, 100);
// cout << "实际读取字节数: " << ifs.gcount() << endl;

void writeTextFile(){
    //打开头文件
    //创建输出文件流对象
    ofstream ofs;
    /*
    ios::out，默认会覆盖原有内容 
    ios::app 追加写入     
    ios::binary 二进制模式
    ios::trunc 如果文件存在则删除原有内容重新创建
    ios::ate 打开文件后将写入位置移动到文件末尾（不覆盖原有内容）
    ios::in 以读模式打开文件（ofstream默认是写模式，无法直接使用ios::in，需要使用ifstream）
    
    
    打开的方法可以包含多个，使用|符号连接，例如：ios::out | ios::app 表示以写入模式打开文件，并且追加内容而不是覆盖。
    */
    //打开文件，指定写入模式 
    ofs.open("test.txt", ios::app);
    if (!ofs) {
        cout << "无法打开文件进行写入" << endl;
        return;
    }
    //写入内容
    while(true) {
        string line;
        cout << "输入要写入文件的内容（输入exit结束）: ";
        getline(cin, line);
        if (line == "exit") {
            break;
        }
        ofs << line << endl; //写入一行内容
    }
    //关闭文件
    ofs.close();
}

void readTextFile(){

    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if (!ifs) {
        cout << "无法打开文件进行读取" << endl;
        return;
    }
    string line;
    cout << "文件内容如下:" << endl;
    while (getline(ifs, line)) {
        cout << line << endl; //输出每行内容
    }
    ifs.close();
}   


// 以字符数组方式读取文件内容
void readTextFileByCharArray() {
    ifstream ifs;
    ifs.open("test.txt", ios::in);
    if (!ifs) {
        cout << "无法打开文件进行读取" << endl;
        return;
    }
    const int bufSize = 1024;
    char buf[bufSize];
    cout << "以字符数组方式读取文件内容如下:" << endl;
    while (ifs.getline(buf, bufSize)) {
        cout << buf << endl;
    }
    ifs.close();
}

// 以单字符方式读取文件内容
void readTextFileByChar() {
    ifstream ifs;
    ifs.open("test.txt", ios::in);
    if (!ifs) {
        cout << "无法打开文件进行读取" << endl;
        return;
    }
    char ch;
    cout << "以字符方式读取文件内容如下:" << endl;
    while (ifs.get(ch)) {
        cout << ch;
    }
    cout << endl;
    ifs.close();
}
// 以二进制方式复制图片到另一张图片
void copyBinaryFile() {
    ifstream ifs("/home/tuxinchang/Cpp_project/image/第六章/1.png", ios::binary);
    ofstream ofs("/home/tuxinchang/Cpp_project/image/第六章/拷贝.png", ios::binary);
    if (!ifs ) {
        cout << "无法打开文件进行复制" << endl;
        return;
    }
    char buffer[4096];
    while (ifs.read(buffer, sizeof(buffer))) {
        ofs.write(buffer, ifs.gcount());
    }
    // 处理最后一次读取的剩余数据
    ofs.write(buffer, ifs.gcount());
    cout << "文件复制完成" << endl;
    ifs.close();
    ofs.close();
}

// 清空 test.txt 文件内容
void clearTextFile() {
    ofstream ofs("test.txt", ios::out | ios::trunc); // 以截断模式打开，直接清空内容
    if (!ofs) {
        cout << "无法打开文件进行清空" << endl;
        return;
    }
    // 不写内容直接关闭即可
    ofs.close();
    cout << "文件内容已清空。" << endl;
}

int main(){
    //writeTextFile();
    //clearTextFile(); // 如需清空文件，取消此行注释
    readTextFile();
    readTextFileByCharArray();
    readTextFileByChar();
    copyBinaryFile();
    return 0;
}
