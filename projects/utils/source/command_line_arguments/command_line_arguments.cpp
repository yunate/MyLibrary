#define  _CRT_SECURE_NO_WARNINGS

#include "command_line_arguments.h"

#include <windows.h>
#include <shellapi.h>


CommandLineArguments::CommandLineArguments()
{
    LPTSTR command_line = ::GetCommandLine();
    LPWSTR *wide_argv = ::CommandLineToArgvW(command_line, &argc_);
    argv_ = new char*[argc_];

    for (int i = 0; i < argc_; ++i) 
    {
        std::string s = _W2A(wide_argv[i]);
        char *buffer = new char[s.length() + 1];
        strncpy(buffer, s.c_str(), s.length());
        buffer[s.length()] = 0;
        argv_[i] = buffer;
    }
    LocalFree(wide_argv);
}

CommandLineArguments::CommandLineArguments(const wchar_t* lpCmdLine)
{
    LPWSTR *wide_argv = ::CommandLineToArgvW(lpCmdLine, &argc_);
    argv_ = new char*[argc_];

    for (int i = 0; i < argc_; ++i) 
    {
        std::string s = _W2A(wide_argv[i]);
        char *buffer = new char[s.length() + 1];
        strncpy(buffer, s.c_str(), s.length());
        buffer[s.length()] = 0;
        argv_[i] = buffer;
    }
    LocalFree(wide_argv);
}

CommandLineArguments::~CommandLineArguments()
{
    // need to free each string in the array, and then the array.
    for (int i = 0; i < argc_; i++) 
    {
        delete[] argv_[i];
    }

    delete[] argv_;
}

std::string CommandLineArguments::_W2A(const wchar_t* src)
{
    char szBuf[1024];
    int nRet = ::WideCharToMultiByte(CP_ACP, 0, src, (int)::wcslen(src), szBuf, 1024, NULL, NULL);
    if (nRet > 0) return std::string(szBuf, nRet);

    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        nRet = ::WideCharToMultiByte(CP_ACP, 0, src, (int)::wcslen(src), NULL, 0, NULL, NULL);
        if (nRet > 0)
        {
            char *pBuf = new char[nRet];
            ::WideCharToMultiByte(CP_ACP, 0, src, (int)::wcslen(src), pBuf, nRet, NULL, NULL);
            std::string strRet(pBuf, nRet);
            delete[]pBuf;
            return strRet;
        }
    }

    return std::string();
}
