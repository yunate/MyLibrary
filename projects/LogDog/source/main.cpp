
#include "LogDog/Export/ILogDog.h"
#include "LogDog/Export/LogDog.h"


int main()
{
    LOG_BIND(LOGTYPE::LOGTYPE_SIMPLE_LOG, SimpleLog);
    LOG(0, LogDogConfigLevel::LDC_LEVEL_5, _DogT("test"));
//     std::shared_ptr<ILogDog> logDog = ILogDog::Create(_DogT(""), _DogT("test"));
// 
//     if (logDog == NULL)
//     {
//         return 0;
//     }

    return 1;
}
