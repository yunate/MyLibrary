#ifndef __STRING_UTILS_S_H_
#define __STRING_UTILS_S_H_

#include "typedef/DogString.h"
#include <vector>

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
    template <class tc>
    bool StrSplit(const DongStringT<tc>& raw, tc spliter, std::vector<DongStringT<tc> >& out)
    {
        tc c = 0;
        DongStringT<tc> line;

        for (size_t i = 0; i < raw.length(); ++i)
        {
            c = raw[i];

            if (c == spliter)
            {
                out.push_back(line);
                line.clear();
            }
            else
            {
                line.append(1, c);
            }
        }

        out.push_back(line);
        return true;
    }

    /** 字符串迭代相关
    */
    template<class tc>
    struct ParseResult
    {
    public:
        /** 该次迭代结果
        */
        DongStringT<tc> value;

        /** 下次开始位置
        */
        const tc* ch;
    };

    template<class tc, class F>
    static inline ParseResult<tc> ParseUntil(const tc* str, F func)
    {
        ParseResult<tc> result{};
        tc const* ch = str;
        for (; *ch && !func(*ch); ++ch);
        result.value = DongStringT<tc>(str, ch - str);
        result.ch = ch;
        return result;
    }

    template<class tc, class F>
    static inline ParseResult<tc> ParseWhile(const tc* str, F func)
    {
        ParseResult<tc> result{};
        tc const* ch = str;
        for (; *ch && func(*ch); ++ch);
        result.value = DongStringT<tc>(str, ch - str);
        result.ch = ch;
        return result;
    }
}

#endif // __STRING_UTILS_S_H_
