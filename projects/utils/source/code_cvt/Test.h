#pragma once

#include "code_cvt.h"

namespace utilstest
{
    using namespace codecvt;

    static void Test_codecvt0()
    {
        char sAnsiCode[]        =    "ABC与或非";         // ANSI(GBK)编码                41 42 43 d3 eb bb f2 b7 c7 00
        wchar_t wsAnsiCode[]    =    L"ABC与或非";        // Unicode（UTF-16）编码         41 00 42 00 43 00 0e 4e 16 62 5e 97 00 00

        // ANSI  转 Unicode
        std::wstring wsRes = L"";
        ANSIToUTF16(sAnsiCode, wsRes);

        // Unicode 转 ANSI 
        std::string sRes = "";
        UTF16ToANSI(wsAnsiCode, sRes);

        // 转UTF-8
        std::string sResU8 = "";
        UTF16ToUTF8_STD(wsAnsiCode, sResU8);

        // UTF-8 转 16
        std::wstring wsRes16 = L"";
        UTF8ToUTF16_Multi(sResU8, wsRes16);
    }

}

