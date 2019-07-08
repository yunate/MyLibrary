#ifndef __STRING_UTILS_C_H_
#define __STRING_UTILS_C_H_

/** char* 字符串操作
所有输入字符串需要外部保证不为空且有效
*/
namespace stringutils_c
{
    /** 字符串前n个比较
    @param [in] src 源
    @param [in] find 比较
    @param [in] n 个数
    @param [in] icase 是否忽略大小写
    @return 0 相等 > 0 src 大 < 0 find 大
    */
    int    strncmp(const char* src, const char* find, int n, bool icase);

    /** 字符串比较
    @param [in] src 源
    @param [in] find 比较
    @param [in] icase 是否忽略大小写
    @return 0 相等 > 0 src 大 < 0 find 大
    */
    int    strcmp(const char* src, const char* find, bool icase);

    /** 以...结尾
    @param [in] src 源
    @param [in] find 
    @param [in] icase 是否忽略大小写
    @return src是否以find结尾
    */
    bool   strendof(const char* src, const char* find, bool icase);

    /** 以...开始
    @param [in] src 源
    @param [in] find
    @param [in] icase 是否忽略大小写
    @return src是否以find开始
    */
    bool   strbegof(const char* src, const char* find, bool icase);

    /** 字符串查找
    @param [in] src 源
    @param [in] find
    @param [in] icase 是否忽略大小写
    @return src 找到 find ? 是，返回首次出现的地址；否0
    */
    char * strstr(const char* src, const char* find, bool icase);

    /** 字符串查找 '*' 代表一个或者多个任意字符；'?' 代表一个字符（UNICODE中文是两个字符）
    @param [in] src 源
    @param [in] find
    @param [in] icase 是否忽略大小写
    @return src 找到 find ? 是，返回首次出现的地址；否0
    */
    bool   strwildcard(const char* src, const char* find, bool icase);
}

#endif // __STRING_UTILS_C_H_
