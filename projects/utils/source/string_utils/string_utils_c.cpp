#include "string_utils_c.h"
#include <string.h>

typedef unsigned char u_char;

static u_char kAsciiLowerCase[] = {
    0x00, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
    0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34,
    0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
    0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C,
    0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64,
    0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
    0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C,
    0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
    0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0,
    0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC,
    0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
    0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4,
    0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0,
    0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC,
    0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8,
    0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4,
    0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

/*
    字符串比较
*/
static int __strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2++)
    {
        if (*s1++ == 0)
        {
            return (0);
        }
    }

    return (*(u_char *)s1 - *(u_char *)--s2);
}

/*
    字符串比较（忽略大小写）
*/
static int __strcmpi(const char *s1, const char *s2)
{
    const u_char *us1 = (const u_char *)s1;
    const u_char *us2 = (const u_char *)s2;

    while (kAsciiLowerCase[*us1] == kAsciiLowerCase[*us2++])
    {
        if (*us1++ == '\0')
        {
            return (0);
        }
    }

    return (kAsciiLowerCase[*us1] - kAsciiLowerCase[*--us2]);
}

/*
    字符串前n个字符比较
*/
static int __strncmp(const char *s1, const char *s2, size_t n)
{
    if (n == 0)
    {
        return (0);
    }    

    do
    {
        if (*s1 != *s2++)
        {
            return (*(u_char *)s1 - *(u_char *)--s2);
        }

        if (*s1++ == 0)
        {
            break;
        }
    } while (--n != 0);

    return (0);
}

/*
    字符串前n个字符比较（忽略大小写）
*/
static int __strncmpi(const char *s1, const char *s2, size_t n)
{
    if (n != 0) 
    {
        const u_char *us1 = (const u_char *)s1;
        const u_char *us2 = (const u_char *)s2;

        do 
        {
            if (kAsciiLowerCase[*us1] != kAsciiLowerCase[*us2++])
            {
                return (kAsciiLowerCase[*us1] - kAsciiLowerCase[*--us2]);
            }

            if (*us1++ == '\0')
            {
                break;
            }
        } while (--n != 0);
    }

    return (0);
}

/*
    str是否以find结尾
*/
static bool __strendof(const char* str, const char* find)
{
    int lenstr = (int)::strlen(str);
    int lensub = (int)::strlen(find);

    if (lenstr < lensub) 
    {
        return false;
    }

    return memcmp(str + lenstr - lensub, find, lensub) == 0;
}

/*
    str是否以find结尾（忽略大小写）
*/
static bool __strendofi(const char* str, const char* find)
{
    const u_char * ufind = (const u_char *)find;
    int lenstr = (int)::strlen(str);
    int lensub = (int)::strlen(find);

    if (lenstr < lensub) 
    {
        return false;
    }

    const u_char* pos = (const u_char*)(str + lenstr - lensub);

    for (int i = 0; i < lensub; i++)
    {
        if (kAsciiLowerCase[pos[i]] != kAsciiLowerCase[ufind[i]])
        {
            return false;
        }
    }

    return true;
}

/*
    str是否以find开始
*/
static bool __strbegof(const char* str, const char* find)
{
    int lenstr = (int)::strlen(str);
    int lensub = (int)::strlen(find);

    if (lenstr < lensub) 
    {
        return false;
    }

    return memcmp(str, find, lensub) == 0;
}

/*
    str是否以find开始（忽略大小写）
*/
static bool __strbegofi(const char* str, const char* find)
{
    const u_char * ustr = (const u_char *)str;
    const u_char * ufind = (const u_char *)find;
    int lenstr = (int)::strlen(str);
    int lensub = (int)::strlen(find);

    if (lenstr < lensub) 
    {
        return false;
    }

    for (int i = 0; i < lensub; i++) 
    {
        if (kAsciiLowerCase[ustr[i]] != kAsciiLowerCase[ufind[i]])
        {
            return false;
        }
    }

    return true;
}

/*
    find是否是str的子串。
    是，返回首次出现的地址；否0

    算法：暴力法，除了像（abcabcabc...）这种有很多重复的，这个暴力法的效率已经很高了，所以不要去优化
*/
static char *__strstr(const char *str, const char *find)
{
    char c, sc;
    size_t len;

    if ((c = *find++) != 0)
    {
        len = strlen(find);

        do
        {
            do
            {
                if ((sc = *str++) == 0)
                {
                    return (NULL);
                }
            } while (sc != c);

        } while (__strncmp(str, find, len) != 0);

        str--;
    }

    return ((char *)str);
}

/*
    find是否是str的子串。（忽略大小写）
    是，返回首次出现的地址；否0

    算法：暴力法，除了像（abcabcabc...）这种有很多重复的，这个暴力法的效率已经很高了，所以不要去优化
*/
static char *__strstri(const char *str, const char *find)
{
    u_char c, sc;
    size_t len;

    if ((c = *find++) != 0)
    {
        len = strlen(find);

        do
        {
            do
            {
                if ((sc = *str++) == 0)
                {
                    return (NULL);
                }

            } while (kAsciiLowerCase[sc] != kAsciiLowerCase[c]);

        } while (__strncmpi(str, find, len) != 0);

        str--;
    }

    return ((char *)str);
}

/*
    find和str是否匹配（相等）。
    '*' 代表一个或者多个任意字符；'?' 代表一个字符（UNICODE中文是两个字符）

    算法：暴力法
*/
static bool __wildcard(const char* str, const char* find)
{
    char const *back_find = nullptr, *back_str = back_str = nullptr;

    for (;;)
    {
        u_char c = *str++;
        u_char d = *find++;

        switch (d)
        {
            case '?':
            {
                if (c == '\0')
                {
                    return false;
                }

                break;
            }
            case '*':
            {
                if (*find == '\0')
                {
                    return true;
                }

                back_find = find;
                back_str = --str;
                break;
            }
            default:
            {
                if (c == d)
                {
                    if (d == '\0')
                    {
                        return true;
                    }

                    break;
                }

                if (c == '\0' || !back_find)
                {
                    /* No point continuing */
                    return false; 
                }

                /* Try again from last *, one character later in str. */
                find = back_find;
                str = ++back_str;
                break;
            }
        }
    }
}

/*
    find和str是否匹配（相等）。（忽略大小写）
    '*' 代表一个或者多个任意字符；'?' 代表一个字符（UNICODE中文是两个字符）

    算法：暴力法
*/
static bool __wildcardi(const char* str, const char* find)
{
    char const *back_find = nullptr, *back_str = back_str = nullptr;

    for (;;)
    {
        u_char c = *str++;
        u_char d = *find++;

        switch (d)
        {
            case '?':
            {
                if (c == '\0')
                {
                    return false;
                }

                break;
            }
            case '*':
            {
                if (*find == '\0')
                {
                    return true;
                }

                back_find = find;
                back_str = --str;
                break;
            }
            default:
            {
                if (kAsciiLowerCase[c] == kAsciiLowerCase[d])
                {
                    if (d == '\0')
                    {
                        return true;
                    }

                    break;
                }

                if (c == '\0' || !back_find)
                {
                    /* No point continuing */
                    return false;
                }

                /* Try again from last *, one character later in str. */
                find = back_find;
                str = ++back_str;
                break;
            }
        }
    }
}

namespace stringutils_c
{
    int strcmp(const char * s, const char * find, bool icase)
    {
        return icase ? __strcmpi(s, find) : __strcmp(s, find);
    }

    int strncmp(const char* s, const char* find, int n, bool icase)
    {
        return icase ? __strncmpi(s, find, n) : __strncmp(s, find, n);
    }

    bool strendof(const char* s, const char* find, bool icase)
    {
        return icase ? __strendofi(s, find) : __strendof(s, find);
    }

    bool strbegof(const char* s, const char* find, bool icase)
    {
        return icase ? __strbegofi(s, find) : __strbegof(s, find);
    }

    char * strstr(const char* s, const char* find, bool icase)
    {
        return icase ? __strstri(s, find) : __strstr(s, find);
    }

    bool strwildcard(const char* s, const char* find, bool icase)
    {
        return icase ? __wildcardi(s, find) : __wildcard(s, find);
    }
}