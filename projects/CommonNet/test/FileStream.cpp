
#include "FileStream.h"
#include <assert.h>
#include <string.h>
#include <tchar.h>
#include <new>

FileStream::FileStream(const DogChar* const path, const DogChar* const mode/* = NULL*/) :
    m_pPath(NULL),
    m_hFile(NULL)
{
    assert(path != NULL);
    size_t len = ::_tcslen(path);
    assert(len > 0);
    m_pPath = new (std::nothrow) DogChar[len + 1];

    if (m_pPath != NULL)
    {
        ::memcpy(m_pPath, path, len * sizeof(DogChar));
        m_pPath[len] = 0;

        if (mode == NULL)
        {
            ::_tfopen_s(&m_hFile, m_pPath, _DogT("a+b"));
        }
        else
        {
            ::_tfopen_s(&m_hFile, m_pPath, mode);
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
