#pragma once

#include "CommonHead.h"
#include "IRegistAdapt.h"

typedef void(*SpecialInit) (WNDCLASSEX& wndClass, HINSTANCE hIns);

/*
    窗口类注册类
*/
class BaseWindow
{
public:
    BaseWindow();
    virtual ~BaseWindow();

protected:
    // 事件处理函数，函数_WndProc间接调用
    virtual LRESULT _OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    static  LRESULT CALLBACK _WndProc(HWND, UINT, WPARAM, LPARAM);

};

