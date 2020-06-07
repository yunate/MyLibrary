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
    // ���ʵ�ж��󣬴������¼�
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
            ���ڴ�����ʱ���lParam��ȡ��ʵ�ж���ָ�룬�����õ�userdata��
            lParam��CreateWindowEx�������һ�������������ģ�ֻ��WM_CREATE
            �¼�����Ӧ
        */
        CREATESTRUCT*   pCreate = (CREATESTRUCT*)lParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (DWORD_PTR)pCreate->lpCreateParams);

        // ��WM_CREATE��Ϣ�׸���һ����Ϣѭ��
        return SendMessage(hWnd, msg, wParam, lParam);
    }

    return  DefWindowProc(hWnd, msg, wParam, lParam);
}
