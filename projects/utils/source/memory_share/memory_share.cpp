
#include "memory_share.h"

MemoryShare::MemoryShare(const std::string & sShareName)
{
    m_hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,     // 物理文件句柄
        NULL,                     // 默认安全级别
        PAGE_READWRITE,           // 可读可写
        0,                        // 高位文件大小
        BUF_SIZE + 1,             // 低位文件大小,多出来一个用来判断是否准备好去读和写
        sShareName.c_str()        // 共享内存名称，可为NULL
    );

    // 映射缓存区视图 , 得到指向共享内存的指针
    m_lpBase = MapViewOfFile(
        m_hMapFile,               // 共享内存的句柄
        FILE_MAP_ALL_ACCESS,      // 可读写许可
        0,                        // 高位偏移量
        0,                        // 低位偏移量
        BUF_SIZE + 1              // 要映射的字节数
    );

}

MemoryShare::~MemoryShare()
{
    UnmapViewOfFile(m_lpBase);
    m_lpBase = NULL;

    // 关闭内存映射文件对象句柄
    CloseHandle(m_hMapFile);
    m_hMapFile = INVALID_HANDLE_VALUE;
}

bool MemoryShare::Write(const void * pBuf, int nSize)
{
    if (0 == m_lpBase || nSize > BUF_SIZE)
    {
        return false;
    }

    memcpy(m_lpBase, pBuf, nSize);
    char cTmp = FLAG;
    memcpy(((char *)m_lpBase) + BUF_SIZE, &cTmp, 1);

    return true;
}

bool MemoryShare::Read(void * pBuf)
{
    if (0 == m_lpBase)
    {
        return false;
    }

    memcpy(pBuf, m_lpBase, BUF_SIZE);
    return true;
}

bool MemoryShare::Clear()
{
    if (0 == m_lpBase)
    {
        return false;
    }

    memset(m_lpBase, 0, BUF_SIZE + 1);
    return true;
}

bool MemoryShare::IsReadToWrite()
{
    if (0 == m_lpBase)
    {
        return false;
    }

    char * cTmp = (((char *)m_lpBase) + BUF_SIZE);

    if (0 == (*cTmp))
    {
        return true;
    }

    return false;
}

bool MemoryShare::IsReadToRead()
{
    if (0 == m_lpBase)
    {
        return false;
    }

    char * cTmp = (((char *)m_lpBase) + BUF_SIZE);

    if (FLAG == (*cTmp))
    {
        return true;
    }

    return false;
}

int MemoryShare::GetBuffSize()
{
    return BUF_SIZE;
}
