
#include "LogDog/LogDog.h"
#include <windows.h>


int main()
{
    LOG_INIT(_DogT(""), _DogT("test"));
    LOG(0, LogDogConfigLevel::LDC_LEVEL_5, _DogT("test"));

    while (1)
    {
        ::Sleep(10);
    }
    LOG_UNINIT();
    //     std::shared_ptr<ILogDog> logDog = ILogDog::Create(_DogT(""), _DogT("test"));
// 
//     if (logDog == NULL)
//     {
//         return 0;
//     }

    return 1;
}
