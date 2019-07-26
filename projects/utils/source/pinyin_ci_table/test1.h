#pragma once

#include "CiToPinYin.h"
#include "singleton/singleton.h"

namespace utilstest
{
    static void Test_StrToPinYin()
    {
        std::vector<std::wstring> out;
        Singleton<CiToPinYin>::GetInstance()->GetStrPinYin(L"ÐÐºÍËµ", out);
    }
   
}