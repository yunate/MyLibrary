#include "init_file.h"

#include <Windows.h>
#include <tchar.h>
#include <new>

IniFile::~IniFile()
{
}

IniFile::IniFile(const DogString& sPath)
    : m_sFileFullPath(sPath)
{
}

IniFile * IniFile::CreateObj(const DogString& sPath, bool bAlwaysCreate)
{
    FILE * file = 0;

    if (0 != _tfopen_s(&file, sPath.c_str(), _DogT("r")) || !file)
    {
        // 文件不存在
        if (!bAlwaysCreate)
        {
            return NULL;
        }
        else
        {
            if (0 != _tfopen_s(&file, sPath.c_str(), _DogT("a")) || !file)
            {
                // 创建文件失败
                return NULL;
            }
        }
    }
    
    fclose(file);
    return new(std::nothrow) IniFile(sPath);
}

bool IniFile::AddKey(const DogChar *  sSection, const DogChar *  sKey, const DogChar *  sValue)
{
    if (!sSection)
    {
        return false;
    }

    return 0 == ::WritePrivateProfileString(sSection, sKey, sValue, m_sFileFullPath.c_str());
}

bool IniFile::DelKey(const DogChar * sSection, const DogChar * sKey)
{
    AddKey(sSection, sKey, 0);
    return false;
}

bool IniFile::DelSection(const DogChar * sSection)
{
    return AddKey(sSection, 0, 0);
}

bool IniFile::ChangKey(const DogChar * sSection, const DogChar * sKey, const DogChar * sValue)
{
    return AddKey(sSection, sKey, sValue);
}

std::vector<DogString> IniFile::Get(const DogChar * sSection, const DogChar * sKey, const int size/* = 512*/)
{
    std::vector<DogString> rtn;
    DogChar* buff = new(std::nothrow) DogChar[size];

    if (buff == NULL)
    {
        return rtn;
    }

    ::memset(buff, 0, size);
    ::GetPrivateProfileString(sSection, sKey, _DogT(""), buff, size, m_sFileFullPath.c_str());

    if (sSection == NULL || sKey == NULL)
    {
        DogString tmp;

        for (int i = 0; i < size; ++i)
        {
            if (buff[i] == 0)
            {
                if (tmp.empty())
                {
                    break;
                }
                else
                {
                    rtn.push_back(tmp);
                    tmp.clear();
                }
            }
            else
            {
                tmp.append(1, buff[i]);
            }
        }
    }
    else
    {
        rtn.push_back(buff);
    }

    delete[]buff;
    buff = NULL;
    return rtn;
}
