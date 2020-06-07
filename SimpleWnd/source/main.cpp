
#include "SimpleWnd/App.h"
#include "SimpleWnd/SimpleWnd.h"

class MyWnd :
    public SimpleWnd
{
public:
    MyWnd()
    {
    }

    ~MyWnd()
    {

    }

    /** ����window��λ��
    @param [in] rect ����λ��
    */
    inline void SetRect(const RECT& rect)
    {
        SimpleWnd::SetX(rect.left);
        SimpleWnd::SetY(rect.top);
        SimpleWnd::SetWidth(rect.right - rect.left);
        SimpleWnd::SetHeight(rect.bottom - rect.top);
    }

    // �¼�������������_WndProc��ӵ���
    virtual LRESULT _OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        bool isHandle = false;
        LRESULT result = 0;

        switch (msg)
        {
        case WM_PAINT:
            {
               
                break;
            }
        case WM_INITDIALOG:
            {
                
                break;
            }
        }

        if (!isHandle)
        {
            return SimpleWnd::_OnEvent(hWnd, msg, wParam, lParam);
        }

        return result;
    }
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       nCmdShow)
{
    App* pApp = &GetAppIns();
    pApp->SetIns(hInstance);
    pApp->RegistAllWnd();

    // ���߼�
    {
        MyWnd myWnd;
        myWnd.SetRect({ 500, 200, 1500, 900 });
        myWnd.DoModel();
    }

    pApp->UnRegistAllWnd();
    return 0;
}