#ifndef __STRING_UTILS_S_H_
#define __STRING_UTILS_S_H_

#include <string>
#include <vector>
#include <tchar.h>

// 用string 还是 wstring
#define MULTI_CHAR

#ifdef MULTI_CHAR
#define TString std::string
#define TChar char
#define T(x)      x
#else
#define TString std::wstring
#define TChar wchar_t
#define T(x)      L ## x
#endif // MULTI_CHAR

/** std::string 字符串操作
*/
namespace stringutils_s
{
    /** 分割字符串
    @param [in] raw 源
    @param [in] spliter 分隔符号
    @param [out] out 输出
    @return 是否成功
    */
    bool StrSplit(const TString& raw, TChar& spliter, std::vector<TString>& out);
}

#endif // __STRING_UTILS_S_H_
