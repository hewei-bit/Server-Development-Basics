#include <string>

class Context
{
public:
    std::string name;
    int day;
};

// 稳定点 抽象  变化点 扩展
class IHandler
{
public:
    virtual ~IHandler() {}
    void SetNextHandler(IHandler *next)
    { // 链表关系
        next = next;
    }
    // 抽象稳定点，对扩展开放
    // 模板模式：固定算法骨架，通过子类去扩展子流程
    bool Handle(const Context &ctx)
    {
        if (CanHandle(ctx))
        {
            return HandleRequest(ctx);
        }
        else if (GetNextHandler())
        {
            return GetNextHandler()->Handle(ctx);
        }
        else
        {
            // err
        }
        return false;
    }

protected:
    virtual bool HandleRequest(const Context &ctx) = 0;
    virtual bool CanHandle(const Context &ctx) = 0;
    IHandler *GetNextHandler()
    {
        return next;
    }

private:
    IHandler *next;
};

// 能不能处理，以及怎么处理
class HandleByMainProgram : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        //
        if (ctx.day <= 10)
            return true;
        return false;
    }
};

class HandleByProjMgr : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        //
        if (ctx.day <= 20)
            return true;
        return false;
    }
};
class HandleByBoss : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        //
        if (ctx.day < 30)
            return true;
        return false;
    }
};

class HandleByBeauty : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        //
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        //
        if (ctx.day <= 3)
            return true;
        return false;
    }
};

int main()
{
    // IHandler * h1 = new HandleByMainProgram();
    // IHandler * h2 = new HandleByProjMgr();
    // IHandler * h3 = new HandleByBoss();
    // h1->SetNextHandler(h2);
    // h2->SetNextHandler(h3);
    // 抽象工厂
    // nginx http 处理
    IHandler *h0 = new HandleByBeauty();
    IHandler *h1 = new HandleByMainProgram();
    IHandler *h2 = new HandleByProjMgr();
    IHandler *h3 = new HandleByBoss();
    h0->SetNextHandler(h1);
    h1->SetNextHandler(h2);
    h2->SetNextHandler(h3);
    // 设置下一指针
    Context ctx;
    h0->Handle(ctx);

    return 0;
}