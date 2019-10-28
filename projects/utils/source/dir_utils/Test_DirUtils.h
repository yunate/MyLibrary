
#pragma once

#include "dir_utils.h"

namespace utilstest
{
    static void Test_DirUtils()
    {
        dir_uitls::CreateDirEx(L"E:\\aa\\bb\\cc");
        dir_uitls::CreateDirEx(L"E:\\aa\\bb1\\cc1\\");
        dir_uitls::CreateDirEx(L"E:/aa/bb2\\cc2\\");
        dir_uitls::CreateDirEx(L"E:/aa/bb2/cc2/");
    }
}
