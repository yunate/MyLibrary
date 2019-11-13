#pragma once

#include "file_utils.h"
#include "big_file_utils.h"
#include "file_utils_reader.h"
#include "file_utils_writer.h"
#include "code_cvt/code_cvt.h"
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

        WriteUCS2FileByBuff(L"D:\\test\\2.txt", [&buff](std::function<bool(void*, size_t)> callback)
        {
            for (size_t i = 0; i < buff.size(); ++i)
            {
                // wchar 别忘了乘2
                if (!callback((void *)buff[i].c_str(), buff[i].length() * 2))
                {
                    return false;
                }
            }

            return true;
        });
    }
   
    // 读文件
    static void Test_FileUtils1()
    {
        ReadUCS2FileByLine(L"D:\\test\\1.txt", [&](const std::wstring& line)
        {
            std::wcout << line.c_str() << L"\r\n";
            return true;
        });
    }

    // 读文件
    static void Test_FileUtilsUTF8()
    {
        ReadUTF8FileByLine(L"C:\\Users\\yudh\\Desktop\\test\\utf8.txt", [&](const std::string& line)
        {
            std::wstring ss;
            UTF8ToUTF16_Multi(line, ss);
            return true;
        });
    }

    static void Test_FileUtilsUTF8Bom()
    {
        ReadUTF8BomFileByLine(L"C:\\Users\\yudh\\Desktop\\test\\utf8Bom.txt", [&](const std::string& line)
        {
            std::wstring ss;
            UTF8ToUTF16_Multi(line, ss);
            return true;
        });
    }

    static void Test_BigFile()
    {
        FileWriter* fileWriter = CreateUTF8FileWriter(L"F:\\test\\7_1");
        BigFileMapper fileMapper;
        fileMapper.MapFile(L"F:\\test\\7");

        SPFileBlock spFileBlock = fileMapper.GetNextBlock();
        assert(spFileBlock != NULL);

        while (spFileBlock != NULL)
        {
            fileWriter->WriteBuffA(spFileBlock->GetBlockAddr(), spFileBlock->GetSize());
            spFileBlock = fileMapper.GetNextBlock();
        }

        delete fileWriter;
    }

    static void Test_file_utils_ex()
    {
        FileReader *pReader = CreateUCS2FileReader(L"D:\\test\\1.txt");

        if (!pReader)
        {
            return;
        }

        std::wstring line = L"";
        pReader->GetLineW(line);

        while (line.length() > 0)
        {
            std::wcout << line.c_str() << L"\r\n";
            pReader->GetLineW(line);
        }

        delete pReader;

        FileWriter *pWrite = CreateUTF8FileWriter(L"D:\\test\\2.txt");

        if (!pWrite)
        {
            return;
        }

        std::string line1 = "test\r\n";
        pWrite->WriteBuffA(line1.c_str(), line1.size());
        pWrite->WriteBuffA(line1.c_str(), line1.size());
        pWrite->WriteBuffA(line1.c_str(), line1.size());
        pWrite->WriteBuffA(line1.c_str(), line1.size());

        delete pWrite;
    }
}