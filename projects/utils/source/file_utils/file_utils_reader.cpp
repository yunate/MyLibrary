#include "file_utils_reader.h"
#include <tchar.h>

FileReader::FileReader(const std::wstring & path, const unsigned char* checker, const size_t checkSize) :
    m_pFile(NULL)
{
    m_pFile = ::_wfopen(path.c_str(), _T("rb"));

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
        delete m_pFile;
        m_pFile = NULL;
    }
}

bool FileReader::GetLineW(std::wstring & line)
{
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
        }
        else
        {
            line.append(1, c);
            c = ::fgetc(m_pFile);
        }
    }

    return line.length() > 0;
}
