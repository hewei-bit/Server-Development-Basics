//1-6-package_task
#include <iostream>
#include <future>
using namespace std;

int add(int a, int b, int c)
{
    return a + b + c;
}

void do_other_things()
{
    std::cout << "Hello World" << std::endl;
}

int main()
{
    std::packaged_task<int(int, int, int)> task(add);
    do_other_things();
    std::future<int> result = task.get_future();
    task(1, 1, 2); //必须要让任务执行，否则在get()获取future的值时会一直阻塞
    std::cout << result.get() << std::endl;
    return 0;
}
