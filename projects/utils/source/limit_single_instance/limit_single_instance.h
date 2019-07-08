#ifndef __LIMITSINGLEINSTANCE_H_
#define __LIMITSINGLEINSTANCE_H_

#include <windows.h>

/** 限制进程实例唯一
*/
class LimitSingleInstance
{
public:
    /** 构造函数
    */
    LimitSingleInstance(LPCTSTR strInstanceUUID)
    {
        m_hMutex = ::CreateMutex(NULL, FALSE, strInstanceUUID);
        m_dwLastError = ::GetLastError();
    }

    /** 析构函数
    */
    ~LimitSingleInstance()
    {
        if (m_hMutex) 
        {
            ::CloseHandle(m_hMutex);
        }
    }

    /** 是否已经在运行了
    @return 是否在运行
    */
    BOOL IsAnotherInstanceRunning()
    {
        return (ERROR_ALREADY_EXISTS == m_dwLastError);
    }

private:
    /** last_error
    */
    DWORD  m_dwLastError;

    /** 句柄
    */
    HANDLE m_hMutex;
};

#endif // LIMITSINGLEINSTANCE_H