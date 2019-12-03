#pragma once

#include "string_utils_c.h"
#include "string_utils_s.h"
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
        DogString toSplit = _DogT("a|b|c|d");
        std::vector<DogString> out;
        StrSplit(toSplit, _DogT('|'), out);

        DogStringA toSplitA = "a|b|c|d";
        std::vector<DogStringA> outA;
        StrSplit(toSplitA, '|', outA);

        DogStringW toSplitW = L"a|b|c|d";
        std::vector<DogStringW> outW;
        StrSplit(toSplitW, L'|', outW);
    }
}
