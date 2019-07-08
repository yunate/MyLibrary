// Utils.cpp : 定义控制台应用程序的入口点。
//

#include "string_utils/Test.h"
#include "sqlite3/Test.h"
#include "memory_share/Test.h"
#include "json/Test.h"
#include "xml/Test.h"
#include "code_cvt/Test.h"
#include "init_file/Test.h"
#include "command_line_arguments/Test.h"
#include "win_registry_key/Test.h"
#include "win_api_caller/Test.h"
#include "file_utils/test.h"

namespace utilstest {}

int main()
{
//     utilstest::Test_stringutils0();
//     utilstest::Test_stringutils1();
//     utilstest::Test_MemoryShare0();
//     utilstest::Test_Sql0();
//     utilstest::Test_Json();
//     utilstest::Test_xml0();

//    utilstest::Test_codecvt0();

//    utilstest::Test_Initfile0();
//    utilstest::Test_CommandLineArguments0();
//    utilstest::Test_WinRegistryKey1();
//    utilstest::Test_WinRegistryKey0();

//    utilstest::Test_WinApiCaller0();

    utilstest::Test_FileUtils1();
    ::system("pause");
    return 0;
}

