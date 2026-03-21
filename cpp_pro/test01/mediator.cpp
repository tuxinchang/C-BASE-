#include <iostream>
#include <vector>
using namespace std;
// 中介者模式: 用于定义一个中介对象，该对象负责协调多个对象之间的通信。
class Employee{
    private:
        string name;
        string context="无语了";  
    public:
        Employee(const string& name) : name(name){}
        void setName(const string& name){
            this->name = name;
        }
        string getName() const {
            return name;
        }
        void setContext(const string& context){
            this->context = context;            
        }
        string getContext() const {
            return context;
        }
        //说话
        virtual void talk() const = 0;
};
//老板
class Boss : public Employee {
    public:
        Boss(const string& name) : Employee(name) {

        }
        void talk() const override {
            cout << getName() << "说: " << getContext() << endl;
        }
};
//经理
class Manager : public Employee {
    public:
        Manager(const string& name) : Employee(name) {

        }
        void talk() const override {
            cout << getName() << "说: " << getContext() << endl;
        }
};
//安全员
class Security : public Employee {
    public:
        Security(const string& name) : Employee(name) {

        }
        void talk() const override {
            cout << getName() << "说: " << getContext() << endl;
        }
};
class Mediator {
    protected:
        vector<Employee*> colleagues; // 同事对象列表
    public:
        void addColleague(Employee* colleague) {
            colleagues.push_back(colleague);
        }
        virtual void notify(const Employee* employee) = 0;
};
//具体中介者
class ConcreteMediator : public Mediator {
    public:
        void notify(const Employee* employee) override {
            employee->talk(); // 先让发送消息的同事说话 
            for (Employee* emp : colleagues) {
                if (emp != employee) { // 不向发送消息的同事发送消息
                    emp->talk();
                }
            }
        }
};
int main() {
    ConcreteMediator mediator;

    Boss* boss = new Boss("老板");
    Manager* manager = new Manager("经理");
    Security* security = new Security("安全员");

    mediator.addColleague(boss);
    mediator.addColleague(manager);
    mediator.addColleague(security);

    boss->setContext("今天开会，所有人必须参加！");
    mediator.notify(boss);

    manager->setContext("好的，我会通知大家的。");
    mediator.notify(manager);

    security->setContext("我会确保会议室的安全。");
    mediator.notify(security);

    delete boss;
    delete manager;
    delete security;

    return 0;
}