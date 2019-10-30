
#ifndef __DOGSTRING_H_
#define __DOGSTRING_H_

#include <string>

using DogStringA = std::string;
using DogStringW = std::wstring;
using DogCharA = char;
using DogCharW = wchar_t;

#ifdef _UNICODE
    #define _DogT(x) L ## x
    using DogString = DogStringW;
    using DogChar = DogCharW;
#else
    #define _DogT
    using DogString = DogStringA;
    using DogChar = DogCharA;
#endif // __DOGSTRING_H_

#endif
