#include "SimpleWnd.h"
#include "App.h"
#include "RegistStyle.h"

SimpleWnd::SimpleWnd()
    : BaseWindow()
    , _hWnd(0), _nWidth(0), _nHeight(0), _nX(0), _nY(0)
{
    CreateWnd();
}

SimpleWnd::~SimpleWnd()
{
}

bool SimpleWnd::CreateWnd()
{
    TString sClassName = SimpleWnd::GetWndClassName();
    _hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
        sClassName.c_str(),
        sClassName.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        GetAppIns().GetIns(),
        this);                    // 传给WM_CREATE事件响应

    if (_hWnd)
    {
        SetWidth(CW_USEDEFAULT);
        SetHeight(CW_USEDEFAULT);
        SetX(CW_USEDEFAULT);
        SetY(CW_USEDEFAULT);
        return true;
    }

    return false;
}

void SimpleWnd::SetWidth(int nWidth)
{
    _nWidth = nWidth;
}

void SimpleWnd::SetHeight(int nHeight)
{
    _nHeight = nHeight;
}

void SimpleWnd::SetX(int nX)
{
    _nX = nX;
}

void SimpleWnd::SetY(int nY)
{
    _nY = nY;
}

int SimpleWnd::GetWidth()
{
    RECT rect;
    GetClientRect(_hWnd, &rect);
    return rect.right - rect.left;
}

int SimpleWnd::GetHeight()
{
    RECT rect;
    GetClientRect(_hWnd, &rect);
    return rect.bottom - rect.top;
}

int SimpleWnd::GetX()
{
    RECT rect;
    GetClientRect(_hWnd, &rect);
    return rect.left;
}

int SimpleWnd::GetY()
{
    RECT rect;
    GetClientRect(_hWnd, &rect);
    return rect.top;
}

bool SimpleWnd::DoModel()
{
    if (!_hWnd)
    {
        return false;
    }

    UpdateWinPos();
    ::SendMessage(_hWnd, WM_INITDIALOG, 0, 0);
    ::ShowWindow(_hWnd, SW_NORMAL);

    // 消息循环，实际上可以将这个函数封装成一个类MsgLoop
    MSG msg = { 0 };
    while (1)
    {
        if (msg.message == WM_DESTROY ||
            msg.message == WM_CLOSE ||
            msg.message == WM_QUIT)
        {
            break;
        }
        
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        else
        {
            ::Sleep(1);
        }
    }

    return false;
}

bool SimpleWnd::UpdateWinPos()
{
    return TRUE == SetWindowPos(_hWnd, HWND_TOP, _nX, _nY, _nWidth, _nHeight, SWP_SHOWWINDOW);
}

TString SimpleWnd::GetWndClassName()
{
    return _T("simplewnd");
}
