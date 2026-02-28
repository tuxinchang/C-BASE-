#include<iostream>
#include<string>
using namespace std;

int main() {
	// 1. 构造函数
	string s1; // 默认构造，空字符串
	string s2("hello"); // 由C字符串构造
	string s3(s2); // 拷贝构造
	string s4(5, 'A'); // 5个'A'
	string s5 = s2 + " world"; // 拼接

	cout << "s1: '" << s1 << "'\ns2: '" << s2 << "'\ns3: '" << s3 << "'\ns4: '" << s4 << "'\ns5: '" << s5 << "'\n";

	// 2. 基本操作
	cout << "\n基本操作演示：" << endl;
	cout << "s2.length(): " << s2.length() << endl;
	cout << "s2.size(): " << s2.size() << endl;
	cout << "s2.empty(): " << (s2.empty() ? "true" : "false") << endl;
	cout << "s2[1]: " << s2[1] << endl;
	s2[0] = 'H';
	cout << "修改后s2: '" << s2 << "'" << endl;

	// 3. 赋值与拼接
	s1 = "C++";
	s1 += " string";
	cout << "赋值和拼接: '" << s1 << "'" << endl;

	// 4. 查找和替换
	size_t pos = s5.find("world");
	if (pos != string::npos) {
		cout << "'world' 在 s5 中的位置: " << pos << endl;
		s5.replace(pos, 5, "C++");
		cout << "替换后s5: '" << s5 << "'" << endl;
	}

	// 5. 插入和删除
	s5.insert(0, "Say: ");
	cout << "插入后s5: '" << s5 << "'" << endl;
	s5.erase(0, 5);
	cout << "删除后s5: '" << s5 << "'" << endl;

	// 6. 子串和比较
	string sub = s5.substr(0, 3);
	cout << "子串: '" << sub << "'" << endl;
	cout << "s2 == s3: " << (s2 == s3 ? "true" : "false") << endl;
	cout << "s2 > s3: " << (s2 > s3 ? "true" : "false") << endl;

	// 7. 遍历
	cout << "\ns5 遍历: ";
	for (char ch : s5) cout << ch << ' ';
	cout << endl;

	return 0;
}
