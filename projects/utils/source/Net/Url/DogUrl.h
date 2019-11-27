
#ifndef __DOGURL_H_
#define __DOGURL_H_

#include "typedef/DogString.h"

#include <regex>

/** url
一般以utf-8编码
scheme://[user[:password]@]host[:port] [/path] [?query] [#fragment]
*/
struct DogUrl
{
    /** 指定低层使用的协议(例如：http, https, ftp)
    */
    DogStringA m_scheme;

    /** 用户名称
    @note: [可省略]
    */
    DogStringA m_user;

    /** 密码
    @note: [可省略]
    */
    DogStringA m_password;

    /** 服务器。通常为域名，有时为IP地址
    */
    DogStringA m_host;

    /** 端口。以数字方式表示,默认值“:80”
    @note: [可省略]
    */
    unsigned int m_port = 0;

    /** 路径。以“/”字符区别路径中的每一个目录名称
    @note: [可省略]
    */
    DogStringA m_path;

    /** 查询。GET模式的窗体参数，以“?”字符为起点，每个参数以“&”隔开，再以“=”分开参数名称与数据，通常以UTF8的URL编码，避开字符冲突的问题
    @note: [可省略]
    */
    DogStringA m_query;

    /** 片段。以“#”字符为起点
    @note: [可省略]
    */
    DogStringA m_fragment;

    /** url 是否有效
    @return 是否有效
    */
    bool IsValid()
    {
        return !m_scheme.empty() && m_port != 0 && !m_host.empty();
    }

    /** 获得格式化后的URL
    @note scheme:[//[user[:password]@]host[:port]] [/path] [?query] [#fragment]
    @return 格式化后的URL
    */
    DogStringA GetFormatedUrl()
    {
        DogStringA formatedUrl = "";

        if (!IsValid())
        {
            return formatedUrl;
        }

        formatedUrl += m_scheme;
        formatedUrl += "://";

        if (m_user.length() != 0 || m_password.length() != 0)
        {
            formatedUrl += m_user;
            formatedUrl += ":";
            formatedUrl += m_password;
            formatedUrl += "@";
        }

        formatedUrl += m_host;

        if (!( (m_port == 80) &&
               (m_scheme.length() >= 4) &&
               (m_scheme[0] == 'h' || m_scheme[0] == 'H') &&
               (m_scheme[1] == 't' || m_scheme[1] == 'T') &&
               (m_scheme[2] == 't' || m_scheme[2] == 'T') &&
               (m_scheme[3] == 'p' || m_scheme[3] == 'P') ))
        {
            formatedUrl += ":";
            char portBuff[10] = {0};
            ::_itoa_s(m_port, portBuff, 10);
            formatedUrl += portBuff;
        }

        if (m_path.length() > 0)
        {
            formatedUrl += "/";
            formatedUrl += m_path;
        }

        if (m_query.length() > 0)
        {
            formatedUrl += "?";
            formatedUrl += m_query;
        }

        if (m_fragment.length() > 0)
        {
            formatedUrl += "#";
            formatedUrl += m_fragment;
        }

        return formatedUrl;
    }
};

/** 解析url
@note: 是否成功用dogUrl 的 IsValid 判断
@param [in] url url原始字符串（一般以UTF-8编码）
@param [out] dogUrl 输出
*/
inline void ParseUrl(const DogStringA& url, DogUrl& dogUrl)
{
    size_t index = 0;
    size_t len = url.length();

    // 找scheme
    for (size_t i = index; i < len; ++i)
    {
        if (url[i] == ':')
        {
            dogUrl.m_scheme = url.substr(index, i - index);
            index = i + 1;
            break;
        }
    }

    if (dogUrl.m_scheme.empty())
    {
        return;
    }

    // 固定 // 或者 \\ 
    if (index + 1 >= len ||
        (url[index] != '/' && url[index] != '\\') ||
        (url[index + 1] != '/' && url[index + 1] != '\\'))
    {
        return;
    }

    index += 2;

    // [user[:password]@]host[:port] 【[/path] [?query] [#fragment]】
    // 找到扩展符号 “/ \ ? #”
    size_t hostPortEndIndex = len - 1;
    for (size_t i = index; i < len; ++i)
    {
        if (url[i] == '/' || url[i] == '\\' || url[i] == '?' || url[i] == '#')
        {
            hostPortEndIndex = i - 1;
            break;
        }
    }

    // 长度为0
    if (hostPortEndIndex < index)
    {
        return;
    }

    // 找到@符号，说明有用户名密码
    {
        size_t userPswEndIndex = index - 1;
        for (size_t i = index; i <= hostPortEndIndex; ++i)
        {
            if (url[i] == '@')
            {
                userPswEndIndex = i - 1;

                // 长度不为0
                if (userPswEndIndex >= index)
                {
                    // 寻找 “:”
                    size_t userEndIndex = userPswEndIndex;
                    for (size_t j = index; j <= userPswEndIndex; ++j)
                    {
                        if (url[j] == ':')
                        {
                            userEndIndex = j - 1;
                            break;
                        }
                    }

                    dogUrl.m_user = url.substr(index, userEndIndex - index + 1);

                    if (userEndIndex < userPswEndIndex - 2)
                    {
                        dogUrl.m_password = url.substr(userEndIndex + 2, userPswEndIndex - userEndIndex - 1);
                    }
                }

                index = userPswEndIndex + 2;
                break;
            }
        }
    }

    // host 端口
    {
        if (index <= hostPortEndIndex)
        {
            // 寻找 “:”
            size_t hostEndIndex = hostPortEndIndex;
            for (size_t j = index; j <= hostPortEndIndex; ++j)
            {
                if (url[j] == ':')
                {
                    hostEndIndex = j - 1;
                    break;
                }
            }

            // 长度为0
            if (hostEndIndex < index)
            {
                return;
            }

            dogUrl.m_host = url.substr(index, hostEndIndex - index + 1);

            if (hostEndIndex < hostPortEndIndex - 2)
            {
                dogUrl.m_port = ::atoi(url.substr(hostEndIndex + 2, hostPortEndIndex - hostEndIndex - 1).c_str());
            }

            if (dogUrl.m_port == 0)
            {
                dogUrl.m_port = 80;
            }

            index = hostPortEndIndex + 2;
        }
        else
        {
            return;
        }
    }

    while (index < len)
    {
        // 寻找下一个扩展符号
        size_t extendEndIndex = len - 1;
        for (size_t i = index; i < len; ++i)
        {
            if (url[i] == '?' || url[i] == '#')
            {
                extendEndIndex = i - 1;
                break;
            }
        }

        // 如果上一个符号是 "/" 或者 "\\" 那么填充m_path
        if (url[index - 1] == '/' || url[index - 1] == '\\')
        {
            dogUrl.m_path = url.substr(index, extendEndIndex - index + 1);
        }

        // 如果上一个符号是 "?" 那么填充m_query
        else if (url[index - 1] == '?')
        {
            dogUrl.m_query = url.substr(index, extendEndIndex - index + 1);
        }

        // 如果上一个符号是 "#" 那么填充m_fragment
        else if (url[index - 1] == '#')
        {
            dogUrl.m_fragment = url.substr(index, extendEndIndex - index + 1);
        }

        index = extendEndIndex + 2;
    }
}

/** 正则表达式解析url
@note: 是否成功用dogUrl 的 IsValid 判断
@param [in] url url原始字符串（一般以UTF-8编码）
@param [out] dogUrl 输出
*/
inline void ParseUrlRegex(const DogStringA& url, DogUrl& dogUrl)
{
    // note: 正则表达式中 方括号中"\"和"]"需要转义，其他的不需要
    DogStringA parttenStr;

    // scheme://
    parttenStr += R"__(([a-zA-Z]+):[\\/]{2})__";

    // [user[:password]@]
    parttenStr += R"__((?:([^:@]*)(?::([^@]*))?@)?)__";

    // host[:port]
    parttenStr += R"__(([^/\\#?:]*)(?::([0-9]{0,5}))?)__";

    // [/path]
    parttenStr += R"__((?:[/\\]([^?#]*))?)__";

    // [?query]
    parttenStr += R"__((?:[?]([^?#/\\]*))?)__";

    //  [#fragment]
    parttenStr += R"__((?:[#]([^?#/\\]*))?)__";

    std::regex partten(parttenStr);
    std::smatch results;

    if (!std::regex_search(url, results, partten) || results.size() != 9)
    {
        return;
    }

    DogStringA ss = results.str();
    dogUrl.m_scheme = results[1];
    dogUrl.m_user = results[2];
    dogUrl.m_password = results[3];
    dogUrl.m_host = results[4];
    dogUrl.m_port = ::atoi(results[5].str().c_str());
    dogUrl.m_path = results[6];
    dogUrl.m_query = results[7];
    dogUrl.m_fragment = results[8];

    if (dogUrl.m_port == 0)
    {
        dogUrl.m_port = 80;
    }
}

#endif //__DOGURL_H_
