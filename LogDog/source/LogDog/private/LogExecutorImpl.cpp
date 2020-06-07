
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
/** ��־�ļ���������С 5M
*/
const int g_file_size = 5242880;

DumpToFileExecutor::DumpToFileExecutor()
{
}

bool DumpToFileExecutor::Executor(const ddstr& logStr)
{
    std::shared_ptr<LogDogConfig> spConfig = singleton<LogDog>::get_instance().GetConfig();

    // ��Ҫд�ļ�
    if (!spConfig->GetBool(_DDT("dump_to_file")))
    {
        return false;
    }

    ddstr baseDirBath = spConfig->GetConfigPath();

    // ȥ���ļ���
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

    // ת��Ϊutf-8����
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

    // ��ó���ģ������
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

    // ��������
    __time64_t long_time;
    ::_time64(&long_time);
    struct tm nowtime;
    ::_localtime64_s(&nowtime, &long_time);
    ddchar data[12] = {0};
    ::_stprintf_s(data, _DDT("%04d-%02d-%02d\\"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday);
    logPath += data;

    // ����Ŀ¼
    if (!dir_uitls::create_dir_ex(logPath))
    {
        return _DDT("");
    }

    // �����ļ����ƣ�Сʱ-0��
    ddchar hour[20] = {0};
    ::_stprintf_s(hour, _DDT("%02dh-%04d.log"), nowtime.tm_hour, 0);
    logPath += hour;

    // ��鲢�����ļ�
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
//             // �ļ����½��Ļ��������ļ�ͷ 0xff 0xfe �����ı����Ϊ UCS-2 Little Endian
//             if (fileStream.Size() == 0)
//             {
//                 unsigned char header[] = { 0xff, 0xfe};
//                 fileStream.Write(header, 2);
//             }
            // ��utf-8���룬��Ȼ�ռ�ռ��̫����
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
    // ��λ
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

    // ��Ҫ�ϴ�
    if (!spConfig->GetBool(_DDT("upload")))
    {
    }

    return false;
}
///UpLoadExecutor}
//////////////////////////////////////////////////////////////////////////
END_NSP_DDM
