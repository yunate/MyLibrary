#pragma once
#include "command_line_arguments.h"

namespace utilstest
{
    inline void Test_CommandLineArguments0()
    {
        CommandLineArguments cmdLine;
        int nCount = cmdLine.argc();
        char ** cmd = cmdLine.argv();

        for (int i = 0; i < nCount; ++i)
        {
            std::string ss = cmd[i];
        }
    }
}
