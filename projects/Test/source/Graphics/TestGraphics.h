
#ifndef __TEST_GRAPHICS_H_
#define __TEST_GRAPHICS_H_

#include <windows.h>


class MyConsoleWnd
{
public:
    /** 构造函数
    */
    MyConsoleWnd();

    /** 析构函数
    */
    ~MyConsoleWnd();


public:
    /** 初始化
    @return 是否成功
    */
    bool Loop();

public:
    /** 窗口消息处理函数
    */
    HRESULT OnEvent(HWND hWnd, UINT, WPARAM, LPARAM);

private:
    /** 控制台句柄
    */
    HWND m_hWnd;
};

#endif // __TEST_GRAPHICS_H_
