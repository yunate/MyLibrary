#include "ShareMemortManager.h"

ShareMemortManager::ShareMemortManager()
{
}

ShareMemortManager::~ShareMemortManager()
{
    for (auto it : m_handleMap)
    {
        ::CloseHandle(it.second);
    }

    m_handleMap.clear();
}

HANDLE ShareMemortManager::Create(const std::wstring name, size_t size)
{
    HANDLE rtn = Open(name);

    if (rtn != NULL)
    {
        return rtn;
    }

    if (name.empty())
    {
        return NULL;
    }

    rtn = ::CreateFileMapping(INVALID_HANDLE_VALUE,
                              NULL,
                              PAGE_READWRITE,
                              0,
                              size,
                              (LPCWSTR)name.c_str());

    // 如果创建失败的话，尝试创建文件映射
    if (rtn == NULL)
    {
        WCHAR tmpPath[MAX_PATH + 1] = { 0 };

        if (::GetTempPath(MAX_PATH + 1, tmpPath))
        {
            std::wstring path = tmpPath;
            path += name;

            // 打开文件句柄
            HANDLE hFile = ::CreateFile(path.c_str(),
                                        GENERIC_READ | GENERIC_WRITE,
                                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                                        NULL,
                                        CREATE_ALWAYS,
                                        FILE_FLAG_OVERLAPPED,
                                        NULL);

            if (INVALID_HANDLE_VALUE != hFile)
            {
                rtn = ::CreateFileMapping(hFile,
                                          NULL, 
                                          PAGE_READWRITE,
                                          0,
                                          size,
                                          (LPCWSTR)name.c_str());
                ::CloseHandle(hFile);
            }
        }
    }

    if (rtn != NULL)
    {
        m_handleMap[name] = rtn;
    }

    return rtn;
}

HANDLE ShareMemortManager::Open(const std::wstring name)
{
    if (name.empty())
    {
        return NULL;
    }

    HANDLE rtn = Find(name);

    if (rtn != NULL)
    {
        return rtn;
    }

    rtn = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (LPCWSTR)name.c_str());

    if (rtn != NULL)
    {
        m_handleMap[name] = rtn;
    }

    return rtn;
}

HANDLE ShareMemortManager::Find(const std::wstring name)
{
    auto it = m_handleMap.find(name);

    if (it == m_handleMap.end())
    {
        return NULL;
    }

    return it->second;
}
