
#include "LogImpl.h"
#include "LogExecutor.h"

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

void ISimpleLog::Log()
{
    if (m_spConfig == NULL)
    {
        return;
    }

    // 每次都要尝试重新加载
    m_spConfig->TryReload();

    // 如果配置文件加载失败的话
    if (m_spConfig->GetErrorCode() != LogDogConfigErrorCode::LDC_NO_ERROR)
    {
        return;
    }

    LogDogConfigEntry& configEntry = m_spConfig->GetLogDogConfigEntry();

    if (configEntry.m_level < m_level)
    {
        return;
    }

    DogString logFormated;

    if (!MakeLogStr(logFormated) || logFormated.empty())
    {
        return;
    }

    // 需要写文件
    if (configEntry.m_isNeedDmpToFile)
    {
        DogString path = configEntry.m_path;
        path += _DogT("\\");
        path += configEntry.m_name;
        DumpToFileExecutor fileExecutor(path);
        fileExecutor.Executor(logFormated);
    }

    // 需要上传
    if (configEntry.m_isNeedUpload)
    {
        UpLoadExecutor uploadExecutor;
        uploadExecutor.Executor(logFormated);
    }
}
///SimpleLog}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///SimpleLog{

SimpleLog::SimpleLog(const DogString& logStr) :
    m_logStr(logStr)
{

}

SimpleLog::~SimpleLog()
{

}

bool SimpleLog::MakeLogStr(DogString& outLogStr)
{
    // 不要对m_spConfig判空，因为约定了判空操作在调用前
    LogDogConfigEntry& configEntry = m_spConfig->GetLogDogConfigEntry();
    
    switch (configEntry.m_level)
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
///SimpleLog}
//////////////////////////////////////////////////////////////////////////

