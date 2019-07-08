#pragma once

#include <string>
#include <vector>

class KMPStrCmp
{
public:
    KMPStrCmp(const std::string & sPat, bool bIgnoreCase = true);

    virtual~KMPStrCmp();

    int Cmp(const char * src);

private:
    void FormateNext();

private:
    std::string  m_sPat;            // 待匹配的
    std::string  m_sPatLower;        // 待匹配的,全小写
    bool         m_bIgnoreCase;        // 忽略大小写
    char *         m_nNext;            // 很明显，匹配符长度不能超过127个
};

class KMPWildCardsStrCmp
{
public:
    KMPWildCardsStrCmp(const std::string & sPat, bool bIgnoreCase = true);

    virtual~KMPWildCardsStrCmp();

    int Cmp(const char * src);

private:
    void FormateNext();
    int GetCmpIndex(const char * sSrc, int nIndex);

private:
    std::vector<std::string>  m_sPats;            // 待匹配的 数组
    std::vector<std::string>  m_sPatLowers;        // 待匹配的,全小写 数组
    bool                      m_bIgnoreCase;    // 忽略大小写
    std::vector<char * >      m_nNexts;            // 很明显，匹配符长度不能超过127个
};


inline void Test1()
{
    KMPStrCmp strCmp("");
    strCmp.Cmp("");
}

inline void Test2()
{
    KMPStrCmp strCmp("abc");
    int b = strCmp.Cmp("cd ef bc abc dd d");
    b = strCmp.Cmp("");
    b = strCmp.Cmp("cd ef bc abc");
    b = strCmp.Cmp("abc dd d");
    b = strCmp.Cmp("ab dd d");
}

inline void Test3()
{
    KMPWildCardsStrCmp strCmp("abc");
    int b = strCmp.Cmp("cd ef bc abc dd d");
    b = strCmp.Cmp("");
    b = strCmp.Cmp("cd ef bc abc");
    b = strCmp.Cmp("abc dd d");
    b = strCmp.Cmp("ab dd d");
}

inline void Test4()
{
    KMPWildCardsStrCmp strCmp("f*?f");
    int b = strCmp.Cmp("amd64_msdri.inf.resources_31bf3856ad364e35_10.0.16299.15_en-us_4e3393c416861798");
    b = strCmp.Cmp("");
    b = strCmp.Cmp("cd ef bc abc");
    b = strCmp.Cmp("yeae");
}

inline void Test5()
{
    KMPWildCardsStrCmp strCmp("");
    int b = strCmp.Cmp("Oh yar.Totay is weekend!");
    b = strCmp.Cmp("");
    b = strCmp.Cmp("cd ef bc abc");
    b = strCmp.Cmp("yeae");
}