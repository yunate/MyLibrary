
#include "../ILogExecutor.h"
#include "../LogDog.h"

#include "code_cvt/code_cvt.h"
#include "dir_utils/dir_utils.h"
#include "stream/FileStream.h"

#include <tchar.h>
#include <time.h>
#include <Windows.h >

//////////////////////////////////////////////////////////////////////////
///DumpToFileExecutor{
/** 日志文件单个最大大小 5M
*/
const int g_file_size = 5242880;

DumpToFileExecutor::DumpToFileExecutor()
{
}

bool DumpToFileExecutor::Executor(const DogString& logStr)
{
    std::shared_ptr<LogDogConfig> spConfig = Singleton<LogDog>::GetInstance().GetConfig();

    // 需要写文件
    if (!spConfig->GetBool(_DogT("dump_to_file")))
    {
        return false;
    }

    DogString baseDirBath = spConfig->GetConfigPath();

    // 去掉文件名
    for (int i = (int)baseDirBath.length() - 1; i >= 0; --i)
    {
        if (baseDirBath[i] == _DogT('\\') || baseDirBath[i] == _DogT('/'))
        {
            baseDirBath[i] = 0;

            // resize~
            baseDirBath = baseDirBath.c_str();
            break;
        }
    }

    baseDirBath += _DogT("\\log\\");
    baseDirBath += spConfig->GetConfigName();
    baseDirBath += _DogT("\\");
    DogString path = GetAndCreateLogFile(logStr.length(), baseDirBath);
    FileStream fileStream(path.c_str());

    // 转换为utf-8编码
    DogStringA utf8Log;
#ifdef _UNICODE
    codecvt::UTF16ToUTF8_STD(logStr, utf8Log);
#else
    DogStringW tmp;
    codecvt::ANSIToUTF16(logStr, tmp);
    codecvt::UTF16ToUTF8_STD(tmp, utf8Log);
#endif // 

    fileStream.Write((const u8*)utf8Log.c_str(), (s32)utf8Log.length());
    return true;
}

DogString DumpToFileExecutor::GetAndCreateLogFile(size_t logLen, const DogString& baseDirBath)
{
    if (baseDirBath.empty())
    {
        return _DogT("");
    }

    // 获得程序模块名称
    std::vector<DogChar> buffVec;
    buffVec.resize(_MAX_ENV, 0);
    DogChar* buff = &buffVec[0];

    if (buff == NULL || ::GetModuleFileName(0, buff, _MAX_ENV) == 0)
    {
        return _DogT("");
    }

    int index = 0;
    DogChar tmp = buff[index];
    DogChar* fileName = buff;

    while (tmp != 0)
    {
        if (tmp == _DogT('\\') || tmp == _DogT('/'))
        {
            fileName = buff + index + 1;
        }

        tmp = buff[++index];
    }

    DogString logPath = baseDirBath;
    logPath += fileName;
    logPath += _DogT('\\');

    // 加上日期
    __time64_t long_time;
    ::_time64(&long_time);
    struct tm nowtime;
    ::_localtime64_s(&nowtime, &long_time);
    DogChar data[12] = {0};
    ::_stprintf_s(data, _DogT("%04d-%02d-%02d\\"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday);
    logPath += data;

    // 创建目录
    if (!dir_uitls::CreateDirEx(logPath))
    {
        return _DogT("");
    }

    // 加上文件名称（小时-0）
    DogChar hour[20] = {0};
    ::_stprintf_s(hour, _DogT("%02dh-%04d.log"), nowtime.tm_hour, 0);
    logPath += hour;

    // 检查并创建文件
    if (!CheckFileSizeAndCreate(logLen, logPath))
    {
        return _DogT("");
    }

    return logPath;
}

bool DumpToFileExecutor::CheckFileSizeAndCreate(size_t logLen, DogString& filePath)
{
    DogChar* buff = (DogChar*)filePath.c_str();
    buff += filePath.length() - 8;

    while (true)
    {
        FileStream fileStream(filePath.c_str());

        if (fileStream.Size() + logLen < g_file_size)
        {
//             // 文件是新建的话，加上文件头 0xff 0xfe 让他的编码变为 UCS-2 Little Endian
//             if (fileStream.Size() == 0)
//             {
//                 unsigned char header[] = { 0xff, 0xfe};
//                 fileStream.Write(header, 2);
//             }
            // 用utf-8编码，不然空间占用太大了
            break;
        }

        if (::_tcscmp(buff, _DogT("9999")) == 0 || !StrInc(buff, 4))
        {
            break;
        }
    }

    return true;
}

bool DumpToFileExecutor::StrInc(DogChar * buff, int len)
{
    // 进位
    int inc = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (buff[i] > _DogT('9') || buff[i] < _DogT('0'))
        {
            return false;
        }

        if (inc == 1)
        {
            if (buff[i] == _DogT('9'))
            {
                buff[i] = _DogT('0');
            }
            else
            {
                buff[i] += 1;
                inc = 0;
            }
        }
        else
        {
            if (buff[i] == _DogT('9'))
            {
                buff[i] = _DogT('0');
                inc = 1;
            }
            else
            {
                buff[i] += 1;
            }
        }

        if (inc == 0)
        {
            break;
        }
    }

    return true;
}
///DumpToFileExecutor}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///UpLoadExecutor{
bool UpLoadExecutor::Executor(const DogString & logStr)
{
    std::shared_ptr<LogDogConfig> spConfig = Singleton<LogDog>::GetInstance().GetConfig();

    // 需要上传
    if (!spConfig->GetBool(_DogT("upload")))
    {
    }

    return false;
}
///UpLoadExecutor}
//////////////////////////////////////////////////////////////////////////

