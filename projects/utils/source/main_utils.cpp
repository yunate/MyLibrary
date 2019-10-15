// Utils.cpp : 定义控制台应用程序的入口点。
//

#include "string_utils/Test.h"
#include "sqlite3/Test.h"
#include "share_memory/Test.h"
#include "json/Test.h"
#include "xml/Test.h"
#include "code_cvt/Test.h"
#include "init_file/Test.h"
#include "command_line_arguments/Test.h"
#include "win_registry_key/Test.h"
#include "win_api_caller/Test.h"
#include "file_utils/test.h"
#include "singleton/test.h"
#include "cpu/test.h"
#include "thread/producer_consumer/test2.h"
#include "thread/task/Test_taskQue.h"
#include "console/test.h"
 #include "logic_executor/Test.h"
 #include "stream/Test.h"
 #include "thread/TestLockFree.h"

// 内存泄露检测器
// 没有64位的
#ifdef _DEBUG
#pragma comment(lib, "vld//release//vld.lib")
#include "vld//head//vld.h"
#include <crtdbg.h>
#include <windows.h>
#endif


namespace utilstest {}

int main()
{
    ::_CrtSetBreakAlloc(89);
    //     utilstest::Test_stringutils0();
//     utilstest::Test_stringutils1();
// utilstest::Test_MemoryShare0();
//utilstest::Test_MemoryShare1();
//     utilstest::Test_Sql0();
//     utilstest::Test_Json();
//     utilstest::Test_xml0();

//    utilstest::Test_codecvt0();

//    utilstest::Test_Initfile0();
//    utilstest::Test_CommandLineArguments0();
//    utilstest::Test_WinRegistryKey1();
//    utilstest::Test_WinRegistryKey0();

//    utilstest::Test_WinApiCaller0();

    //utilstest::Test_FileUtils();
    //utilstest::Test_FileUtilsUTF8();
    //utilstest::Test_FileUtilsUTF8Bom();
    //utilstest::Test_Singleton();
    //utilstest::Test_StrToPinYin();
    // utilstest::Test_GetCpuCount();
    //utilstest::Test_file_utils_ex();
    //utilstest::Test_ColorPrint();
    //utilstest::Test_Executor();
    //utilstest::Test_taskQue();
    //utilstest::Test_taskQue1();

   // utilstest::Test_MemoryStream();
    //utilstest::Test_FileStream();
    utilstest::Test_LockFreeQue();
    ::system("pause");
    return 1;
}

