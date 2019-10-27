
#include "LogImpl.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
///DecreasePriority{
void DecreasePriority::Log()
{
    ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
}
///DecreasePriority}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///SimpleLog{
std::shared_ptr<ILog> SimpleLog::Create(LogDogConfigLevel level, const DogChar* logStr)
{
    return std::shared_ptr<ILog>(new (std::nothrow)SimpleLog(level, logStr));
}

SimpleLog::SimpleLog(LogDogConfigLevel level, const DogString& logStr) :
    m_level(level),
    m_logStr(logStr)
{

}

SimpleLog::~SimpleLog()
{

}

void SimpleLog::Log()
{

}
///SimpleLog}
//////////////////////////////////////////////////////////////////////////
