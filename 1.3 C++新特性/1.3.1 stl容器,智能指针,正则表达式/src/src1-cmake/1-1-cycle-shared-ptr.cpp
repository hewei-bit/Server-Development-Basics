#include <iostream>
#include <memory>
using namespace std;


class A;
class B;

class A {
public:
    std::shared_ptr<B> bptr;
    ~A() {
        cout << "A is deleted" << endl;
    }
};

class B {
public:
    std::shared_ptr<A> aptr;
    ~B() {
        cout << "B is deleted" << endl;  // 析构函数后，才去释放成员变量
    }
};

int main()
{
    std::shared_ptr<A> pa;

    {
        std::shared_ptr<A> ap(new A);
        std::shared_ptr<B> bp(new B);
        ap->bptr = bp;
        bp->aptr = ap;
        pa = ap;
        // 是否可以手动释放呢？
//        ap.reset();
        ap->bptr.reset(); // 手动释放成员变量才行
    }
    cout<< "main leave. pa.use_count()" << pa.use_count() << endl;  // 循环引用导致ap bp退出了作用域都没有析构
    return 0;
}
