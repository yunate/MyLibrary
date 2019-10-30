
/****************************************************************************/
/* 提供一个使用的方法，用户可以根据需求重新改写该文件                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "ILog.h"
#include "LogDogConfig.h"

#include "singleton.h"
#include "task/SimpleTaskQueue.h"
#include <functional>
#include <unordered_map>
#include <thread>

/** 日志对象管理类，用户可以根据需求重新改写
*/
class LogDog :
    public NonCopyable
{
protected:
    LogDog()
    {
    }

public:
    /** 初始化
    @param [in] path 配置文件路径
    @param [in] name 配置文件中对应的secsion
    @return 日志线程是否创建成功
    */
    inline bool Init(const DogString& path, const DogString& name)
    {
        // 初始化任务队列
        m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());
        m_spLogQue->Start();

        // 初始化配置文件
        m_spConfig.reset(new(std::nothrow)LogDogConfig(path, name));

        return m_spLogQue != NULL;
    }

    inline void Push(const std::shared_ptr<ILog>& log)
    {
        if (m_spLogQue != NULL)
        {
            m_spLogQue->PushTask(log);
        }
    }

    /** 释放资源，其实这个函数并不是很重要，因为单例在程序退出的时候会自己释放的，
    只是为了和init想对应
    */
    inline void UnInit()
    {
        m_spLogQue.swap(std::shared_ptr<SimpleTaskQueue>());
    }

    inline std::shared_ptr <LogDogConfig>& GetConfig()
    {
        return m_spConfig;
    }

private:
    /** 配置文件
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** 日志任务队列
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;
};

/** 降低线程的优先级,这个是一个特殊的日志
*/
#include <windows.h>
class DecreasePriority :
    public ILog
{
public:
    /** 日志
    */
    virtual void Log()
    {
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
    }
};

/** 初始化
@param [in] path 配置文件路径
@param [in] name 配置文件中对应的secsion
*/
inline void LOG_INIT(const DogString& path, const DogString& name)
{
    if (!Singleton<LogDog>::GetInstance().Init(path, name))
    {
        return;
    }

    {
        // 将日志线程的优先级降低
        std::shared_ptr<ILog> log(new (std::nothrow)DecreasePriority());

        if (log != NULL)
        {
            Singleton<LogDog>::GetInstance().Push(log);
        }
    }
}

/** 反初始化
*/
inline void LOG_UNINIT()
{
    Singleton<LogDog>::GetInstance().UnInit();
}

/** 简单日志
@param [in] level 日志等级
@param [in] logStr 日志具体内容
*/
inline void SIMPLE_LOG(LogDogConfigLevel level, const DogString& logStr)
{
    // 将日志线程的优先级降低
    std::shared_ptr<ISimpleLog> log(new (std::nothrow)SimpleLog(logStr));

    if (log == NULL)
    {
        return;
    }

    log->Init(level, Singleton<LogDog>::GetInstance().GetConfig());
    log->PushExecutor(std::make_shared<DumpToFileExecutor>());
    log->PushExecutor(std::make_shared<UpLoadExecutor>());
    Singleton<LogDog>::GetInstance().Push(log);
}

/** 调试信息
*/
#define LOG_DEBUG(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_6, logStr)

/** 普通信息
*/
#define LOG_INFO(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_5, logStr)

/** 警告
*/
#define LOG_WARNING(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_4, logStr)

/** assert 比如判空/分母为0
*/
#define LOG_ASSERT(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_3, logStr)

/** 严重的错误，比如资源不足了等
*/
#define LOG_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_2, logStr)

/** 极其严重的错误，我不知道和崩溃有啥区别o_0
*/
#define LOG_VERY_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_1, logStr)

/** 程序崩溃错误，崩溃了为什么能够打日志？其实我也不知道
@note try catch中的崩溃上报
*/
#define LOG_CRASH(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_0, logStr)

#endif

