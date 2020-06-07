#pragma once

#include "BaseWindow.h"

class SimpleWnd : public BaseWindow
{
public:
    SimpleWnd();
    virtual ~SimpleWnd();

public:
    bool CreateWnd();
    void SetWidth(int nWidth);
    void SetHeight(int nHeight);
    void SetX(int nX);
    void SetY(int nY);

    HWND GetWnd() { return _hWnd; }
    int GetWidth();
    int GetHeight();
    int GetX();
    int GetY();

public:
    virtual bool DoModel();
    virtual bool UpdateWinPos();

private:
    HWND _hWnd;
    int _nWidth;
    int _nHeight;
    int _nX;
    int _nY;

public:
    static TString GetWndClassName();
};

