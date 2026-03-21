#pragma once
#include <string>

#ifdef _WIN32
  #include <windows.h>
  #include <iostream>

namespace utf8 {

inline std::string wstring_to_utf8(const std::wstring& ws) {
    if (ws.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), (int)ws.size(),
                                nullptr, 0, nullptr, nullptr);
    std::string out(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), (int)ws.size(),
                        out.data(), n, nullptr, nullptr);
    return out;
}

// 可选：初始化输出为 UTF-8（显示中文更稳）
inline void init_console_utf8() {
    SetConsoleOutputCP(CP_UTF8);
}

// 读一整行（支持中文/空格）
inline std::string getline() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE) return {};

    std::wstring wbuf(8192, L'\0');
    DWORD read = 0;

    if (!ReadConsoleW(hIn, wbuf.data(), (DWORD)wbuf.size(), &read, nullptr))
        return {};

    // 去掉 Windows 行尾 \r\n
    while (read > 0 && (wbuf[read - 1] == L'\n' || wbuf[read - 1] == L'\r'))
        --read;

    wbuf.resize(read);
    return wstring_to_utf8(wbuf);
}

// 读一个 token（按空白分隔），适合“姓名/指令”这类输入
inline std::string read_word() {
    for (;;) {
        std::string line = getline();
        // 去掉前导空白
        size_t i = line.find_first_not_of(" \t");
        if (i == std::string::npos) continue;

        // 取第一个 token
        size_t j = line.find_first_of(" \t", i);
        return (j == std::string::npos) ? line.substr(i) : line.substr(i, j - i);
    }
}

} // namespace utf8

#else
  #include <iostream>

namespace utf8 {
inline void init_console_utf8() {}
inline std::string getline() { std::string s; std::getline(std::cin, s); return s; }
inline std::string read_word() { std::string s; std::cin >> s; return s; }
} // namespace utf8
#endif
