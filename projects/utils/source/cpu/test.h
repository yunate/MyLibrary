
#pragma once

#include "cpu_thread_count.h"
#include "singleton/singleton.h"

namespace utilstest
{
    static void Test_GetCpuCount()
    {
        unsigned int cpuThreadCOunt = Singleton<CpuCoreThreadCount>::GetInstance()->GetCount();
        cpuThreadCOunt;
    }
}
