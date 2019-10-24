#pragma once

#include "noncopyable/noncopyable.h"

namespace utilstest
{
    class No : public NonCopyable
    {
    public:
        No()
        {
        }
    };

    static void Test_NoCopyable()
    {

        No n1;
//         No n2(n1);
//         No n3;
//         n3 = n1;
    }
}
