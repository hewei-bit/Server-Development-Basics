#include <iostream>
#include <memory>
using namespace std;


class A;
class B;

class A {
public:
    std::weak_ptr<B> bptr; // 修改为weak_ptr
    int *val;
    A() {
        val = new int(1);
    }
    ~A() {
        cout << "A is deleted" << endl;
        delete  val;
    }
};

class B {
public:
    std::shared_ptr<A> aptr;
    ~B() {
        cout << "B is deleted" << endl;
    }
};

//weak_ptr 是一种不控制对象生命周期的智能指针,
void test()
{
    std::shared_ptr<A> ap(new A);
    std::weak_ptr<A> wp1 = ap;
    std::weak_ptr<A> wp2 = ap;
    cout<< "ap.use_count()" << ap.use_count()<< endl;
}

void test2()
{
    std::weak_ptr<A> wp;
    {
        std::shared_ptr<A> ap(new A);
        wp = ap;
    }
    cout<< "wp.use_count()" << wp.use_count() << ", wp.expired():" << wp.expired() << endl;
    if(!wp.expired()) {
        // wp不能直接操作对象的成员、方法
        std::shared_ptr<A> ptr = wp.lock(); // 需要先lock获取std::shared_ptr<A>
        *(ptr->val) = 20;  // 是不是有问题了？
    }
}


int main()
{
    test2();
//    {
//        std::shared_ptr<A> ap(new A);
//        std::shared_ptr<B> bp(new B);
//        ap->bptr = bp;
//        bp->aptr = ap;
//    }
    cout<< "main leave" << endl;
    return 0;
}
