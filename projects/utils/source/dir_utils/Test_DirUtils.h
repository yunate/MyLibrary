
#pragma once

#include "dir_utils.h"
#include <tchar.h>

namespace utilstest
{
    static void Test_DirUtils()
    {
        dir_uitls::CreateDirEx(_T("E:\\aa\\bb\\cc"));
        dir_uitls::CreateDirEx(_T("E:\\aa\\bb1\\cc1\\"));
        dir_uitls::CreateDirEx(_T("E:/aa/bb2\\cc2\\"));
        dir_uitls::CreateDirEx(_T("E:/aa/bb2/cc2/"));
    }
}
