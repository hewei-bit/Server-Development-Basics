#include <iostream>

using namespace std;
//匿名函数的基本语法为
//[捕获列表](参数列表)->返回类型{函数体}
void test1()
{
    auto Add = [](int a, int b) -> int {
        return a + b;
    };
    std::cout << Add(1, 2) << std::endl;        //输出3
}
//一般情况下，编译器可以自动推断出lambda表达式的返回类型，所以我们可以不指定返回类型
//[捕获列表](参数列表){函数体}
void test2()
{
    auto Add = [](int a, int b) {
        return a + b;
    };
    std::cout << Add(1, 2) << std::endl;        //输出3
}

void test3()
{
    int c = 12;
    int d = 30;
    auto Add = [c, d](int a, int b)->int { //捕获列表加入使用的外部变量c，否则无法通过编译
        cout << "d = " << d  << endl;
        return c;
    };
    d = 20;
    std::cout << Add(1, 2) << std::endl;
}

void test4()
{
    int c = 12;
    auto Add = [c](int a, int b)->int { //捕获列表加入使用的外部变量c，否则无法通过编译
//        c = a; // 编译报错
        return c;
    };
    std::cout << Add(1, 2) << std::endl;
}

void test5()
{
    int c = 12;
    int d = 30;
    auto Add = [&c, &d](int a, int b)->int { //捕获列表加入使用的外部变量c，否则无法通过编译
        c = a; // 编译对的
        cout << "d = " << d  << endl;
        return c;
    };
    d = 20;
    std::cout << Add(1, 2) << std::endl;
}

void test6()
{
    int c = 12;
    int d = 30;
    auto Add = [&c, &d](int &a, int &b)->int { //捕获列表加入使用的外部变量c，否则无法通过编译
        a = 11;
        b = 12;
        cout << "d = " << d  << endl;
        return a + b;
    };
    d = 20;
    std::cout << Add(c, d) << std::endl;
    cout << "c = " << d  << endl;
    cout << "d = " << d  << endl;
}

int main()
{
    test6();

    return 0;
}
