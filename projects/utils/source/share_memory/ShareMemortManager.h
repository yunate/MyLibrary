
#ifndef __MEMORYSHARE_MANAGER_H_
#define __MEMORYSHARE_MANAGER_H_

#include "singleton/singleton.h"

#include <string>
#include <map>
#include <Windows.h>

/** 这个是单例
*/
class ShareMemortManager
{
protected:
    ShareMemortManager();
    ~ShareMemortManager();

    // 不允许拷贝
    ShareMemortManager(const ShareMemortManager&) = delete;
    ShareMemortManager(ShareMemortManager&&) = delete;
    ShareMemortManager& operator=(const ShareMemortManager&) = delete;

public:
    /** 创建共享内存，如果已经存在则打开
    @param [in] name 共享内存名称，为空时失败
    @param [in] size 大小
    @return 映射句柄，失败返回NULL
    */
    HANDLE Create(const std::wstring name, size_t size);

    /** 打开共享内存，如果不存在则打开失败
    @param [in] name 共享内存名称，为空时失败
    @return 映射句柄，失败返回NULL
    */
    HANDLE Open(const std::wstring name);

private:
    /** 查找map是否已经存在了
    @param [in] name 共享内存名称，为空时失败
    @return 映射句柄，不存在返回NULL
    */
    HANDLE Find(const std::wstring name);

private:
    /** 内存映射句柄和他的名称的map
    */
    std::map<std::wstring, HANDLE> m_handleMap;
};

// 单例对象
#define SHAREMEMORYMANAGER() (Singleton<ShareMemortManager>::GetInstance())
#endif // __MEMORYSHARE_MANAGER_H_
