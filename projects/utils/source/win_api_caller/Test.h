#pragma once

#include "win_api_caller.h"
int getSize() { return 0; }

namespace utilstest
{
    static void Test_WinApiCaller0()
    {
        API_Caller<BOOL(PVOID *)> Disable("Kernel32.dll", "Wow64DisableWow64FsRedirection");
        PVOID OldValue = NULL;
        BOOL b = Disable(&OldValue);

        API_Caller<BOOL(PVOID)> Enable("Kernel32.dll", "Wow64RevertWow64FsRedirection");
        b = Enable(OldValue);

        API_Caller<BOOL(LPCWSTR)> deleteFile("Kernel32.dll", "DeleteFileW");
        b = deleteFile(L"C:\\Users\\ydh\\Desktop\\aa\\q.txt");
    }
}