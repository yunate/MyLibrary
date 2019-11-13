
#ifndef __GETUSERINPUT_H_
#define __GETUSERINPUT_H_

#include "color_print.h"
#include "typedef/DogString.h"

/** 用户输入一行，回车结束
@param [out] line 用户输入的一行
*/
inline void GetUserInputLineW(DogStringW& line)
{
    ColorPrintf(Gray, "input>>");
    line = L"";

    while (true)
    {
        DogCharW wc = ::getwchar();

        if (wc == L'\n')
        {
            break;
        }
        else
        {
            line.append(1, wc);
        }
    }
}

/** 用户输入一行，回车结束
@param [out] line 用户输入的一行
*/
inline void GetUserInputLineA(DogStringA& line)
{
    ColorPrintf(Gray, "input>>");
    line = "";

    while (true)
    {
        DogCharA c = ::getchar();

        if (c == '\n')
        {
            break;
        }
        else
        {
            line.append(1, c);
        }
    }
}

#ifdef _UNICODE
#define GetUserInputLine GetUserInputLineW
#else
#define GetUserInputLine GetUserInputLineA
#endif // 


#endif //__GETUSERINPUT_H_
