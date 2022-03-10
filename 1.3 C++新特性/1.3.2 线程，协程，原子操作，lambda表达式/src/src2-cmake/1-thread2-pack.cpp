#include <iostream>
#include <chrono>
#include "zero_thread.h"
using namespace std;

class A: public ZERO_Thread
{
public:
    void run()
    {
        while (_running)
        {
            cout << "print A " << endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        cout << "----- leave A " << endl;
    }
};

class B: public ZERO_Thread
{
public:
    void run()
    {
        while (_running)
        {
            cout << "print B " << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        cout << "----- leave B " << endl;
    }
};

int main()
{
    {
        A a;
        a.start();
        B b;
        b.start();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        a.stop();
        a.join();
        b.stop();
        b.join();
    }
    cout << "Hello World!" << endl;
    return 0;
}
