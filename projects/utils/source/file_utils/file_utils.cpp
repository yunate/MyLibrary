#include "file_utils.h"

bool ReadFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback)
{
    FILE* pFile = NULL;
    ::_wfopen_s(&pFile, path.c_str(), L"rb");

    if (pFile == NULL)
    {
        return false;
    }

    if (checker != NULL)
    {
        for (size_t i = 0; i < checkSize; ++i)
        {
            int c = ::fgetc(pFile);

            if (c == EOF || c != checker[i])
            {
                ::fclose(pFile);
                pFile = NULL;
                return false;
            }
        }
    }

    wint_t wc = ::fgetwc(pFile);
    std::wstring line = L"";

    while (wc != WEOF)
    {
        if (wc != L'\r' && wc != L'\n')
        {
            line.append(1, wc);
            wc = ::fgetwc(pFile);
        }
        else
        {
            if (!callback(line))
            {
                break;
            }

            line = L"";
            wc = ::fgetwc(pFile);

            if (wc == L'\r' || wc == L'\n')
            {
                wc = ::fgetwc(pFile);
            }
        }
    }

    if (line.length() > 0)
    {
        callback(line);
    }

    ::fclose(pFile);
    pFile = NULL;
    return true;
}

bool ReadUCS2FileByLine(const std::wstring & path, std::function<bool(const std::wstring&line)> callback)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    return ReadFileByLineW(path, header, 2, callback);
}

bool ReadFileByLine(const std::wstring & path, const unsigned char * checker, const size_t checkSize, std::function<bool(const std::string&line)> callback)
{
    FILE* pFile = NULL;
    ::_wfopen_s(&pFile, path.c_str(), L"rb");

    if (pFile == NULL)
    {
        return false;
    }

    if (checker != NULL)
    {
        for (size_t i = 0; i < checkSize; ++i)
        {
            int c = ::fgetc(pFile);

            if (c == EOF || c != checker[i])
            {
                ::fclose(pFile);
                pFile = NULL;
                return false;
            }
        }
    }

    int c = ::fgetc(pFile);
    std::string line = "";

    while (c != EOF)
    {
        if (c != '\r' && c != '\n')
        {
            line.append(1, (char)c);
            c = ::fgetc(pFile);
        }
        else
        {
            if (!callback(line))
            {
                break;
            }

            line = "";
            c = ::fgetc(pFile);

            if (c == '\r' || c == '\n')
            {
                c = ::fgetc(pFile);
            }
        }
    }

    if (line.length() > 0)
    {
        callback(line);
    }

    ::fclose(pFile);
    pFile = NULL;
    return true;
}

bool ReadUTF8FileByLine(const std::wstring & path, std::function<bool(const std::string&line)> callback)
{
    return ReadFileByLine(path, NULL, 0, callback);
}

bool ReadUTF8BomFileByLine(const std::wstring & path, std::function<bool(const std::string&line)> callback)
{
    unsigned char header[] = {0xef, 0xbb, 0xbf, '\0'};
    return ReadFileByLine(path, header, 3, callback);
}

bool WriteFileByBuff(const std::wstring & path,
    const unsigned char * header,
    const size_t headSize,
    std::function<bool(std::function<bool (void*, size_t)>)> callback)
{
    FILE* pFile = NULL;
    ::_wfopen_s(&pFile, path.c_str(), L"wb");

    if (pFile == NULL)
    {
        return false;
    }

    if (header != NULL)
    {
        for (size_t i = 0; i < headSize; ++i)
        {
            if (::fwrite((const void*)(&header[i]), 1, 1, pFile) == 0)
            {
                ::fclose(pFile);
                pFile = NULL;
                return false;
            }
        }
    }

    bool res = callback([&pFile](void* buff, size_t size)
    {
        if (buff == NULL)
        {
            return false;
        }

        if (size != ::fwrite(buff, 1, size, pFile))
        {
            ::fclose(pFile);
            pFile = NULL;
            return false;
        }
        return true;
    });

    ::fclose(pFile);
    pFile = NULL;
    return res;
}

bool WriteUCS2FileByBuff(const std::wstring & path, std::function<bool(std::function<bool(void*, size_t)>)> callback)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    return WriteFileByBuff(path, header, 2, callback);
}
