
#include "FileStream.h"
#include <assert.h>
#include <string.h>
#include <new>

FileStream::FileStream(const char * const path, const char* const mode) :
    m_pPath(NULL),
    m_hFile(NULL)
{
    assert(path != NULL);
    size_t len = ::strlen(path);
    assert(len > 0);
    m_pPath = new (std::nothrow) char[len + 1];

    if (m_pPath != NULL)
    {
        ::memcpy(m_pPath, path, len);
        m_pPath[len] = 0;

        if (mode == NULL)
        {
            ::fopen_s(&m_hFile, m_pPath, "a+b");
        }
        else
        {
            ::fopen_s(&m_hFile, m_pPath, mode);
        }
    }

    assert(m_hFile != NULL);
}

FileStream::FileStream(FileStream && stream) noexcept
{
    m_pPath = stream.m_pPath;
    m_hFile = stream.m_hFile;
    stream.m_pPath = NULL;
    stream.m_hFile = NULL;
}

FileStream::~FileStream()
{
    if (m_pPath)
    {
        delete m_pPath;
        m_pPath = NULL;
    }

    if (m_hFile)
    {
        ::fclose(m_hFile);
        m_hFile = NULL;
    }
}

s64 FileStream::Pos()
{
    assert(m_hFile != NULL);
    return ::_ftelli64(m_hFile);
}

s64 FileStream::Seek(s64 offset, int origin)
{
    assert(m_hFile != NULL);
    ::_fseeki64(m_hFile, offset, origin);
    return Pos();
}

s64 FileStream::ReSize(s64 newSize)
{
    newSize;
    return -1;
}

s32 FileStream::Read(u8 * const buff, s32 count)
{
    assert(m_hFile != NULL && buff != NULL);
    return (s32)::fread(buff, 1, count, m_hFile);
}

s32 FileStream::Write(const u8 * const buff, s32 count)
{
    assert(m_hFile != NULL && buff != NULL);
    return (s32)::fwrite(buff, 1, count, m_hFile);
}
