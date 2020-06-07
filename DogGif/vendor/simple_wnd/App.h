#pragma once

#include <tchar.h>
#include <windows.h>

class App
{
public:
    ~App();

private:
    App();
    App(const App&);

public:
    // ע�����еĴ�����
    void RegistAllWnd();

    // ж�����еĴ�����
    void UnRegistAllWnd();

public:
    inline HINSTANCE GetIns() { return _hIns; }
    inline void SetIns(HINSTANCE hIns) { _hIns = hIns; };

private:
    HINSTANCE _hIns;

private:
    static App& GetSignalIns()
    {
        static App s_Ins;
        return s_Ins;
    }

    friend App& GetAppIns();
};

inline App& GetAppIns() 
{
    return App::GetSignalIns();
}

