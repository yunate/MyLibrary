#pragma once

#include "CommonHead.h"
#include "IRegistAdapt.h"

typedef void(*SpecialInit) (WNDCLASSEX& wndClass, HINSTANCE hIns);

/*
    ������ע����
*/
class BaseWindow
{
public:
    BaseWindow();
    virtual ~BaseWindow();

protected:
    // �¼�������������_WndProc��ӵ���
    virtual LRESULT _OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    static  LRESULT CALLBACK _WndProc(HWND, UINT, WPARAM, LPARAM);

};

