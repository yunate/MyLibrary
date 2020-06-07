
#include "../LogDog.h"
#include "../LogDogDef.h"

#include <windows.h>
BEG_NSP_DDM
/** �����̵߳����ȼ�,�����һ���������־
*/
class DecreasePriority :
    public ILog
{
public:
    /** ��־
    */
    virtual void Log()
    {
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
    }
};

void LOG_INIT(const ddstr& path, const ddstr& name)
{
    if (!singleton<LogDog>::get_instance().Init(path, name))
    {
        return;
    }

    // ����־�̵߳����ȼ�����
    std::shared_ptr<ILog> log(new (std::nothrow)DecreasePriority());

    if (log != NULL)
    {
        singleton<LogDog>::get_instance().Push(log);
    }
}

void LOG_UNINIT()
{
    singleton<LogDog>::get_instance().UnInit();
}

void SIMPLE_LOG(LogDogConfigLevel level, const ddstr & logStr)
{
    std::shared_ptr<ISimpleLog> log(new (std::nothrow)SimpleLog(level, logStr));

    if (log == NULL)
    {
        return;
    }

    log->PushExecutor(std::make_shared<DumpToFileExecutor>());
    log->PushExecutor(std::make_shared<UpLoadExecutor>());
    singleton<LogDog>::get_instance().Push(log);
}

LogDog::LogDog()
{

}

bool LogDog::Init(const ddstr & path, const ddstr & name)
{
    // ��ʼ���������
    m_spLogQue.reset(new(std::nothrow) simple_task_thread());
    m_spLogQue->start();

    // ��ʼ�������ļ�
    m_spConfig.reset(new(std::nothrow)LogDogConfig(path, name));

    return m_spLogQue != NULL;
}

void LogDog::Push(const std::shared_ptr<ILog>& log)
{
    if (m_spLogQue != NULL)
    {
        m_spLogQue->push_task(log);
    }
}

std::shared_ptr<LogDogConfig> LogDog::GetConfig()
{
    assert(m_spConfig != NULL);
    return m_spConfig;
}

void LogDog::UnInit()
{
    m_spLogQue.swap(std::shared_ptr<simple_task_thread>());
}
END_NSP_DDM
