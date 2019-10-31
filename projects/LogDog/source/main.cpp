
#include "LogDog/LogDogDef.h"
#include <windows.h>

#include <memory>

int main()
{
    LOG_INIT(_DogT("D:\\projects\\my\\MyLibrary\\projects\\LogDog\\bin\\test.ini"), _DogT("≤‚ ‘"));


    /** µ˜ ‘–≈œ¢
    */
    LOG_DEBUG(_DogT("test1\r\n"));
    LOG_DEBUG(_DogT("test2\r\n"));
    LOG_WARNING(_DogT("test3\r\n"));
    LOG_WARNING(_DogT("test4\r\n"));

    while (1)
    {
        ::Sleep(10);
    }

    LOG_UNINIT();


    return 1;
}
