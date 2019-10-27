
#ifndef _LOGIMPL_H__
#define _LOGIMPL_H__

#include "ILogDog.h"

enum class LOGTYPE
{
    /** 简单日志
    */
    LOGTYPE_SIMPLE_LOG = 0,
};

class SimpleLog :
    public ILog
{
public:
    /** 创建一个实例
    @param [in] level 日志等会
    @param [in] logStr 日志具体内容
    */
    static std::shared_ptr<ILog> Create(LogDogConfigLevel level, const DogChar* logStr)
    {
        std::shared_ptr<ILog> log(new (std::nothrow)SimpleLog(level, logStr));
        return log;
    }

    /** 构造函数
    @param [in] level 日志等会
    @param [in] logStr 日志具体内容
    */
    SimpleLog(LogDogConfigLevel level, const DogString& logStr) :
        m_level(level),
        m_logStr(logStr)
    {

    }

    ~SimpleLog()
    {
    }

public:
    /** 执行任务
    */
    virtual void DoTask()
    {
    }

private:
    /** 日志内容
    */
    DogString m_logStr;

    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;
};

static std::shared_ptr<ILog> Create(LogDogConfigLevel level, const DogString& logStr)
{
    std::shared_ptr<ILog> log(new (std::nothrow)SimpleLog(level, logStr));
    return log;
}
#endif

