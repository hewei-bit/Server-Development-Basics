//1-6-promise
// std::promise和std::future配合，可以在线程之间传递数据。
#include <future>
#include <string>
#include <thread>
#include <iostream>
using namespace std;
void print(std::promise<std::string>& p)
{
    p.set_value("There is the result whitch you want.");
}

void print2(std::promise<int>& p)
{
    p.set_value(1);
}

void do_some_other_things()
{
    std::cout << "Hello World" << std::endl;
}

int main()
{
    std::promise<std::string> promise;

    std::future<std::string> result = promise.get_future();
    std::thread t(print, std::ref(promise));
    do_some_other_things();
    std::cout <<"result " << result.get() << std::endl;
    t.join();

    std::promise<int> promise2;

    std::future<int> result2 = promise2.get_future();
    std::thread t2(print2, std::ref(promise2));
    do_some_other_things();
    std::cout << "result2 " << result2.get() << std::endl;
    t2.join();
    return 0;
}
