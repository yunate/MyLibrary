
#ifndef DOGBUFF
#define DOGBUFF

#include <vector>
using DogBuffA = std::vector<char>;
using DogBuffW = std::vector<wchar_t>;

#ifdef _UNICODE
    using DogBuff = DogBuffW;
#else
    using DogBuff = DogBuffA;
#endif // MULTI_CHAR

#endif
