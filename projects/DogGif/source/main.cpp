
#include "DogGif/DogGif.h"
#include "file_utils_writer.h"
#include "file_utils_reader.h"
#include "simple_wnd/App.h"
#include "simple_wnd/SimpleWnd.h"
using namespace DogGifNSP;

class MyWnd :
    public SimpleWnd
{
public:
    MyWnd()
    {
        m_hBitMap = NULL;
        timer = false;
    }

    /** 设置window的位置
    @param [in] rect 窗口位置
    */
    inline void SetRect(const RECT& rect)
    {
        SimpleWnd::SetX(rect.left);
        SimpleWnd::SetY(rect.top);
        SimpleWnd::SetWidth(rect.right - rect.left);
        SimpleWnd::SetHeight(rect.bottom - rect.top);
    }

    // 事件处理函数，函数_WndProc间接调用
    virtual LRESULT _OnEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        bool isHandle = false;
        LRESULT result = 0;

        switch (msg)
        {
        case WM_PAINT:
            {
                if (!m_gif.HasInit())
                {
                    return false;
                }

                if (!timer)
                {
                    timer = true;
                    ::SetTimer(GetWnd(), 0xffee, m_gif.GetTimeDelay(), NULL);
                }

                if (m_hBitMap != NULL)
                {
                    ::DeleteObject(m_hBitMap);
                    m_hBitMap = NULL;
                }
                DogGifColor* pBuffData;
                u32 buffLen;
                m_gif.GetNextFrame(&pBuffData, buffLen);

                m_hBitMap = ::CreateBitmap((int)m_gif.GetWidth(),
                    (int)m_gif.GetHeight(),
                    1,
                    32,
                    pBuffData);

                PAINTSTRUCT ps;
                RECT backRect = { 0, 0, GetWidth(), GetHeight() };
                ::InvalidateRect(GetWnd(), &backRect, FALSE);
                HDC hdc = ::BeginPaint(hWnd, &ps);
                HBRUSH brush = ::CreatePatternBrush(m_hBitMap);
                RECT rect = { 0, 0, (int)m_gif.GetWidth(), (int)m_gif.GetHeight() };
                ::FillRect(hdc, &rect, brush);
                ::DeleteObject(brush);
                ::EndPaint(hWnd, &ps);
                break;
            }
        case WM_INITDIALOG:
            {
                FileReader reader(L"D:\\workspaces\\C++_workspaces\\MyLibrary\\projects\\DogGif\\test\\4.gif", NULL, 0);
                size_t fileSize = reader.GetFileSize();
                u8* pBuff = new u8[fileSize];
                reader.GetBuff((char*)pBuff, fileSize);
                m_gif.Init(pBuff, fileSize);
                delete[] pBuff;
                break;
            }
        case WM_TIMER:
            switch (wParam)
            {
            case 0xffee:
                {
                    ::SendMessage(GetWnd(), WM_PAINT, 0, 0);
                    RECT backRect = { 0, 0, GetWidth(), GetHeight() };
                    isHandle = true; 
                }
            }
        }

        if (!isHandle)
        {
            return SimpleWnd::_OnEvent(hWnd, msg, wParam, lParam);
        }

        return result;
    }

protected:
    /** 图片缓存
    */
    HBITMAP m_hBitMap;

    DogGif m_gif;
    bool timer;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       nCmdShow)
{
    App* pApp = &GetAppIns();
    pApp->SetIns(hInstance);
    pApp->RegistAllWnd();

    // 主逻辑
    {
        MyWnd myWnd;
        myWnd.SetRect({ 500, 200, 1500, 900 });
        myWnd.DoModel();
    }

    pApp->UnRegistAllWnd();
    return 0;
}



int main___()
{
    FileReader reader(L"D:\\workspaces\\C++_workspaces\\MyLibrary\\projects\\DogGif\\test\\test.gif", NULL, 0);
    size_t fileSize = reader.GetFileSize();
    u8* pBuff = new u8[fileSize];
    reader.GetBuff((char*)pBuff, fileSize);
    DogGif gif;
    gif.Init(pBuff, fileSize);
    DogGifColor* pbuff;
    u32 buffLen;
    gif.GetNextFrame(&pbuff, buffLen);

    FileWriter writer(L"D:\\workspaces\\C++_workspaces\\MyLibrary\\projects\\DogGif\\test\\1.bmp", NULL, 0);
    writer.WriteBuffA((const char*)pbuff, buffLen);
    return 1;
}
