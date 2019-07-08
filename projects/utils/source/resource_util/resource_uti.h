#ifndef __RESOURCERUIL_H_
#define __RESOURCERUIL_H_

#include <string>
#include <windows.h>

namespace resourceutil
{
    // 释放资源文件
    // hModule ： 模块句柄，比如wWinMain( _In_ HINSTANCE hInstance,...) 的hInstance
    // resourceId
    // resourceType
    // target ： 保存路径
    bool ReleaseResource(HMODULE hModule, unsigned int resourceId, const std::wstring& resourceType, const std::wstring& target);
}

#endif

