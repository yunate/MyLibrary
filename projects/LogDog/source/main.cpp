
#include "LogDog/LogDog.h"
#include <windows.h>


int main()
{
    LOG_INIT(_DogT(""), _DogT("test"));

    while (1)
    {
        ::Sleep(10);
    }
    LOG_UNINIT();


    return 1;
}
