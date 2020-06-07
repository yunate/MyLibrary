#include "BaseWindow.h"

BaseWindow::BaseWindow()
{
}

BaseWindow::~BaseWindow()
{
}

LRESULT BaseWindow::_OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
    case WM_DESTROY:
    {
        ::PostQuitMessage(0);
    }
    break;
    case WM_CREATE:
    {
        int i = 0;
        ++i;
    }
    break;
    case WM_MOUSEMOVE:
        break;
    case WM_LBUTTONDOWN:
        break;
    case WM_LBUTTONUP:
        break;
    case WM_RBUTTONDOWN:
        break;
    case WM_RBUTTONUP:
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            break;
        default:
            break;
        }
    }
    break;
    case WM_KEYUP:
        break;
    default:
        return  DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return  S_OK;
}

LRESULT BaseWindow::_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // 获得实列对象，处理窗口事件
    BaseWindow* pThis = (BaseWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (pThis)
    {
        if (S_OK == pThis->_OnEvent(hWnd, msg, wParam, lParam))
        {
            return S_OK;
        }
    }

    if (WM_CREATE == msg)
    {
        /* 
            窗口创建的时候从lParam中取出实列对象指针，并设置到userdata中
            lParam是CreateWindowEx函数最后一个参数传过来的，只有WM_CREATE
            事件会响应
        */
        CREATESTRUCT*   pCreate = (CREATESTRUCT*)lParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (DWORD_PTR)pCreate->lpCreateParams);

        // 将WM_CREATE消息抛给下一次消息循环
        return SendMessage(hWnd, msg, wParam, lParam);
    }

    return  DefWindowProc(hWnd, msg, wParam, lParam);
}
