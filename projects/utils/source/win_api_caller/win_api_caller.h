#ifndef __WINAPICALLER_H_
#define __WINAPICALLER_H_

#include <windows.h>

template<typename T>
class API_Caller;
template<typename RET, typename... Args>
class API_Caller<RET(Args...)>
{
    typedef RET(WINAPI*FUNC)(Args...);

public:
    API_Caller(LPCSTR lpcModuleName, LPCSTR lpcProcessName)
        : m_hFun(0)
    {
        m_hModule = ::LoadLibraryA(lpcModuleName);

        if (!m_hModule)
        {
            return;
        }

        m_hFun = (FUNC)GetProcAddress(m_hModule, lpcProcessName);
    }

    ~API_Caller()
    {
        if (m_hModule)
        {
            FreeLibrary(m_hModule);
        }
    }

    RET operator()(Args ... args)
    {
        if (m_hFun)
        {
            return (m_hFun)(args...);
        }

        return RET();
    }

private:
    API_Caller(const API_Caller&) {};
    API_Caller & operator = (const API_Caller&) {};

private:
    HMODULE m_hModule;
    FUNC        m_hFun;
};

#endif
