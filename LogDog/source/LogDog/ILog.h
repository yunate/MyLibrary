
//////////////////////////////////////////////////////////////////////////
// 提供一个日志实体基类，以及一些常用的实现                                     //
//////////////////////////////////////////////////////////////////////////

#ifndef __ILOG_H_
#define __ILOG_H_

#include "ILogExecutor.h"
#include "base/nocopyable.hpp"
#include "LogDogDef.h"

#include "thread/task/i_ddtask.h"

#include <assert.h>
#include <memory>
#include <vector>

BEG_NSP_DDM
/** 日志实体
*/
class ILog :
    public i_ddtask,
    public nocopyable
{
public:
    ILog();

    virtual ~ILog();

    /** 执行任务
    */
    virtual void do_task() override;

    /** 日志任务
    */
    virtual void Log() = 0;

    /** 停止任务
    */
    virtual void stop() override
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
    ISimpleLog(LogDogConfigLevel level, const ddstr& logStr);

    /** 析构函数
    */
    virtual ~ISimpleLog();

    /** 日志
    */
    virtual void Log();

    /** 添加一个执行器
    @param [in] executor 执行器
    */
    void PushExecutor(const std::shared_ptr<ILogExecutor>& executor);

private:
    /** 格式化日志字符串
    @param [out] outLogStr 输出字符串
    @return 是否成功
    */
    virtual bool MakeLogStr(ddstr& outLogStr) = 0;

protected:
    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;

    /** 日志内容
    */
    ddstr m_logStr;

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
    @param [in] logStr 日志具体内容
    */
    SimpleLog(LogDogConfigLevel level, const ddstr& logStr);

    /** 析构函数
    */
    ~SimpleLog();

private:
    /** 格式化日志字符串
    @param [out] outLogStr 输出字符串
    @return 是否成功
    */
    virtual bool MakeLogStr(ddstr& outLogStr);
};

END_NSP_DDM
#endif //__ILOG_H_
