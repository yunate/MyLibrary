
#ifndef __COLOR_PEINT_H_
#define __COLOR_PEINT_H_

#include <Windows.h>
#include <stdio.h>

//   控制台前景颜色
enum Color
{
    Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
    Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    Purple = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Gray = FOREGROUND_INTENSITY,
    White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    HighWhite = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Black = 0,
};

#define ColorPrintf(foreColor, fmt, ...)\
do {\
    HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);\
    CONSOLE_SCREEN_BUFFER_INFO info;\
    if (handle != NULL && ::GetConsoleScreenBufferInfo(handle, &info))\
    {\
        ::SetConsoleTextAttribute(handle, foreColor | Black);\
        ::printf(fmt, __VA_ARGS__);\
        ::SetConsoleTextAttribute(handle, info.wAttributes);\
    }\
}while (0)

#define ColorPrintfW(foreColor, fmt, ...)\
do {\
    HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);\
    CONSOLE_SCREEN_BUFFER_INFO info;\
    if (handle != NULL && ::GetConsoleScreenBufferInfo(handle, &info))\
    {\
        ::SetConsoleTextAttribute(handle, foreColor | Black);\
        ::wprintf(fmt, __VA_ARGS__);\
        ::SetConsoleTextAttribute(handle, info.wAttributes);\
    }\
}while (0)

#endif //__COLOR_PEINT_H_
