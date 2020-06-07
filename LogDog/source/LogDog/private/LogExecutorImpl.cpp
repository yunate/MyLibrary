
#include "../ILogExecutor.h"
#include "../LogDog.h"

#include "str/str_utils.h"
#include "file/dir_utils.h"
#include "stream/file_stream.h"

#include <tchar.h>
#include <time.h>
#include <Windows.h >
BEG_NSP_DDM
//////////////////////////////////////////////////////////////////////////
///DumpToFileExecutor{
/** 日志文件单个最大大小 5M
*/
const int g_file_size = 5242880;

DumpToFileExecutor::DumpToFileExecutor()
{
}

bool DumpToFileExecutor::Executor(const ddstr& logStr)
{
    std::shared_ptr<LogDogConfig> spConfig = singleton<LogDog>::get_instance().GetConfig();

    // 需要写文件
    if (!spConfig->GetBool(_DDT("dump_to_file")))
    {
        return false;
    }

    ddstr baseDirBath = spConfig->GetConfigPath();

    // 去掉文件名
    for (int i = (int)baseDirBath.length() - 1; i >= 0; --i)
    {
        if (baseDirBath[i] == _DDT('\\') || baseDirBath[i] == _DDT('/'))
        {
            baseDirBath[i] = 0;

            // resize~
            baseDirBath = baseDirBath.c_str();
            break;
        }
    }

    baseDirBath += _DDT("\\log\\");
    baseDirBath += spConfig->GetConfigName();
    baseDirBath += _DDT("\\");
    ddstr path = GetAndCreateLogFile(logStr.length(), baseDirBath);
    file_stream fileStream(path.c_str());

    // 转换为utf-8编码
    ddstra utf8Log;
#ifdef _UNICODE
    str_utils::uft16_uft8(logStr, utf8Log);
#else
    ddstrW tmp;
    codecvt::ANSIToUTF16(logStr, tmp);
    codecvt::UTF16ToUTF8_STD(tmp, utf8Log);
#endif // 

    fileStream.write((const u8*)utf8Log.c_str(), (s32)utf8Log.length());
    return true;
}

ddstr DumpToFileExecutor::GetAndCreateLogFile(size_t logLen, const ddstr& baseDirBath)
{
    if (baseDirBath.empty())
    {
        return _DDT("");
    }

    // 获得程序模块名称
    std::vector<ddchar> buffVec;
    buffVec.resize(_MAX_ENV, 0);
    ddchar* buff = &buffVec[0];

    if (buff == NULL || ::GetModuleFileName(0, buff, _MAX_ENV) == 0)
    {
        return _DDT("");
    }

    int index = 0;
    ddchar tmp = buff[index];
    ddchar* fileName = buff;

    while (tmp != 0)
    {
        if (tmp == _DDT('\\') || tmp == _DDT('/'))
        {
            fileName = buff + index + 1;
        }

        tmp = buff[++index];
    }

    ddstr logPath = baseDirBath;
    logPath += fileName;
    logPath += _DDT('\\');

    // 加上日期
    __time64_t long_time;
    ::_time64(&long_time);
    struct tm nowtime;
    ::_localtime64_s(&nowtime, &long_time);
    ddchar data[12] = {0};
    ::_stprintf_s(data, _DDT("%04d-%02d-%02d\\"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday);
    logPath += data;

    // 创建目录
    if (!dir_uitls::create_dir_ex(logPath))
    {
        return _DDT("");
    }

    // 加上文件名称（小时-0）
    ddchar hour[20] = {0};
    ::_stprintf_s(hour, _DDT("%02dh-%04d.log"), nowtime.tm_hour, 0);
    logPath += hour;

    // 检查并创建文件
    if (!CheckFileSizeAndCreate(logLen, logPath))
    {
        return _DDT("");
    }

    return logPath;
}

bool DumpToFileExecutor::CheckFileSizeAndCreate(size_t logLen, ddstr& filePath)
{
    ddchar* buff = (ddchar*)filePath.c_str();
    buff += filePath.length() - 8;

    while (true)
    {
        file_stream fileStream(filePath.c_str());

        if (fileStream.size() + logLen < g_file_size)
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

        if (::_tcscmp(buff, _DDT("9999")) == 0 || !StrInc(buff, 4))
        {
            break;
        }
    }

    return true;
}

bool DumpToFileExecutor::StrInc(ddchar * buff, int len)
{
    // 进位
    int inc = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (buff[i] > _DDT('9') || buff[i] < _DDT('0'))
        {
            return false;
        }

        if (inc == 1)
        {
            if (buff[i] == _DDT('9'))
            {
                buff[i] = _DDT('0');
            }
            else
            {
                buff[i] += 1;
                inc = 0;
            }
        }
        else
        {
            if (buff[i] == _DDT('9'))
            {
                buff[i] = _DDT('0');
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
bool UpLoadExecutor::Executor(const ddstr & logStr)
{
    std::shared_ptr<LogDogConfig> spConfig = singleton<LogDog>::get_instance().GetConfig();

    // 需要上传
    if (!spConfig->GetBool(_DDT("upload")))
    {
    }

    return false;
}
///UpLoadExecutor}
//////////////////////////////////////////////////////////////////////////
END_NSP_DDM
