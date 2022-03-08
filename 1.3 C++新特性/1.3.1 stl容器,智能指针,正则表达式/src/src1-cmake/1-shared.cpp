#include <iostream>
#include <memory>
using namespace std;

class A
{
public:
    ~A(){
        cout << "delete A\n";
    }

};
int main()
{
    {
//        A *pa = new A;
        std::shared_ptr<A> pb(new A);
        std::shared_ptr<A> pb2 = pb;
        std::shared_ptr<A> pb3 = pb;

    }
    cout << "main finish" << endl;
    return 0;
}
