#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
using namespace std;

// 自定义异常类
class InvalidInputException : public exception {
private:
    string message;
public:
    InvalidInputException(const string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// 案例1：基本的异常处理 - 除零错误
void divideNumbers() {
    cout << "\n=== 案例1：除零异常处理 ===" << endl;
    
    try {
        int numerator = 10;
        int denominator = 0;
        
        if (denominator == 0) {
            throw runtime_error("除数不能为零！");
        }
        
        int result = numerator / denominator;
        cout << "计算结果：" << result << endl;
        
    } catch (const runtime_error& e) {
        cout << "捕获到运行时异常：" << e.what() << endl;
    }
}

// 案例2：数组越界异常处理
void arrayBoundsCheck() {
    cout << "\n=== 案例2：数组越界异常处理 ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    try {
        // 尝试访问越界元素
        int index = 10;
        if (index >= numbers.size() || index < 0) {
            throw out_of_range("数组索引越界！索引：" + to_string(index) + 
                             ", 数组大小：" + to_string(numbers.size()));
        }
        
        cout << "数组元素：" << numbers[index] << endl;
        
    } catch (const out_of_range& e) {
        cout << "捕获到越界异常：" << e.what() << endl;
    }
}

// 案例3：自定义异常处理 - 输入验证
void validateUserInput() {
    cout << "\n=== 案例3：自定义异常处理 ===" << endl;
    
    try {
        string input;
        cout << "请输入一个正整数：";
        cin >> input;
        
        // 检查输入是否为空
        if (input.empty()) {
            throw InvalidInputException("输入不能为空！");
        }
        
        // 检查输入是否为数字
        for (char c : input) {
            if (!isdigit(c)) {
                throw InvalidInputException("输入必须为数字！");
            }
        }
        
        // 转换为整数并检查范围
        int number = stoi(input);
        if (number <= 0) {
            throw InvalidInputException("数字必须为正整数！");
        }
        
        cout << "输入验证成功！数字：" << number << endl;
        
    } catch (const InvalidInputException& e) {
        cout << "输入验证失败：" << e.what() << endl;
    } catch (const exception& e) {
        cout << "其他异常：" << e.what() << endl;
    }
}

// 案例4：多重异常捕获
void multipleExceptionHandling() {
    cout << "\n=== 案例4：多重异常捕获 ===" << endl;
    
    try {
        string input;
        cout << "请输入一个数字：";
        cin >> input;
        
        // 可能抛出多种异常
        double number = stod(input);
        
        if (number < 0) {
            throw invalid_argument("数字不能为负数！");
        }
        
        cout << "数字的平方根：" << sqrt(number) << endl;
        
    } catch (const invalid_argument& e) {
        cout << "参数无效：" << e.what() << endl;
    } catch (const out_of_range& e) {
        cout << "数值超出范围：" << e.what() << endl;
    } catch (const exception& e) {
        cout << "其他异常：" << e.what() << endl;
    }
}

// 案例5：异常传播和重新抛出
void processData(const string& data) {
    if (data.empty()) {
        throw runtime_error("数据不能为空！");
    }
    
    if (data.length() > 100) {
        throw length_error("数据长度超过限制！");
    }
    
    cout << "数据处理成功：" << data << endl;
}

void exceptionPropagation() {
    cout << "\n=== 案例5：异常传播 ===" << endl;
    
    try {
        string data = ""; // 空数据会触发异常
        processData(data);
        
    } catch (const runtime_error& e) {
        cout << "捕获到运行时异常：" << e.what() << endl;
        // 重新抛出异常
        throw;
    }
}

int main() {
    cout << "========== C++ 异常处理案例演示 ==========" << endl;
    
    // 运行所有异常处理案例
    divideNumbers();
    arrayBoundsCheck();
    validateUserInput();
    multipleExceptionHandling();
    
    // 异常传播案例
    try {
        exceptionPropagation();
    } catch (...) {
        cout << "在main函数中捕获到传播的异常" << endl;
    }
    
    cout << "\n=== 程序正常结束 ===" << endl;
    return 0;
}