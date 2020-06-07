
#include "LogDog/LogDogDef.h"
#include <windows.h>

#include <memory>
BEG_NSP_DDM
int main(int)
{
    LOG_INIT(_DDT("..\\..\\test.ini"), _DDT("测试"));


    /** 调试信息
    */
    LOG_DEBUG(_DDT("test1"));
    LOG_DEBUG(_DDT("test2"));
    LOG_WARNING(_DDT("警告"));
    LOG_ASSERT(_DDT("断言"));
    LOG_SERIOUS_ERROR(_DDT("严重错误"));
    LOG_VERY_SERIOUS_ERROR(_DDT("非常严重错误"));
    LOG_CRASH(_DDT("挂了"));

    while (1)
    {
        ::Sleep(10);
    }

    LOG_UNINIT();


    return 1;
}
END_NSP_DDM
