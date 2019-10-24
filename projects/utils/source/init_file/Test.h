#pragma once
#include "init_file.h"

namespace utilstest
{
    inline void Test_Initfile0()
    {
        IniFile * pInitFIle = IniFile::CreateObj(L"E:\\aa\\1.ini", true);

        if (!pInitFIle)
        {
            return;
        }

        pInitFIle->AddKey(L"Sec1", L"key1", L"1");
        pInitFIle->AddKey(L"Sec1", L"key2", L"1");
        pInitFIle->AddKey(L"Sec1", L"key3", L"1");
        pInitFIle->AddKey(L"Sec1", L"key4", L"1");

        pInitFIle->AddKey(L"Sec2", L"key1", L"1");
        pInitFIle->AddKey(L"Sec2", L"key2", L"1");
        pInitFIle->AddKey(L"Sec2", L"key3", L"1");
        pInitFIle->AddKey(L"Sec2", L"key4", L"1");

        pInitFIle->DelKey(L"Sec1", L"key1");
        pInitFIle->DelSection(L"sec2");
        pInitFIle->ChangKey(L"sec1", L"key2", L"2");

        std::vector<DogString> ss = pInitFIle->Get(L"sec1", L"key2");
        std::vector<DogString> ss2 = pInitFIle->Get(L"sec1", 0);
        std::vector<DogString> ss1 = pInitFIle->Get(0, 0);

        delete pInitFIle;
    }
}
