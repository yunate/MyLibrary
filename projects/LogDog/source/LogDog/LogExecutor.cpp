
#include "LogExecutor.h"
#include "dir_utils/dir_utils.h"

#include <libloaderapi.h >
#include <time.h>

DumpToFileExecutor::DumpToFileExecutor(const DogString & path):
    m_path(path)
{
}

bool DumpToFileExecutor::Executor(const DogString& logStr)
{
    return false;
}

DogString DumpToFileExecutor::GetAndCreateLogFile()
{
    if (m_path.empty())
    {
        return _DogT("");
    }

    wchar_t buff[_MAX_ENV] = {0};

    if (::GetModuleFileName(0, buff, _MAX_ENV) == 0)
    {
        return _DogT("");
    }

    // ȡĩβ
    int index = 0;
    wchar_t tmp = buff[index];
    wchar_t* fileName = NULL;

    while (tmp != 0)
    {
        if (tmp == _DogT('\\') || tmp == _DogT('/'))
        {
            fileName = buff + index + 1;
        }

        tmp = buff[++index];
    }

    DogString logPath = m_path;
    logPath += tmp;
    struct tm* nowtime;
    __time64_t long_time;
    ::_time64(&long_time);
    nowtime = _localtime64(&long_time);

    return DogString();
}

bool UpLoadExecutor::Executor(const DogString & logStr)
{
    return false;
}
