
#include "cpu_thread_count.h"
#include <thread>
#include <windows.h>

CpuCoreThreadCount::CpuCoreThreadCount() :
    m_cpuCoreThreadCount(0)
{
    // 通过std提供的方法获取
    m_cpuCoreThreadCount = std::thread::hardware_concurrency();

    if (m_cpuCoreThreadCount != 0)
    {
        return;
    }

    // 如果获取不到，再调用winapi尝试获取
    ::SYSTEM_INFO info;
    ::GetSystemInfo(&info);
    m_cpuCoreThreadCount = (unsigned int)info.dwNumberOfProcessors;

    // 如果还是获取不到，尝试 
    // WMIC CPU Get NumberOfCores,NumberOfLogicalProcessors /Format:List > ./cpucore.txt 
    // 命令获取，但是这儿因为这个命令可能要初始化WMIC，还要涉及文件读写而引入其他库，所以就不去尝试了
}
