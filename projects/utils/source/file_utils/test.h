#pragma once

#include "file_utils.h"
#include <vector>
#include "code_cvt/code_cvt.h"

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

        WriteUCS2FileByBuff(L"D:\\test\\1.txt", [&](size_t & size, bool& hasNext)
        {
            const void * rtn = NULL;

            if (i < buff.size())
            {
                // wchar 别忘了乘2
                size = buff[i].length() * 2; 
                rtn = (const void *)buff[i].c_str();
				hasNext = true;
                ++i;
            }

            return rtn;
        });
    }
   
    // 读文件
    static void Test_FileUtils1()
    {
        HandleUCS2FileByLine(L"D:\\test\\1.txt", [&](const std::wstring& line)
        {
            std::wcout << line.c_str() << L"\r\n";
            return true;
        });
    }

    // 读文件
    static void Test_FileUtilsUTF8()
    {
        HandleUTF8FileByLine(L"C:\\Users\\yudh\\Desktop\\test\\utf8.txt", [&](const std::string& line)
        {
            std::wstring ss;
            UTF8ToUTF16(line, ss);
            return true;
        });
    }

    static void Test_FileUtilsUTF8Bom()
    {
        HandleUTF8BomFileByLine(L"C:\\Users\\yudh\\Desktop\\test\\utf8Bom.txt", [&](const std::string& line)
        {
            std::wstring ss;
            UTF8ToUTF16(line, ss);
            return true;
        });
    }
}