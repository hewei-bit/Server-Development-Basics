#include <string>
#include <vector>
using namespace std;

class LogSys
{
public:
    LogSys() {}
    void WriteLog(const vector<string> &)
    {
        // ... 日志id 时间戳 服务器id 具体日志内容 roleid
    }
    vector<string> &ReadLog()
    {
        // ...
        vector<string> data /* = ...*/;
        return data;
    }
};

class DB; // 面向接口编程 而不是具体类 强依赖  耦合性高  mysql mongo

class LogSysEx : public LogSys
{
public:
    LogSysEx(DB *db) : _db(db) {}

    void AddLog(const vector<string> &data)
    {
        LogSys::WriteLog(data);
        /*
            这里调用 _db 的方法将 data 数据存储到数据库
        */
    }

    void DelLog(const int logid)
    {
        vector<string> &data = LogSys::ReadLog();
        // 从 vector<string> 中删除 logid的日志
        LogSys::WriteLog(data);
        // 调用 _db 的方法将 logid的日志删除
    }

    void UpdateLog(const int logid, const string &udt)
    {
        vector<string> &data = LogSys::ReadLog();
        // 从 vector<string> 中更新 logid的日志 udt
        LogSys::WriteLog(data);
        // 调用 _db 的方法将 logid的日志更改
    }

    string &LocateLog(const int logid)
    {
        vector<string> &data = LogSys::ReadLog();
        string log1 /* = from log file*/;
        string log2 /* = from db */;
        string temp = log1 + ";" + log2;
        return temp;
    }

private:
    DB *_db;
};