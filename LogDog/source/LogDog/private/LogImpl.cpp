
#include "base/g_def.h"
#include "../ILog.h"
#include "../LogDog.h"
#include "../LogDogDef.h"

#include <tchar.h>
#include <time.h>
BEG_NSP_DDM
ILog::ILog()
{
}

ILog::~ILog()
{

}

void ILog::do_task()
{
    Log();
}

ISimpleLog::ISimpleLog(LogDogConfigLevel level, const ddstr& logStr) :
    m_level(level),
    m_logStr(logStr)
{
}

ISimpleLog::~ISimpleLog()
{
}

void ISimpleLog::Log()
{
    std::shared_ptr<LogDogConfig> spConfig = singleton<LogDog>::get_instance().GetConfig();

    // 每次都要尝试重新加载
    spConfig->TryReload();

    // 如果配置文件加载失败的话
    if (spConfig->GetErrorCode() != LogDogConfigErrorCode::LDC_NO_ERROR)
    {
        return;
    }

    if (spConfig->GetInt32(_DDT("level")) < (int)m_level)
    {
        return;
    }

    ddstr logFormated;

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

SimpleLog::SimpleLog(LogDogConfigLevel level, const ddstr& logStr) :
    ISimpleLog(level, logStr)
{

}

SimpleLog::~SimpleLog()
{
}

bool SimpleLog::MakeLogStr(ddstr & outLogStr)
{
    // 加上日期
    __time64_t long_time;
    ::_time64(&long_time);
    struct tm nowtime;
    ::_localtime64_s(&nowtime, &long_time);
    ddchar date[24] = { 0 };
    ::_stprintf_s(date, _DDT("[%04d-%02d-%02d %02d:%02d:%02d "),
                  nowtime.tm_year + 1900,
                  nowtime.tm_mon + 1,
                  nowtime.tm_mday,
                  nowtime.tm_hour,
                  nowtime.tm_min,
                  nowtime.tm_sec);

    outLogStr = date;

    // 加上等级描述
    switch (m_level)
    {
    case LogDogConfigLevel::LDC_LEVEL_0:
        outLogStr += _DDT("CRASH");
        break;
    case LogDogConfigLevel::LDC_LEVEL_1:
        outLogStr += _DDT("VERY_SERIOUS_ERROR");
        break;
    case LogDogConfigLevel::LDC_LEVEL_2:
        outLogStr += _DDT("SERIOUS_ERROR");
        break;
    case LogDogConfigLevel::LDC_LEVEL_3:
        outLogStr += _DDT("ASSERT");
        break;
    case LogDogConfigLevel::LDC_LEVEL_4:
        outLogStr += _DDT("WARNING");
        break;
    case LogDogConfigLevel::LDC_LEVEL_5:
        outLogStr += _DDT("INFO");
        break;
    case LogDogConfigLevel::LDC_LEVEL_6:
        outLogStr += _DDT("DEBUG");
        break;
    default:
        break;
    }
    outLogStr += _DDT("] ");

    // 加上日志,如果日志尾巴是换行符号，去掉
    if (m_logStr.length() > 0)
    {
        if (m_logStr[m_logStr.length() - 1] == _DDT('\n'))
        {
            m_logStr[m_logStr.length() - 1] = 0;
        }
    }

    if (m_logStr.length() > 1)
    {
        if (m_logStr[m_logStr.length() - 2] == _DDT('\r'))
        {
            m_logStr[m_logStr.length() - 2] = 0;
        }
    }

    m_logStr = m_logStr.c_str();
    outLogStr += m_logStr;
    outLogStr += _DDT(" \r\n");
    return true;
}
END_NSP_DDM
