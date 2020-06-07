#pragma once

#include <tchar.h>
#include <windows.h>
#include <string>

#ifdef UNICODE
typedef std::wstring TString;
#else
typedef std::string TString;
#endif // UNICODE
