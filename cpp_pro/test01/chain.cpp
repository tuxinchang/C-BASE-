#include <iostream>
using namespace std;    
// 责任链模式: 用于将请求沿着处理者链传递，直到有一个处理者处理该请求。
class Logger {
    public:
        enum LEVEL{
            Debug=1,
            Info=2,
            Warning=3,
            Error=4
        };
        LEVEL level=LEVEL::Debug;
        Logger(){

        } 
        virtual ~Logger() {

        }
        void logMessage(LEVEL level, const string& message) {
            if(level >= my_level){
                write(message);
            }
            
            if (next_logger != nullptr) {
                next_logger->logMessage(level, message);
            }
        }
        void setNextLogger(Logger* next_logger) {
            this->next_logger = next_logger;
        }
        virtual void write(const string& message) = 0; // 纯虚函数，要求子类必须实现写日志的方法
    
        protected:
            LEVEL my_level;
            Logger* next_logger = nullptr;

};   
    
        

class DebugLogger : public Logger {
    public:
        DebugLogger(LEVEL level) {
            this->my_level = level;
        }
        void write(const string& message) override {
            cout << "Debug: " << message << endl;
        }
};

class InfoLogger : public Logger {
    public:
        InfoLogger(LEVEL level) {
            this->my_level = level;
        }
        void write(const string& message) override {
            cout << "Info: " << message << endl;
        }
};

class WarningLogger : public Logger {
    public:
        WarningLogger(LEVEL level) {
            this->my_level = level;
        }
        void write(const string& message) override {
            cout << "Warning: " << message << endl;
        }
};

class ErrorLogger : public Logger {
    public:
        ErrorLogger(LEVEL level) {
            this->my_level = level;
        }
        void write(const string& message) override {
            cout << "Error: " << message << endl;
        }
};

//客户·
class Client {
    public:
        Client() {
        }
        virtual ~Client() {

        }
        void text(){
            Logger* logger_chain = getChain();
            logger_chain->logMessage(Logger::Debug, "这是一个调试日志");
            cout << endl;
            logger_chain->logMessage(Logger::Info, "这是一个信息日志"); 
            cout << endl;   
            logger_chain->logMessage(Logger::Warning, "这是一个警告日志");
            cout << endl;   
            logger_chain->logMessage(Logger::Error, "这是一个错误日志");
            cout << endl;   
        }
    private:
        Logger* logger_chain; // 责任链的起点
        Logger* getChain() {
            Logger* debug_logger = new DebugLogger(Logger::Debug);
            Logger* info_logger = new InfoLogger(Logger::Info);
            Logger* warning_logger = new WarningLogger(Logger::Warning);
            Logger* error_logger = new ErrorLogger(Logger::Error);

            // 正确的责任链顺序：从低级别到高级别
            debug_logger->setNextLogger(info_logger);
            info_logger->setNextLogger(warning_logger); 
            warning_logger->setNextLogger(error_logger);   

            return debug_logger;  // 返回链的起点（最低级别）
        }
        void logMessage(Logger::LEVEL level, const string& message) {
            if (logger_chain != nullptr) {
                logger_chain->logMessage(level, message);
            }
        }
};
//设置责任链
int main() {
    Client client;
    client.text();
    return 0;
}