
#include "MemoryStream.h"
#include <malloc.h>
#include <memory.h>
#include <assert.h>

MemoryStream::MemoryStream() :
    m_pos(0),
    m_size(0),
    m_capacity(0),
    m_pBuff(0)
{
}

MemoryStream::MemoryStream(s64 size)
{
    m_pos = 0;
    m_size = 0;
    m_capacity = 0;
    m_pBuff = 0;

    if (ReSize(size) >= size)
    {
        m_size = size;
    }
}

MemoryStream::MemoryStream(s8* pBuff, s64 size)
{
    m_pos = 0;
    m_size = 0;
    m_capacity = 0;
    m_pBuff = 0;

    if (ReSize(size) >= size)
    {
        ::memcpy(m_pBuff, pBuff, (size_t)size);
        m_size = size;
    }
}

MemoryStream::MemoryStream(const IDogStream& stream)
{
    m_pos = 0;
    m_size = 0;
    m_capacity = 0;
    m_pBuff = 0;
    *this = stream;
}

MemoryStream::MemoryStream(MemoryStream&& stream)
{
    this->m_pBuff = stream.m_pBuff;
    stream.m_pBuff = NULL;
    this->m_pos = stream.m_pos;
    stream.m_pos = 0;
    this->m_size = stream.m_size;
    stream.m_size = 0;
    this->m_capacity = stream.m_capacity;
    stream.m_capacity = 0;
}

MemoryStream & MemoryStream::operator=(const IDogStream& stream)
{
    if (this == &stream)
    {
        return *this;
    }

    if (m_pBuff)
    {
        delete m_pBuff;
        m_pBuff = NULL;
    }

    m_pos = 0;
    m_size = 0;
    m_capacity = 0;
    m_pBuff = 0;
    MemoryStream& r = (MemoryStream&)(stream);
    s64 size = r.Size();

    if (ReSize(size) >= size)
    {
        s64 pos = r.Pos();
        r.ReadAllA((u8*)m_pBuff);
        r.Seek(pos, 0);
        m_size = size;
    }

    return *this;
}

MemoryStream::~MemoryStream()
{
    if (m_pBuff)
    {
        ::free(m_pBuff);
        m_pBuff = NULL;
    }
}

s64 MemoryStream::Pos()
{
    return m_pos;
}

s64 MemoryStream::Seek(s64 offset, s64 start)
{
    m_pos = start + offset;
    assert(m_pos >= 0);

    if (m_pos >= m_size)
    {
        m_pos = m_size - 1;
    }

    return m_pos;
}

s64 MemoryStream::Size()
{
    return m_size;
}

s64 MemoryStream::ReSize(s64 newSize)
{
    assert(newSize >= 0);

    if (newSize > m_capacity)
    {
        if (ReallocMemory(newSize) >= newSize)
        {
            m_size = newSize;
        }
    }
    else
    {
        m_size = newSize;
    }
 
    return m_size;
}

s64 MemoryStream::Capacity()
{
    return m_capacity;
}

void MemoryStream::Clear()
{
    m_size = 0;
    m_pos = 0;
    ::memset(m_pBuff, 0, (size_t)m_capacity);
}

s32 MemoryStream::Read(u8 * const buff, s32 count)
{
    if (m_pos >= m_size)
    {
        return 0;
    }

    s64 endPos = count + m_pos;
    assert(endPos >= 0);

    if (endPos > m_size)
    {
        count = (s32)(m_size - m_pos);
        endPos = m_size;
    }

    ::memcpy(buff, m_pBuff + m_pos, count);
    m_pos = endPos;
    return count;
}

s32 MemoryStream::Write(const u8 * const buff, s32 count)
{
    s64 endPos = count + m_pos;
    assert(endPos >= 0);

    if (endPos > m_size)
    {
        if (ReSize(endPos) < endPos)
        {
            return 0;
        }
    }

    ::memcpy(m_pBuff + m_pos, buff, count);
    m_pos = endPos;
    return count;
}

s64 MemoryStream::ReallocMemory(s64 newSize)
{
    assert(newSize >=0);

    // 计算新的大小
    s64 calSize = (s64)CalNewSize(newSize);

    if (calSize < newSize)
    {
        return m_capacity;
    }

    void* pNewBuff = ::malloc((size_t)calSize);

    if (pNewBuff == NULL)
    {
        return m_capacity;
    }

    if (m_pBuff != NULL)
    {
        ::memcpy(pNewBuff, m_pBuff, (size_t)m_capacity);
        ::free(m_pBuff);
    }

    m_capacity = calSize;
    m_pBuff = (s8*)pNewBuff;
    return m_capacity;
}

s64 MemoryStream::CalNewSize(s64 newSize)
{
    if (newSize < m_capacity + m_capacity / 2)
    {
        newSize = m_capacity + m_capacity / 2;
    }

    return GetMinUpper(newSize, MET_DATA_SIZE);
}
