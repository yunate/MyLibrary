#include "TestLogDog.h"
#include "LogDog/LogDogDef.h"

#include <windows.h>

#include "AutoLib.h"
#pragma comment(lib, LIBDIR "LogDog.lib")

void LogDog()
{
    LOG_INIT(_DogT("./test.ini"), _DogT("测试"));

    /** 调试信息
    */
    LOG_DEBUG(_DogT("test1"));
    LOG_DEBUG(_DogT("test2"));
    LOG_WARNING(_DogT("警告"));
    LOG_ASSERT(_DogT("断言"));
    LOG_SERIOUS_ERROR(_DogT("严重错误"));
    LOG_VERY_SERIOUS_ERROR(_DogT("非常严重错误"));
    LOG_CRASH(_DogT("挂了"));

    while (1)
    {
        ::Sleep(10);
    }

    LOG_UNINIT();
}
