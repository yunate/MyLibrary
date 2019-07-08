#ifndef __CODECVT_H_
#define __CODECVT_H_


#include <string>

namespace codecvt
{
    /** 宽字符转多字符
    @param [in] wsSrc 源，编码一般为Unicode
    @param [in] sRes 结果，编码一般为Unicode
    @return 是否成功
    */
    bool UTF16ToUTF8(const std::wstring & wsSrc, std::string & sRes);

    /** 多字符转宽字符（编码一般为UNICODE码）
    @param [in] wsSrc 源，编码一般为Unicode
    @param [in] sRes 结果，编码一般为Unicode
    @return 是否成功
    */
    bool UTF8ToUTF16(const std::string  & sSrc, std::wstring & wsRes);

    /** 宽字符转ANSI（编码一般为UNICODE码）
    @param [in] wsSrc 源，编码一般为Unicode
    @param [in] sRes 结果，编码为ANSI windows下中国编码一般为GBK
    @return 是否成功
    */
    bool UTF16ToANSI(const std::wstring & wsSrc, std::string & sRes);

    /** ANSI转宽字符（编码一般为UNICODE码）
    @param [in] wsSrc 源，编码为ANSI windows下中国编码一般为GBK
    @param [in] sRes 结果，编码一般为Unicode
    @return 是否成功
    */
    bool ANSIToUTF16(const std::string  & sSrc, std::wstring & wsRes);
}

#endif




