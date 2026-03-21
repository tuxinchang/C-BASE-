#include <fstream>
#include <iostream>
#include <string>

// 写入文本到文件（支持中文，需保存为UTF-8编码）
void writeTextFile(const std::string& filename, const std::string& content) {
    std::ofstream ofs(filename, std::ios::out | std::ios::binary);
    if (!ofs) {
        std::cerr << "无法打开文件进行写入: " << filename << std::endl;
        return;
    }
    // 写入UTF-8 BOM，确保Windows下记事本等能正确识别
    const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    ofs.write(reinterpret_cast<const char*>(bom), 3);
    ofs << content;
    ofs.close();
}

// 读取文本文件内容（支持中文，假设文件为UTF-8编码）
std::string readTextFile(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    if (!ifs) {
        std::cerr << "无法打开文件进行读取: " << filename << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    // 跳过UTF-8 BOM
    if (content.size() >= 3 && (unsigned char)content[0] == 0xEF && (unsigned char)content[1] == 0xBB && (unsigned char)content[2] == 0xBF) {
        content = content.substr(3);
    }
    ifs.close();
    return content;
}


// 示例用法
int main() {
    std::string filename = "test_utf8.txt";
    std::string text = "Hello, 世界！这是中文内容。";
    std::string file_name1 = "操作.txt";
    writeTextFile(filename, text);

    std::string readText = readTextFile(file_name1);
    std::cout << "读取内容: " << readText << std::endl;
    return 0;
}