#pragma once

#include "ShareMemory.h"

namespace utilstest
{
    static void Test_MemoryShare0()
    {
        ShareMemory share;
        share.Create(L"test share", 100);
        char* p = (char*)share.GetBuff();
        ::memset(p, 0, 101);
        std::wstring ss = L"this is test";
        ::memcpy(p, ss.c_str(), ss.length() * 2);
    }

    static void Test_MemoryShare1()
    {
        ShareMemory share;
        share.Create(L"test share", 100);
        char* p = (char*)share.GetBuff();
        std::wstring ss = (WCHAR*)p;
        ::wprintf(ss.c_str());
    }
}