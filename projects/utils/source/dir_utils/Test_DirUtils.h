
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

    static void Test_EnumDir()
    {
        DogString dirPath = L"F:\\TmpWorkSpace\\accuracy";
        std::vector<DogString> pathAllVec;
        dir_uitls::EnumDir(dirPath, pathAllVec, NULL);

        std::vector<DogString> pathAllDir;
        dir_uitls::EnumDir(dirPath, pathAllDir, [](const DogString&, bool isDir){
            if (isDir)
            {
                return true;
            }

            return false;
        });

        std::vector<DogString> pathAllFile;
        dir_uitls::EnumDir(dirPath, pathAllFile, [](const DogString&, bool isDir)
        {
            if (isDir)
            {
                return false;
            }

            return true;
        });

        std::vector<DogString> pathAllTxt;
        dir_uitls::EnumDir(dirPath, pathAllTxt, [](const DogString& path, bool isDir)
        {
            if (isDir)
            {
                return false;
            }

            if (path[path.length() - 4] == L'.' &&
                path[path.length() - 3] == L't' &&
                path[path.length() - 2] == L'x' &&
                path[path.length() - 1] == L't')
            {
                return true;
            }

            return false;
        });
    }

}
