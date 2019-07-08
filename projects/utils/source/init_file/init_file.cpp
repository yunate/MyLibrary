#include "init_file.h"

#include <Windows.h>

IniFile::~IniFile()
{
}

IniFile::IniFile(std::string sPath)
    : m_sFileFullPath(sPath)
{
}

IniFile * IniFile::CreateObj(const std::string sPath, bool bAlwaysCreate)
{
    FILE * file = 0;

    if (0 != fopen_s(&file, sPath.c_str(), "r") || !file)
    {
        // 文件不存在
        if (!bAlwaysCreate)
        {
            return 0;
        }
        else
        {
            if (0 != fopen_s(&file, sPath.c_str(), "a") || !file)
            {
                // 创建文件失败
                return 0;
            }
        }
    }
    
    fclose(file);
    return new IniFile(sPath);
}

bool IniFile::AddKey(const char *  sSection, const char *  sKey, const char *  sValue)
{
    if (!sSection)
    {
        return false;
    }

    return 0 == WritePrivateProfileStringA(sSection, sKey, sValue, m_sFileFullPath.c_str());
}

bool IniFile::DelKey(const char * sSection, const char * sKey)
{
    AddKey(sSection, sKey, 0);
    return false;
}

bool IniFile::DelSection(const char * sSection)
{
    return AddKey(sSection, 0, 0);
}

bool IniFile::ChangKey(const char * sSection, const char * sKey, const char * sValue)
{
    return AddKey(sSection, sKey, sValue);
}

std::string IniFile::GetKey(const char * sSection, const char * sKey)
{
    char sReturn[MAX_PATH] = { 0 };
    GetPrivateProfileStringA(sSection, sKey, "", sReturn, sizeof(sReturn), m_sFileFullPath.c_str());
    return std::string(sReturn);
}
