
#include "../ILog.h"
#include "../LogDog.h"
#include "../LogDogDef.h"

ILog::ILog()
{
}

ILog::~ILog()
{

}

void ILog::DoTask()
{
    Log();
}

ISimpleLog::ISimpleLog(LogDogConfigLevel level, const DogString& logStr) :
    m_level(level),
    m_logStr(logStr)
{
}

ISimpleLog::~ISimpleLog()
{
}

void ISimpleLog::Log()
{
    std::shared_ptr<LogDogConfig> spConfig = Singleton<LogDog>::GetInstance().GetConfig();

    // 每次都要尝试重新加载
    spConfig->TryReload();

    // 如果配置文件加载失败的话
    if (spConfig->GetErrorCode() != LogDogConfigErrorCode::LDC_NO_ERROR)
    {
        return;
    }

    if (spConfig->GetInt32(_DogT("level")) < (int)m_level)
    {
        return;
    }

    DogString logFormated;

    if (!MakeLogStr(logFormated) || logFormated.empty())
    {
        return;
    }

    for (auto it : m_executors)
    {
        assert(it != NULL);
        it->Executor(logFormated);
    }
}

void ISimpleLog::PushExecutor(const std::shared_ptr<ILogExecutor>& executor)
{
    m_executors.push_back(executor);
}

SimpleLog::SimpleLog(LogDogConfigLevel level, const DogString& logStr) :
    ISimpleLog(level, logStr)
{

}

SimpleLog::~SimpleLog()
{
}

bool SimpleLog::MakeLogStr(DogString & outLogStr)
{
    outLogStr = m_logStr;

    switch (m_level)
    {
    case LogDogConfigLevel::LDC_LEVEL_0:
        break;
    case LogDogConfigLevel::LDC_LEVEL_1:
        break;
    case LogDogConfigLevel::LDC_LEVEL_2:
        break;
    case LogDogConfigLevel::LDC_LEVEL_3:
        break;
    case LogDogConfigLevel::LDC_LEVEL_4:
        break;
    case LogDogConfigLevel::LDC_LEVEL_5:
        break;
    case LogDogConfigLevel::LDC_LEVEL_6:
        break;
    default:
        break;
    }

    return true;
}
