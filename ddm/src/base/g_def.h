
#ifndef g_def_h_
#define g_def_h_ 1

// �����ռ�� DDM for dog_doggy_man
#define NSP_DDM ddm
#define BEG_NSP_DDM namespace NSP_DDM {
#define END_NSP_DDM }

/////////////////////////////////////���ֶ���/////////////////////////////////////
// �޷���
BEG_NSP_DDM
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned long;
using u64 = unsigned long long;

// �з���
using s8 = char;
using s16 = short;
using s32 = long;
using s64 = long long;

// 32λ�з��������ֵ
#define MAX_S32 0x7fffffff

// 32λ�޷��������ֵ
#define MAX_U32 0xffffffff

// 64λ�з��������ֵ
#define MAX_S64 0x7fffffffffffffff

// 64λ�޷��������ֵ
#define MAX_U64 0xffffffffffffffff

// ȡ64λ��λ
#define L64(l) ((__int64)(l) & 0xffffffff)

// ȡ64λ��λd
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

// string ���� tc ��ģ��
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

// ddbuff ���� tc ��ģ��
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


//////////////////////////////////assert_fmt////////////////////////////////////////
BEG_NSP_DDM
#ifdef _DEBUG
#include <crtdbg.h>
#   define DD_ASSERT_FMTW(expr, format, ...) \
    (void) ((!!(expr)) || \
    (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, format, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

#   define DD_ASSERT_FMTA(expr, format, ...) \
    (void) ((!!(expr)) || \
    (1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, format, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))
#else
#   define DD_ASSERT_FMTW(expr, format, ...) \
    if(!(expr)) SLOGFMTW(format,__VA_ARGS__);

#   define DD_ASSERT_FMTA(expr, format, ...) \
    if(!(expr)) SLOGFMTW(format,__VA_ARGS__);
#endif

#ifdef _UNICODE 
#   define DD_ASSERT_FMT    DD_ASSERT_FMTW
#else
#   define DD_ASSERT_FMT    DD_ASSERT_FMTA
#endif//_UNICODE
END_NSP_DDM

#endif // g_def_h_
