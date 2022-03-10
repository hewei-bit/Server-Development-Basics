#include "zero_thread.h"
#include <sstream>
#include <iostream>
#include <exception>
ZERO_Thread::ZERO_Thread():
    _running(false), _th(NULL)
{

}

ZERO_Thread::~ZERO_Thread()
{
    if(_th != NULL)
    {
        //如果资源没有被detach或者被join，则自己释放
        if (_th->joinable())
        {
            _th->detach();
        }

        delete _th;
        _th = NULL;
    }
    std::cout << "~ZERO_Thread()" << std::endl;
}

bool ZERO_Thread::start()
{
    if (_running)
    {
        return false;
    }
    try
    {
        _th = new std::thread(&ZERO_Thread::threadEntry, this);
    }
    catch(...)
    {
        throw  "[ZERO_Thread::start] thread start error";
    }
    return true;
}

void ZERO_Thread::stop()
{
    _running = false;
}

bool ZERO_Thread::isAlive() const
{
    return _running;
}

void ZERO_Thread::join()
{
    if (_th->joinable())
    {
        _th->join();  // 不是detach才去join
    }
}

void ZERO_Thread::detach()
{
    _th->detach();
}

size_t ZERO_Thread::CURRENT_THREADID()
{
    // 声明为thread_local的本地变量在线程中是持续存在的，不同于普通临时变量的生命周期，
    // 它具有static变量一样的初始化特征和生命周期，即使它不被声明为static。
    static thread_local size_t threadId = 0;
    if(threadId == 0 )
    {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        threadId = strtol(ss.str().c_str(), NULL, 0);
    }
    return threadId;
}

void ZERO_Thread::threadEntry(ZERO_Thread *pThread)
{
    pThread->_running = true;

    try
    {
        pThread->run();   // 函数运行所在
    }
    catch (std::exception &ex)
    {
        pThread->_running = false;
        throw ex;
    }
    catch (...)
    {
        pThread->_running = false;
        throw;
    }
    pThread->_running = false;
}
