#pragma once
#include <string>
#include <iostream>
#include "limit_single_instance.h"

namespace utilstest
{
    void Test_LimitSingleInstance()
    {
        LimitSingleInstance SingleInstance(L"{C5856B69-C3DE-44EF-B4A1-CBB08C6BCEB4}");

        if (SingleInstance.IsAnotherInstanceRunning())
        {
            return ;
        }
    }
}
