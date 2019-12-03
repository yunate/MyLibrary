#pragma once

#include "string_utils_c.h"
#include "string_utils_s.hpp"
#include "typedef/DogString.h"

namespace utilstest
{
    using namespace stringutils_c;
    using namespace stringutils_s;

    static void Test_stringutils0()
    {
        strwildcard("cabcd", "*a", true);
    }

    static void Test_stringutils1()
    {
        bool b = strwildcard("н╒пе", "*в╒", true);
        b = 0 != strstr("н╒пе", "н╒пе", true);
    }

    static void Test_stringutils2()
    {
        DogString toSplit = _DogT("+=+aaa+=+bbb+=+ccc+=+ddd+=+");
        std::vector<DogString> out;
        StrSplit(toSplit.c_str(), _DogT("+=+"), out);

        DogStringA toSplitA = "+=+aaa+=+bbb+=+ccc+=+ddd";
        std::vector<DogStringA> outA;
        StrSplit(toSplitA.c_str(), "+=+", outA);

        DogStringW toSplitW = L"aaa+=+bbb+=+ccc+=+ddd";
        std::vector<DogStringW> outW;
        StrSplit(toSplitW.c_str(), L"+=+", outW);

        DogStringW toSplitW1 = L"++aaa+=+bbb+=+ccc+=+ddd";
        std::vector<DogStringW> outW1;
        StrSplit(toSplitW1.c_str(), L"+=+", outW1);

        DogStringW toSplitW2 = L"aaa+=+bbb+=+ccc+=+ddd+";
        std::vector<DogStringW> outW2;
        StrSplit(toSplitW2.c_str(), L"+=+", outW2);
    }
}
