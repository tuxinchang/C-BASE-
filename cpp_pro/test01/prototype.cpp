#include <iostream>
using namespace std;
// 原型模式: 用于创建对象的原型，通过复制原型对象来创建新的对象。
class Prototype {
public:
    Prototype(){

    }
    virtual ~Prototype() {

    }
    virtual Prototype* clone() const = 0; // 纯虚函数，要求子类必须实现克隆方法
};
class ConcretePrototype : public Prototype {
public:
    ConcretePrototype() : my_counter(0) {

    }
    ~ConcretePrototype(){

    }
    ConcretePrototype(const ConcretePrototype& cp) : my_counter(cp.my_counter) {

    }
    Prototype* clone() const  override{
        return new ConcretePrototype(*this);
    }

private:
    int my_counter;
};
int main() {
    ConcretePrototype* original = new ConcretePrototype();
    Prototype* copy = original->clone();

    // 使用 copy 进行操作...

    delete original;
    delete copy;
    return 0;
}