
#ifndef _LOGIMPL_H__
#define _LOGIMPL_H__

#include "ILog.h"
#include "LogDogDef.h"
#include <memory>

/** 降低线程的优先级,这个是一个特殊的日志
*/
class DecreasePriority :
    public ILog
{
public:
    /** 日志
    */
    virtual void Log();
};

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
    static std::shared_ptr<ILog> Create(LogDogConfigLevel level, const DogChar* logStr);

    /** 构造函数
    @param [in] level 日志等会
    @param [in] logStr 日志具体内容
    */
    SimpleLog(LogDogConfigLevel level, const DogString& logStr);

    /** 析构函数
    */
    ~SimpleLog();

public:
    /** 日志
    */
    virtual void Log();

private:
    /** 日志内容
    */
    DogString m_logStr;

    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;
};

#endif

