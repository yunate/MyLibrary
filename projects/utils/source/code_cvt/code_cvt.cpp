#define  _CRT_SECURE_NO_WARNINGS

#include "code_cvt.h"
#include <codecvt>  

namespace codecvt
{
    typedef unsigned char byte_t;
    const byte_t kUtf8Limits[5] = {0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
    typedef unsigned __int32  uint32_t;

    bool UTF16ToUTF8_STD(const std::wstring & wsSrc, std::string & sRes)
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

    bool UTF16ToUTF8_Raw(const std::wstring & wsSrc, std::string & sRes)
    {
        return false;
    }

    bool UTF8ToUTF16_STD(const std::string  & sSrc, std::wstring & wsRes)
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

    bool Utf8_To_Utf16(wchar_t *dest, size_t *destLen, const char *src, size_t srcLen)
    {
        size_t destPos = 0, srcPos = 0;
        for (;;)
        {
            byte_t c;
            unsigned numAdds;
            if (srcPos == srcLen)
            {
                *destLen = destPos;
                return true;
            }
            c = (byte_t)src[srcPos++];

            if (c < 0x80)
            {
                if (dest)
                    dest[destPos] = (wchar_t)c;
                destPos++;
                continue;
            }
            if (c < 0xC0)
                break;
            for (numAdds = 1; numAdds < 5; numAdds++)
                if (c < kUtf8Limits[numAdds])
                    break;
            uint32_t value = (c - kUtf8Limits[numAdds - 1]);

            do
            {
                byte_t c2;
                if (srcPos == srcLen)
                    break;
                c2 = (byte_t)src[srcPos++];
                if (c2 < 0x80 || c2 >= 0xC0)
                    break;
                value <<= 6;
                value |= (c2 - 0x80);
            } while (--numAdds);

            if (value < 0x10000)
            {
                if (dest)
                    dest[destPos] = (wchar_t)value;
                destPos++;
            }
            else
            {
                value -= 0x10000;
                if (value >= 0x100000)
                    break;
                if (dest)
                {
                    dest[destPos + 0] = (wchar_t)(0xD800 + (value >> 10));
                    dest[destPos + 1] = (wchar_t)(0xDC00 + (value & 0x3FF));
                }
                destPos += 2;
            }
        }
        *destLen = destPos;
        return false;
    }

    bool UTF8ToUTF16_Raw(const std::string & src, std::wstring & des)
    {
        size_t destLen = 0;
        Utf8_To_Utf16(NULL, &destLen, src.c_str(), src.length());

        if (destLen == 0)
        {
            return false;
        }

        des.resize(destLen + 1);
        des[destLen] = 0;
        bool res = Utf8_To_Utf16((wchar_t *)des.c_str(), &destLen, src.c_str(), src.length());
        return res;
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