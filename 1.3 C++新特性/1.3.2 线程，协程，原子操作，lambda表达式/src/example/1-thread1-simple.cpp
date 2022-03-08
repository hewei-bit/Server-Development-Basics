#include <iostream>
#include <thread> // 头文件
using namespace std;

void func1()
{
    cout << "func1 into" << endl;
}

void func2(int a, int b)
{
    cout << "func2 a + b = " << a+b << endl;
}

class A
{
public:
    static void func3(int a)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        cout << "fun3 a = " << a << endl;

    }
};


void func4(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "func4 a + b = " << a+b << endl;
}

int main()
{
    std::thread t1(func1);  // 只传递函数
    t1.join();  // 阻塞等待线程函数执行结束

    int a =10;
    int b =20;
    std::thread t2(func2, a, b); // 加上参数传递,可以任意参数
    t2.join();

    std::thread t3(&A::func3, 1); // 绑定类静态函数
    if(t3.joinable()) {
        t3.join();
        cout << " t3.join()\n";
    }

    std::thread t4(func4, a, b);
    t4.detach();
    if(t4.joinable()) {
        t4.join();
        cout << " t4.join()\n";
    }else {
        cout << " t4 detach\n";
    }
    // 休眠注释和不注释
//    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
