#define  _CRT_SECURE_NO_WARNINGS

#include "code_cvt.h"
#include <codecvt>  

namespace codecvt
{
    bool UTF16ToUTF8(const std::wstring & wsSrc, std::string & sRes)
    {
        try
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
            sRes = wcv.to_bytes(wsSrc);
        }
        catch (const std::exception & )
        {
            return false;
        }

        return true;
    }

    bool UTF8ToUTF16(const std::string  & sSrc, std::wstring & wsRes)
    {
        try
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
            wsRes = wcv.from_bytes(sSrc);
        }
        catch (const std::exception & )
        {
            return false;
        }

        return true;
    }

    bool UTF16ToANSI(const std::wstring & wsSrc, std::string & sRes)
    {

        setlocale(LC_CTYPE, "");
        std::mbstate_t state ={};
        const wchar_t *src = wsSrc.data();
        size_t len = std::wcsrtombs(nullptr, &src, 0, &state);

        if (static_cast<size_t>(-1) != len)
        {
            char * buff = new char[len + 1];
            len = std::wcsrtombs(buff, &src, len, &state);

            if (static_cast<size_t>(-1) != len)
            {
                sRes.assign(buff, len);
            }
            else
            {
                delete buff;
                return false;
            }

            delete buff;
        }
        else
        {
            return false;
        }

        return true;
    }

    bool ANSIToUTF16(const std::string  & sSrc, std::wstring & wsRes)
    {
        setlocale(LC_CTYPE, "");
        std::mbstate_t state ={};
        const char *src = sSrc.data();
        size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);

        if (static_cast<size_t>(-1) != len)
        {
            wchar_t * buff = new wchar_t[len + 1];
            len = std::mbsrtowcs(buff, &src, len, &state);

            if (static_cast<size_t>(-1) != len)
            {
                wsRes.assign(buff, len);
            }
            else
            {
                delete buff;
                return false;
            }

            delete buff;
        }
        else
        {
            return false;
        }

        return true;
    }
}