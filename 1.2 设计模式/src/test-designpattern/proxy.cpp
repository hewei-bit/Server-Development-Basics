
class ISubject {
public:
    virtual void Handle() = 0;
    virtual ~ISubject() {}
};

// 该类在当前进程，也可能在其他进程当中
class RealSubject : public ISubject {
public:
    virtual void Handle() {
        // 只完成功能相关的操作，不做其他模块的判断
    }
};

// 在当前进程当中  只会在某个模块中使用
class Proxy1 : public ISubject {
public:
    Proxy1(ISubject *subject) : _subject(subject) {}
    virtual void Handle() {
        // 在访问 RealSubject 之前做一些处理
        //if (不满足条件)
        //    return;
        _subject->Handle();
        count++;
        // 在访问 RealSubject 之后做一些处理
    }
private:
    ISubject* _subject;
    static int count;
};
int Proxy1::count = 0;

// 在分布式系统当中  skynet actor
class Proxy2 : public ISubject {
public:
    virtual void Handle() {
        // 在访问 RealSubject 之前做一些处理
        
        // 发送到数据到远端  网络处理  同步非阻塞 ntyco c协程
        //IResult * val = rpc->call("RealSubject", "Handle");

        // 在访问 RealSubject 之后做一些处理
    }
private:
    /*void callback(IResult * val) {
        // 在访问 RealSubject 之后做一些处理
    }*/
};