#include "file_utils.h"

bool HandleFileByLineW(const std::wstring& path, const unsigned char* checker, const size_t checkSize, std::function<bool(const std::wstring&line)> callback)
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

bool HandleUCS2FileByLine(const std::wstring & path, std::function<bool(const std::wstring&line)> callback)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    return HandleFileByLineW(path, header, 2, callback);
}

bool WriteFileByBuff(const std::wstring & path, const unsigned char * header, const size_t headSize, std::function<const void* (size_t& size, bool& hasNext)> callback)
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

    const void* buff = NULL;
    size_t size = 0;
	bool hasNext = false;

    while (true)
    {
		hasNext = false;
        buff = callback(size, hasNext);

        if (buff == NULL)
        {
            break;
        }

        if (size != ::fwrite(buff, 1, size, pFile))
        {
            ::fclose(pFile);
            pFile = NULL;
            return false;
        }

		if (!hasNext)
		{
			break;
		}
    }

    ::fclose(pFile);
    pFile = NULL;
    return true;
}

bool WriteUCS2FileByBuff(const std::wstring & path, std::function<const void*(size_t& size, bool& hasNext)> callback)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    return WriteFileByBuff(path, header, 2, callback);
}
