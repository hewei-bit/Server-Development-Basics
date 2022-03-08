#include <string>

class Context
{
public:
    std::string name;
    int day;
};

// 稳定点 和 变化点
// 稳定点：批假流程   由职位从低到高批假  有权限
// 变化点：请假天数、增加批假人员
// 在一个整洁的房子（稳定点），好动的猫（变化），怎么保证这个房子的整洁？
// 把猫放在笼子里
// 如果某一个需求 只有稳定点  不需要设计模式（应对变化的）
// 如果全是变化点，也不需要设计模式？软件开发怎么解决全是变化点？脚本语言 热更新 来应对变化点
// 如果两者都存在，不是消灭变化点，是隔离变化点   解耦合
// 多线程锁  锁的类型  锁的粒度 线程池
class LeaveRequest
{
public:
    bool HandleRequest(const Context &ctx)
    {
        if (ctx.day <= 1)
            HandleByBeaty(ctx);
        if (ctx.day <= 1)
            HandleByMainProgram(ctx);
        else if (ctx.day <= 10)
            HandleByProjMgr(ctx);
        else
            HandleByBoss(ctx);
    }

public:
    bool HandleByBeaty(const Context &ctx)
    {
    }
    bool HandleByMainProgram(const Context &ctx)
    {
    }
    bool HandleByProjMgr(const Context &ctx)
    {
    }
    bool HandleByBoss(const Context &ctx)
    {
    }
};