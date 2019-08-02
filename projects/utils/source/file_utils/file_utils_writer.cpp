#include "file_utils_writer.h"
#include <tchar.h>


FileWriter::FileWriter(const std::wstring & path, const unsigned char * header, const size_t headSize) :
    m_pFile(NULL)
{
    m_pFile = ::_wfopen(path.c_str(), _T("wb"));

    if (header != NULL)
    {
        for (size_t i = 0; i < headSize; ++i)
        {
            if (::fwrite((const void*)(&header[i]), 1, 1, m_pFile) == 0)
            {
                ::fclose(m_pFile);
                m_pFile = NULL;
            }
        }
    }

}

FileWriter::~FileWriter()
{
}

bool FileWriter::WriteBuffW(const wchar_t * buff, const size_t size)
{
    if (buff == NULL)
    {
        return false;
    }

    if (size != ::fwrite(buff, 2, size, m_pFile))
    {
        return false;
    }

    return true;
}

bool FileWriter::WriteBuffA(const char * buff, const size_t size)
{
    if (buff == NULL)
    {
        return false;
    }

    if (size != ::fwrite(buff, 1, size, m_pFile))
    {
        return false;
    }

    return true;
}

