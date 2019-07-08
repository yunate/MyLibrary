#pragma once

#include "file_utils.h"
#include <vector>

namespace utilstest
{
    // 写文件
    static void Test_FileUtils()
    {
        std::vector <std::wstring> buff;
        buff.push_back(L"test\r\n");
        buff.push_back(L"test\r\n");
        buff.push_back(L"test\r\n");
        buff.push_back(L"test\r\n");
        size_t i = 0;

        WriteUCS2FileByBuff(L"F:\\TmpWorkSpace\\test\\1.txt", [&](size_t & size)
        {
            const void * rtn = NULL;

            if (i < buff.size())
            {
                // wchar 别忘了乘2
                size = buff[i].length() * 2; 
                rtn = (const void *)buff[i].c_str();
                ++i;
            }

            return rtn;
        });
    }
   
    // 读文件
    static void Test_FileUtils1()
    {
        HandleUCS2FileByLine(L"F:\\TmpWorkSpace\\test\\1.txt", [&](const std::wstring& line)
        {
            std::wcout << line.c_str() << L"\r\n";
            return true;
        });
    }
}