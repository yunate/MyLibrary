
#include "ShareMemory.h"
#include "ShareMemortManager.h"

ShareMemory::ShareMemory() :
    m_pMapViewOfFile(NULL),
    m_offset(0),
    m_hMap(NULL)
{
}

ShareMemory::~ShareMemory()
{
    if (m_pMapViewOfFile)
    {
        ::UnmapViewOfFile(m_pMapViewOfFile);
        m_pMapViewOfFile = NULL;
    }
}

bool ShareMemory::Create(const std::wstring name, size_t size)
{
    if (m_hMap != NULL)
    {
        return true;
    }

    m_hMap = SHAREMEMORYMANAGER()->Create(name, size);
    return m_hMap != NULL;
}

bool ShareMemory::Open(const std::wstring name)
{
    if (m_hMap != NULL)
    {
        return true;
    }

    m_hMap = SHAREMEMORYMANAGER()->Open(name);
    return m_hMap != NULL;
}

void * ShareMemory::GetBuff(size_t offset /* = 0 */)
{
    if (m_hMap == NULL)
    {
        return NULL;
    }

    if (m_pMapViewOfFile != NULL && offset == m_offset)
    {
        return m_pMapViewOfFile;
    } 

    if (m_pMapViewOfFile)
    {
        ::UnmapViewOfFile(m_pMapViewOfFile);
        m_pMapViewOfFile = NULL;
    }

    m_offset = offset;
    m_pMapViewOfFile = ::MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, offset, 0);
    return m_pMapViewOfFile;
}
