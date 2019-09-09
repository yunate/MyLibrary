
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
        timer = false;
        needDrawGif = false;
    }

    ~MyWnd()
    {
        for (auto it : m_gifVec)
        {
            delete it;
        }

        m_gifVec.clear();
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
                PAINTSTRUCT ps;
                HDC hdc = ::BeginPaint(hWnd, &ps);
                int left = 0;
                int top = 0;

                for (int i = 0; i < 5; ++i)
                {
                    if (m_gifVec[i]->HasInit())
                    {
                        DogGifColor* pBuffData;
                        u32 buffLen;

                        if (!needDrawGif)
                        {
                            m_gifVec[i]->GetCurrentFrame(&pBuffData, buffLen);
                        }
                        else
                        {
                            m_gifVec[i]->GetNextFrame(&pBuffData, buffLen);
                        }

                        HBITMAP bitMap = ::CreateBitmap((int)m_gifVec[i]->GetWidth(),
                            (int)m_gifVec[i]->GetHeight(),
                                                        1,
                                                        32,
                                                        pBuffData);

                        if (bitMap)
                        {
                            HBRUSH brush = ::CreatePatternBrush(bitMap);
                            RECT rect = {left, top, left + (int)m_gifVec[i]->GetWidth(), top + (int)m_gifVec[i]->GetHeight()};

                            if (left + (int)m_gifVec[i]->GetWidth() + (int)m_gifVec[i]->GetWidth() < GetWidth())
                            {
                                left += (int)m_gifVec[i]->GetWidth();
                            }
                            else
                            {
                                left = 0;
                                top += (int)m_gifVec[i]->GetHeight();
                            }

                            ::FillRect(hdc, &rect, brush);
                            ::DeleteObject(brush);
                            ::DeleteObject(bitMap);
                        }
                    }
                }

                ::EndPaint(hWnd, &ps);
                isHandle = true;
                needDrawGif = false;
                break;
            }
        case WM_INITDIALOG:
            {
                for (int i = 0; i < 5; ++i)
                {
                    m_gifVec.push_back(new DogGifNSP::DogGif);
                    FileReader reader(L"test\\1.gif", NULL, 0);
                    size_t fileSize = reader.GetFileSize();

                    if (fileSize > 0)
                    {
                        u8* pBuff = new u8[fileSize];
                        reader.GetBuff((char*)pBuff, (u32)fileSize);
                        m_gifVec[i]->Init(pBuff, (u32)fileSize);
                        delete[] pBuff;
                    }
                  
                }
               
                if (!timer)
                {
                    timer = true;
                    ::SetTimer(GetWnd(), 0xffee, m_gifVec[0]->GetTimeDelay(), NULL);
                }

                break;
            }
        case WM_TIMER:
            switch (wParam)
            {
            case 0xffee:
                {
                    needDrawGif = true;
                    RECT backRect = {0, 0, GetWidth(), GetHeight()};
                    ::InvalidateRect(GetWnd(), &backRect, FALSE);
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
    DogGif m_gif;
    std::vector<DogGif*> m_gifVec;
    bool timer;
    bool needDrawGif;
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
    gif.Init(pBuff, (u32)fileSize);
    DogGifColor* pbuff;
    u32 buffLen;
    gif.GetNextFrame(&pbuff, buffLen);

    FileWriter writer(L"D:\\workspaces\\C++_workspaces\\MyLibrary\\projects\\DogGif\\test\\1.bmp", NULL, 0);
    writer.WriteBuffA((const char*)pbuff, buffLen);
    return 1;
}
