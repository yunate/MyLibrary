#define _CRT_RAND_S
#include "rand.h"
#include <stdlib.h>

bool GetRandNum(int min, int max, int & out)
{
    if (max < min)
    {
        return false;
    }

    unsigned int tmp = 0;

    if (rand_s(&tmp) != 0)
    {
        return false;
    }

    out = tmp % (max - min + 1) + min;
    return true;
}
