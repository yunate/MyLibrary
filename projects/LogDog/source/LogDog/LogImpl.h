
#ifndef _LOGIMPL_H__
#define _LOGIMPL_H__

#include "ILog.h"
#include "LogDogConfig.h"
#include "LogExecutor.h"

#include <vector>
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

class ISimpleLog :
    public ILog
{
public:
    /** 构造函数
    @param [in] level 日志等会
    @param [in] logStr 日志具体内容
    */
    ISimpleLog()
    {

    }

    virtual ~ISimpleLog()
    {
    }

    /** 日志
    */
    virtual void Log();

    /** 设置等级
    @param [in] level 日志等级
    @param [in] config 日志配置
    */
    inline void Init(LogDogConfigLevel level, const std::shared_ptr <LogDogConfig>& config)
    {
        m_level = level;
        m_spConfig = config;
    }

    inline void PushExecutor(const std::shared_ptr<ILogExecutor>& executor)
    {
        m_executors.push_back(executor);
    }

private:
    /** 格式化日志字符串
    @param [out] outLogStr 输出字符串
    @return 是否成功
    */
    virtual bool MakeLogStr(DogString& outLogStr) = 0;

protected:
    /** 配置文件
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;

    /** 后续执行器
    */
    std::vector<std::shared_ptr<ILogExecutor> > m_executors;
};

class SimpleLog :
    public ISimpleLog
{
public:
    /** 构造函数
    @param [in] logStr 日志具体内容
    */
    SimpleLog(const DogString& logStr);

    /** 析构函数
    */
    ~SimpleLog();

private:
    /** 格式化日志字符串
    @param [out] outLogStr 输出字符串
    @return 是否成功
    */
    virtual bool MakeLogStr(DogString& outLogStr);

private:
    /** 日志内容
    */
    DogString m_logStr;
};

#endif

