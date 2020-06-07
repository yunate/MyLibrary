
#include "LogDog/LogDogDef.h"
#include <windows.h>

#include <memory>
BEG_NSP_DDM
int main(int)
{
    LOG_INIT(_DDT("..\\..\\test.ini"), _DDT("����"));


    /** ������Ϣ
    */
    LOG_DEBUG(_DDT("test1"));
    LOG_DEBUG(_DDT("test2"));
    LOG_WARNING(_DDT("����"));
    LOG_ASSERT(_DDT("����"));
    LOG_SERIOUS_ERROR(_DDT("���ش���"));
    LOG_VERY_SERIOUS_ERROR(_DDT("�ǳ����ش���"));
    LOG_CRASH(_DDT("����"));

    while (1)
    {
        ::Sleep(10);
    }

    LOG_UNINIT();


    return 1;
}
END_NSP_DDM
