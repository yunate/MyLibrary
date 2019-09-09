
#include "file_utils_reader.h"
#include <tchar.h>
#include <windows.h>

FileReader::FileReader(const std::wstring & path, const unsigned char* checker, const size_t checkSize) :
    m_pFile(NULL)
{
    ::_wfopen_s(&m_pFile, path.c_str(), _T("rb"));

    if (checker != NULL)
    {
        for (size_t i = 0; i < checkSize; ++i)
        {
            int c = ::fgetc(m_pFile);

            if (c == EOF || c != checker[i])
            {
                ::fclose(m_pFile);
                m_pFile = NULL;
                break;
            }
        }
    }
}

FileReader::~FileReader()
{
    if (m_pFile != NULL)
    {
        ::fclose(m_pFile);
        m_pFile = NULL;
    }
}

bool FileReader::GetLineW(std::wstring & line)
{
    if (m_pFile == NULL)
    {
        return false;
    }

    wint_t wc = ::fgetwc(m_pFile);
    line = L"";

    while (wc != WEOF)
    {
        if (wc == L'\r' || wc == L'\n')
        {
            if (line.length() > 0)
            {
                break;
            }

            wc = ::fgetwc(m_pFile);
        }
        else
        {
            line.append(1, wc);
            wc = ::fgetwc(m_pFile);
        }
    }

    return line.length() > 0;
}

bool FileReader::GetLineA(std::string & line)
{
    if (m_pFile == NULL)
    {
        return false;
    }

    int c = ::fgetc(m_pFile);
    line = "";

    while (c != EOF)
    {
        if (c == L'\r' || c == L'\n')
        {
            if (line.length() > 0)
            {
                break;
            }

            c = ::fgetc(m_pFile);
        }
        else
        {
            line.append(1, c);
            c = ::fgetc(m_pFile);
        }
    }

    return line.length() > 0;
}

size_t FileReader::GetBuff(char * buff, const size_t & size)
{
    if (m_pFile == NULL || buff == NULL || size == 0)
    {
        return 0;
    }

    size_t pos = 0;
    int c = ::fgetc(m_pFile);

    while (c != EOF && pos != size)
    {
        buff[pos++] = c;
        c = ::fgetc(m_pFile);
    }

    return pos;
}

size_t FileReader::GetFileSize()
{
    if (m_pFile == NULL)
    {
        return 0;
    }

    long curPos = ::ftell(m_pFile);
    ::fseek(m_pFile, 0, SEEK_END);
    long size = ::ftell(m_pFile);
    ::fseek(m_pFile, 0, curPos);
    return size;
}

