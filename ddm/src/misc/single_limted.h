#ifndef single_limted_h_
#define single_limted_h_ 1

#include "base/g_def.h"
#include <vector>
#include <windows.h>
BEG_NSP_DDM

// 尝试创建并持有某些对象，用来限制实例唯一
class auto_limted
{
public:
    ~auto_limted()
    {
        for (size_t i = 0; i < m_handles.size(); ++i) {
            DD_ASSERT(m_handles[i] != nullptr);
            ::CloseHandle(m_handles[i]);
        }
    }

    // 返回false说明实例已经存在了，持有失败
    bool hold_mutex(const ddstr& mutexName)
    {
        HANDLE m_hMutex = ::CreateMutex(nullptr, FALSE, mutexName.c_str());

        if (m_hMutex != nullptr) {
            m_handles.push_back(m_hMutex);
        }

        return (ERROR_ALREADY_EXISTS != ::GetLastError());
    }

private:
    std::vector<HANDLE> m_handles;
};

END_NSP_DDM
#endif // single_limted_h_
