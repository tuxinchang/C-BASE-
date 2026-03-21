#include <iostream>
using namespace std;
enum StrategyType {
    Night,
    Day,
    Rainy,
    Sunny
};
//策略模式: 用于封装算法，使算法可以独立于使用它的客户而变化。
class Strategy {
    public:
        virtual ~Strategy() {

        }
        virtual void algorithm() = 0;
};
// 具体策略类: 实现具体的算法。晚上
class StrategyNight : public Strategy {
    public:
        void algorithm() override {
            cout << "夜间模式算法" << endl;
        }   
};
// 具体策略类: 实现具体的算法。白天
class StrategyDay : public Strategy {
    public: 
        void algorithm() override {
            cout << "白天模式算法" << endl;
        }   
};
//具体策略类: 实现具体的算法。雨天
class StrateryRainy:public Strategy{
    public:
        void algorithm() override {
            cout << "雨天模式算法" << endl;
        }   
};
// 具体策略类: 实现具体的算法。晴天
class StraterySunny:public Strategy{
    public:
        void algorithm() override {
            cout << "晴天模式算法" << endl;
        }   
};
// 上下文类: 使用策略对象来执行算法。   
class Context {
    public:
        Context(StrategyType strategy)  {
            switch (strategy){
                case Night:
                    pstrategy = new StrategyNight();
                    break;  
                case Day:
                    pstrategy = new StrategyDay();
                    break;          
                case Rainy:
                    pstrategy = new StrateryRainy();
                    break;          
                case Sunny:
                    pstrategy = new StraterySunny();
                    break;
                default:
                    cout << "未知的策略类型" << endl;
            }
        }
        ~Context() {
            delete pstrategy;
        }
        void execute() {
            if (pstrategy) {
                pstrategy->algorithm();
            } else {
                cout << "没有可用的策略" << endl;
            }
        } 
    private:
        Strategy* pstrategy=nullptr;
}; 
int main() {
    Context context(Night);
    context.execute(); // 输出: 夜间模式算法

    Context context2(Day);
    context2.execute(); // 输出: 白天模式算法

    Context context3(Rainy);
    context3.execute(); // 输出: 雨天模式算法

    Context context4(Sunny);
    context4.execute(); // 输出: 晴天模式算法
    return 0;
}