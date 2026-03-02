#include <string>
#include <iostream>

static std::string WStringToUtf8(const std::wstring& ws) {
    if (ws.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), (int)ws.size(),
                                nullptr, 0, nullptr, nullptr);
    std::string out(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), (int)ws.size(),
                        out.data(), n, nullptr, nullptr);
    return out;
}

static std::string ReadLineUtf8() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    std::wstring wbuf(4096, L'\0');
    DWORD read = 0;

    if (!ReadConsoleW(hIn, wbuf.data(), (DWORD)wbuf.size(), &read, nullptr))
        return {};

    while (read > 0 && (wbuf[read - 1] == L'\n' || wbuf[read - 1] == L'\r'))
        --read;

    wbuf.resize(read);
    return WStringToUtf8(wbuf);
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // 让输出按 UTF-8 显示更稳

    std::cout << "输入中文: ";
    std::string s = ReadLineUtf8();
    std::cout << "你输入的是: " << s << "\n";
    return 0;
}



