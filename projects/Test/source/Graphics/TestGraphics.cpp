
#include "GolMacro.h"

//#define TEST_GRAPHICS
#ifdef TEST_GRAPHICS
#include "TestGraphics.h"

MyConsoleWnd::MyConsoleWnd() :
    m_hWnd(NULL)
{
}

MyConsoleWnd::~MyConsoleWnd()
{
}

LRESULT MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // 获得实列对象，处理窗口事件
    MyConsoleWnd* pThis = (MyConsoleWnd*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (pThis != NULL)
    {
        if (S_OK == pThis->OnEvent(hWnd, msg, wParam, lParam))
        {
            return S_OK;
        }
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

bool MyConsoleWnd::Loop()
{
    HWND m_hWnd = ::GetConsoleWindow();

    if (m_hWnd == NULL)
    {
        return false;
    }

    long res = ::SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
    res = ::SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)MyWndProc);

    ::SendMessage(m_hWnd, WM_INITDIALOG, 0, 0);
    ::ShowWindow(m_hWnd, SW_NORMAL);

    // 消息循环，实际上可以将这个函数封装成一个类MsgLoop
    MSG msg = {0};
    while (1)
    {
        // 放到前面，允许程序响应一次这些消息
        if (msg.message == WM_DESTROY ||
            msg.message == WM_CLOSE ||
            msg.message == WM_QUIT)
        {
            break;
        }

        if (::GetMessage(&msg, m_hWnd, 0, 0))
        {
            if (::PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
            else
            {
                break;
            }
        }
    }

    return true;
}

HRESULT MyConsoleWnd::OnEvent(HWND hWnd, UINT, WPARAM, LPARAM)
{
    return E_NOTIMPL;
}

#endif // TEST_GRAPHICS
