
//////////////////////////////////////////////////////////////////////////
// 提供一个日志实体基类，以及一些常用的实现                                     //
//////////////////////////////////////////////////////////////////////////

#ifndef __ILOG_H_
#define __ILOG_H_

#include "ILogExecutor.h"
#include "task/ISimpleTask.h"
#include "noncopyable.h"

#include <assert.h>
#include <memory>
#include <vector>

/** 日志实体
*/
class ILog :
    public ITask,
    public NonCopyable
{
public:
    ILog()
    {
    }

    /** 执行任务
    */
    virtual void DoTask()
    {
        Log();
    }

    /** 日志任务
    */
    virtual void Log() = 0;

    /** 停止任务
    */
    virtual void Stop()
    {
        // 删除
    };
};

/** 提供一个简单基类，将日志处理分为两部分：字符串的format，对处理后的字符串处理（文件记录、网络传输等）
*/
class ISimpleLog :
    public ILog
{
public:
    /** 构造函数
    @param [in] level 日志等会
    @param [in] logStr 日志具体内容
    */
    ISimpleLog(LogDogConfigLevel level, const DogString& logStr):
        m_level(level),
        m_logStr(logStr)
    {

    }

    virtual ~ISimpleLog()
    {
    }

    /** 日志
    */
    virtual void Log();

    /** 添加一个执行器
    */
    inline void PushExecutor(const std::shared_ptr<ILogExecutor>& executor)
    {
        m_executors.push_back(executor);
    }

protected:
    /** 格式化日志字符串
    @param [out] outLogStr 输出字符串
    @return 是否成功
    */
    virtual bool MakeLogStr(DogString& outLogStr) = 0;

protected:
    /** 日志内容
    */
    DogString m_logStr;

    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;

    /** 后续执行器
    */
    std::vector<std::shared_ptr<ILogExecutor> > m_executors;
};

/** 一个简单日志处理类，对日志做了基础信息（文件、行数、日志等级）的formate
*/
class SimpleLog :
    public ISimpleLog
{
public:
    /** 构造函数
    @param [in] level 日志等会
    @param [in] logStr 日志具体内容
    */
    SimpleLog(LogDogConfigLevel level, const DogString& logStr) :
        ISimpleLog(level, logStr)
    {

    }

    /** 析构函数
    */
    ~SimpleLog()
    {

    }

protected:
    /** 格式化日志字符串
    @param [out] outLogStr 输出字符串
    @return 是否成功
    */
    virtual bool MakeLogStr(DogString& outLogStr);
};

#endif //__ILOG_H_
