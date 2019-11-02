
#include "../LogDog.h"
#include "../LogDogDef.h"

#include <windows.h>

/** 降低线程的优先级,这个是一个特殊的日志
*/
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

void LOG_INIT(const DogString& path, const DogString& name)
{
    if (!Singleton<LogDog>::GetInstance().Init(path, name))
    {
        return;
    }

    // 将日志线程的优先级降低
    std::shared_ptr<ILog> log(new (std::nothrow)DecreasePriority());

    if (log != NULL)
    {
        Singleton<LogDog>::GetInstance().Push(log);
    }
}

void LOG_UNINIT()
{
    Singleton<LogDog>::GetInstance().UnInit();
}

void SIMPLE_LOG(LogDogConfigLevel level, const DogString & logStr)
{
    std::shared_ptr<ISimpleLog> log(new (std::nothrow)SimpleLog(level, logStr));

    if (log == NULL)
    {
        return;
    }

    log->PushExecutor(std::make_shared<DumpToFileExecutor>());
    log->PushExecutor(std::make_shared<UpLoadExecutor>());
    Singleton<LogDog>::GetInstance().Push(log);
}

LogDog::LogDog()
{

}

bool LogDog::Init(const DogString & path, const DogString & name)
{
    // 初始化任务队列
    m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());
    m_spLogQue->Start();

    // 初始化配置文件
    m_spConfig.reset(new(std::nothrow)LogDogConfig(path, name));

    return m_spLogQue != NULL;
}

void LogDog::Push(const std::shared_ptr<ILog>& log)
{
    if (m_spLogQue != NULL)
    {
        m_spLogQue->PushTask(log);
    }
}

std::shared_ptr<LogDogConfig> LogDog::GetConfig()
{
    assert(m_spConfig != NULL);
    return m_spConfig;
}

void LogDog::UnInit()
{
    m_spLogQue.swap(std::shared_ptr<SimpleTaskQueue>());
}
