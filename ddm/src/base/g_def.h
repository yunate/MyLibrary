
#ifndef g_def_h_
#define g_def_h_ 1

// 命名空间宏 DDM for dog_doggy_man
#define NSP_DDM ddm
#define BEG_NSP_DDM namespace NSP_DDM {
#define END_NSP_DDM }

/////////////////////////////////////数字定义/////////////////////////////////////
// 无符号
BEG_NSP_DDM
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned long;
using u64 = unsigned long long;

// 有符号
using s8 = char;
using s16 = short;
using s32 = long;
using s64 = long long;

// 32位有符号数最大值
#define MAX_S32 0x7fffffff

// 32位无符号数最大值
#define MAX_U32 0xffffffff

// 64位有符号数最大值
#define MAX_S64 0x7fffffffffffffff

// 64位无符号数最大值
#define MAX_U64 0xffffffffffffffff

// 取64位高位
#define L64(l) ((__int64)(l) & 0xffffffff)

// 取64位低位d
#define H64(l) (((__int64)(l) >> 32) & 0xffffffff)
END_NSP_DDM

/////////////////////////////////////string/////////////////////////////////////
#include <string>
BEG_NSP_DDM
using ddstra = std::string;
using ddstrw = std::wstring;
using ddchara = char;
using ddcharw = wchar_t;

#ifdef _UNICODE
#define _DDT(x) L ## x
using ddstr = ddstrw;
using ddchar = ddcharw;
#else
#define _DDT
using ddstr = ddstra;
using ddchar = ddchara;
#endif // 

// string 对于 tc 的模板
template<class tc>
using ddstrt = std::basic_string<tc, std::char_traits<tc>, std::allocator<tc> >;
END_NSP_DDM

/////////////////////////////////////buff/////////////////////////////////////
#include <vector>
BEG_NSP_DDM
using ddbuffa = std::vector<char>;
using ddbuffw = std::vector<wchar_t>;

#ifdef _UNICODE
using ddbuff = ddbuffw;
#else
using ddbuff = ddbuffa;
#endif //

// ddbuff 对于 tc 的模板
template<class tc>
using ddbufft = std::vector<tc>;
END_NSP_DDM

//////////////////////////////////assert////////////////////////////////////////
BEG_NSP_DDM
#undef DD_ASSERT
#ifdef _DEBUG
#include <assert.h>
#define DD_ASSERT(e) assert(e)
#else
#define DD_ASSERT(x) ((void)0)
#endif // _DEBUG
END_NSP_DDM
#endif // g_def_h_
