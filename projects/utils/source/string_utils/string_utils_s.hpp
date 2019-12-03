#ifndef __STRING_UTILS_S_H_
#define __STRING_UTILS_S_H_

#include "typedef/DogString.h"
#include <vector>
#include <assert.h>

/** std::string 字符串操作
*/
namespace stringutils_s
{
    /** 遍历字符串直到
    @return 第一次符合条件或者'\0'的地方
    @note : DongStringT<tc>(pBeg, pNex - pBeg)
    */
    template<class tc, class F>
    static inline const tc* StrParseUntil(const tc* str, F func)
    {
        assert(str != NULL);
        for (; *str && !func(*str); ++str);
        return str;
    }

    /** 获得str中的一行（\r\n 或者 \n 分割）包括\r\n
    @note: DongStringT<tc>(pBeg, pNex - pBeg)
    @eg: abc\r\nce返回执行c；
    @param [in] str 字符串，以 '\0' 结尾
    @return
    */
    template<class tc>
    static inline const tc* GetLine(const tc* str)
    {
        assert(str != NULL);

        const tc* lr = StrParseUntil(str, [](tc ch)
        {
            return (ch == (tc)('\r') || ch == (tc)('\n'));
        });

        if (*lr == 0)
        {
            return lr;
        }

        if (*(lr) == (tc)('\r'))
        {
            ++lr;
        }

        if (*(lr) == (tc)('\n'))
        {
            ++lr;
        }

        return lr;
    }

    /** 查找字符串
    @param [in] str 源，是一个字符串，以'\0'结尾
    @param [in] finder，是一个字符串，以'\0'结尾
    @param [in] times，遇到的次数
    @return 遍历字符串直到第times次遇到 finder或'\0'的地方
    */
    template<class tc>
    static inline const tc* StrFind(const tc* str, const tc* finder, int times)
    {
        assert(str != NULL);
        assert(finder != NULL);
        const tc* i = str;
        const tc* ic = finder;
        int t = 0;

        while (1)
        {
            if (*i++ != *ic)
            {
                if (*i == 0)
                {
                    break;
                }

                continue;
            }

            const tc* in = i;
            ++ic;

            while (*ic == *i)
            {
                ++i;
                ++ic;

                if (*ic == 0)
                {
                    break;
                }
            }

            // 找到了
            if (*ic == 0)
            {
                if (++t == times)
                {
                    return in - 1;
                }
            }
            else
            {
                i = in;
            }

            ic = finder;
        }

        return 0;
    }

    /** 分割字符串
    @param [in] str 源，是一个字符串，以'\0'结尾
    @param [in] spliter 分隔符号，是一个字符串，以'\0'结尾
    @param [out] out 输出
    @return 是否成功
    */
    template<class tc>
    static inline void StrSplit(const tc* str, const tc* spliter, std::vector<DongStringT<tc> >& out)
    {
        assert(str != NULL);
        assert(spliter != NULL);
        const tc* beg = str;
        const tc* i = str;
        const tc* ic = spliter;

        while (1)
        {
            if (*i++ != *ic)
            {
                if (*i == 0)
                {
                    out.push_back(DongStringT<tc>(beg, i - beg));
                    break;
                }

                continue;
            }

            const tc* in = i;
            ++ic;

            while (*ic == *i)
            {
                ++i;
                ++ic;

                if (*ic == 0)
                {
                    break;
                }
            }

            // 找到了
            if (*ic == 0)
            {
                out.push_back(DongStringT<tc>(beg, in - 1 - beg));
                beg = i;
            }
            else
            {
                i = in;
            }

            ic = spliter;
        }
    }
}

#endif // __STRING_UTILS_S_H_
