#ifndef __STRING_UTILS_S_H_
#define __STRING_UTILS_S_H_

#include "typedef/DogString.h"
#include <vector>
#include <assert.h>

/** std::string �ַ�������
*/
namespace stringutils_s
{
    /** �����ַ���ֱ��
    @return ��һ�η�����������'\0'�ĵط�
    @note : DongStringT<tc>(pBeg, pNex - pBeg)
    */
    template<class tc, class F>
    static inline const tc* StrParseUntil(const tc* str, F func)
    {
        assert(str != NULL);
        for (; *str && !func(*str); ++str);
        return str;
    }

    /** ���str�е�һ�У�\r\n ���� \n �ָ����\r\n
    @note: DongStringT<tc>(pBeg, pNex - pBeg)
    @eg: abc\r\nce����ִ��c��
    @param [in] str �ַ������� '\0' ��β
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

    /** �����ַ���
    @param [in] str Դ����һ���ַ�������'\0'��β
    @param [in] finder����һ���ַ�������'\0'��β
    @param [in] times�������Ĵ���
    @return �����ַ���ֱ����times������ finder��'\0'�ĵط�
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

            // �ҵ���
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

    /** �ָ��ַ���
    @param [in] str Դ����һ���ַ�������'\0'��β
    @param [in] spliter �ָ����ţ���һ���ַ�������'\0'��β
    @param [out] out ���
    @return �Ƿ�ɹ�
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

            // �ҵ���
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
