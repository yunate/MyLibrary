#include "KMPStrCmp.h"

void MakeLower(char * sSrc)
{
    for (size_t i = 0; i < strlen(sSrc); ++i)
    {
        sSrc[i] = tolower(sSrc[i]);
    }
}

void Split(std::string sSrc, char cSpliter, std::vector<std::string> & sOut)
{
    int nBegin = 0;
    int i = 0;

    for (; i < (int)sSrc.length(); ++i)
    {
        if (cSpliter == sSrc[i])
        {
            if (nBegin < i)
            {
                sOut.push_back(sSrc.substr(nBegin, i - nBegin));
            }

            nBegin = i + 1;
        }
    }

    if (nBegin < i)
    {
        sOut.push_back(sSrc.substr(nBegin, i - nBegin));
    }
}

void Split(std::string sSrc, std::string sSpliter, std::vector<std::string> & sOut)
{
    int nIndex = 0;

    while (nIndex < (int)sSrc.length())
    {
        int nTmp = (int)sSrc.find(sSpliter, nIndex);

        if (std::string::npos == nTmp)
        {
            break;
        }

        if (nIndex < nTmp)
        {
            sOut.push_back(sSrc.substr(nIndex, nTmp - nIndex));
            nIndex = nTmp + (int)sSpliter.length();
        }
    }

    if (nIndex < (int)sSrc.length())
    {
        sOut.push_back(sSrc.substr(nIndex));
    }
}

/////////////////////////////KMPStrCmp/////////////////////////////////////////////
KMPStrCmp::KMPStrCmp(const std::string & sPat, bool bIgnoreCase /* =true */)
    : m_sPat(sPat)
    , m_bIgnoreCase(bIgnoreCase)
    , m_nNext(0)
{
    if (m_bIgnoreCase)
    {
        char * sTmp = new char[m_sPat.length() + 1];
        sTmp[m_sPat.length()] = 0;
        memcpy(sTmp, m_sPat.c_str(), m_sPat.length());
        MakeLower(sTmp);
        m_sPatLower = sTmp;
        delete[]sTmp;
    }
    else
    {
        m_sPatLower = "";
    }

    FormateNext();
}

KMPStrCmp::~KMPStrCmp()
{
    if (m_nNext)
    {
        delete[] m_nNext;
        m_nNext = 0;
    }
}

int KMPStrCmp::Cmp(const char * src)
{
    char * sTmp = 0;
    const char * t = 0;
    const char * p = 0;
    int nSrcLen = (int)strlen(src);
    int nCmpLen = (int)m_sPat.length();

    if (nCmpLen > nSrcLen)
    {
        return -1;
    }

    if (m_bIgnoreCase)
    {
        sTmp = new char[nSrcLen + 1];
        sTmp[nSrcLen] = 0;

        // 这里不要用MakeLower
        for (int i = 0; i < nSrcLen; ++i)
        {
            sTmp[i] = tolower(src[i]);
        }

        t = sTmp;
        p = m_sPatLower.c_str();
    }
    else
    {
        p = m_sPat.c_str();
        t = src;
    }

    int i = 0; // 主串的位置
    int j = 0; // 模式串的位置

    while (i < nSrcLen && j < nCmpLen)
    {
        if (j == -1 || t[i] == p[j])
        {
            // 当j为-1时，要移动的是i，当然j也要归0
            i++;
            j++;
        }
        else
        {
            // i不需要回溯了
            // i = i - j + 1;
            j = m_nNext[j]; // j回到指定位置
        }
    }

    int nIndex = -1;

    if (j == nCmpLen)
    {
        nIndex = i - j;
    }

    if (sTmp)
    {
        delete[]sTmp;
    }

    return nIndex;
}

void KMPStrCmp::FormateNext()
{
    int nLenth = (int)m_sPat.length();
    m_nNext = new char[nLenth];
    memset(m_nNext, -1, nLenth);
    const char * p = 0;

    if (m_bIgnoreCase)
    {
        p = m_sPatLower.c_str();
    }
    else
    {
        p = m_sPat.c_str();
    }

    int j = 0;
    int k = -1;

    while (j < nLenth - 1)
    {
        if (k == -1 || p[j] == p[k])
        {
            if (p[++j] == p[++k])
            {
                // 当两个字符相等时要跳过
                m_nNext[j] = m_nNext[k];
            }
            else
            {
                m_nNext[j] = k;
            }
        }
        else
        {
            k = m_nNext[k];
        }
    }
}

/////////////////////////////KMPWildCardsStrCmp/////////////////////////////////////////////
KMPWildCardsStrCmp::KMPWildCardsStrCmp(const std::string & sPat, bool bIgnoreCase /* =true */)
    : m_bIgnoreCase(bIgnoreCase)
{
    Split(sPat, '*', m_sPats);

    if (m_bIgnoreCase)
    {
        for (auto it : m_sPats)
        {
            char * sTmp = new char[it.length() + 1];
            sTmp[it.length()] = 0;
            memcpy(sTmp, it.c_str(), it.length());
            MakeLower(sTmp);
            m_sPatLowers.push_back(sTmp);
            delete[]sTmp;
        }
    }


    FormateNext();
}

KMPWildCardsStrCmp::~KMPWildCardsStrCmp()
{
    for (auto it : m_nNexts)
    {
        delete[] it;
    }

    m_nNexts.clear();
}

int KMPWildCardsStrCmp::Cmp(const char * src)
{
    if (m_sPats.size() == 0)
    {
        return -1;
    }

    int nLastIndex = GetCmpIndex(src, 0);

    if (-1 == nLastIndex)
    {
        return -1;
    }

    while (1)
    {
        int nPat0Len = (int)m_sPats[0].length();
        int nIndex = nLastIndex + nPat0Len;
        bool bFinde = true;

        int nPatSize = (int)m_sPats.size();

        for (int i = 1; i < nPatSize; ++i)
        {
            nIndex = GetCmpIndex(src + nIndex, i);

            if (-1 == nIndex)
            {
                bFinde = false;
                break;
            }

            nIndex += (int)m_sPats[i].length();
        }

        if (bFinde)
        {
            return nLastIndex;
        }

        int nTmp = GetCmpIndex(src + nLastIndex + nPat0Len, 0);

        if (-1 == nTmp)
        {
            return -1;
        }

        nLastIndex += (nTmp + nPat0Len);
    }

    return -1;
}

void KMPWildCardsStrCmp::FormateNext()
{
    for (int i = 0; i < (int)m_sPats.size(); ++i)
    {
        int nLenth = (int)m_sPats[i].length();
        m_nNexts.push_back(new char[nLenth + 1]);
        m_nNexts[i][nLenth] = 0;
        memset(m_nNexts[i], -1, nLenth);
        const char * p = 0;

        if (m_bIgnoreCase)
        {
            p = m_sPatLowers[i].c_str();
        }
        else
        {
            p = m_sPats[i].c_str();
        }

        int j = 0;
        int k = -1;

        while (j < nLenth - 1)
        {
            if (k == -1 || p[j] == p[k] || '?' == p[j] || '?' == p[k])
            {
                ++j;
                ++k;

                if (p[j] == p[k])
                {
                    // 当两个字符相等时要跳过 //注意？不能跳过，因为？可能代表其他的字符，并不想等
                    m_nNexts[i][j] = m_nNexts[i][k];
                }
                else
                {
                    m_nNexts[i][j] = k;
                }
            }
            else
            {
                k = m_nNexts[i][k];
            }
        }
    }
}

int KMPWildCardsStrCmp::GetCmpIndex(const char * sSrc, int nIndex)
{
    if (strlen(sSrc) == 0)
    {
        return -1;
    }

    char * sTmp = 0;
    const char * t = 0;
    const char * p = 0;

    int nSrcLen = (int)strlen(sSrc);
    int nCmpLen = (int)m_sPats[nIndex].length();

    if (nCmpLen > nSrcLen)
    {
        if (sTmp)
        {
            delete[]sTmp;
        }

        return -1;
    }

    if (m_bIgnoreCase)
    {
        sTmp = new char[nSrcLen + 1];
        sTmp[nSrcLen] = 0;

        // 这里不要用MakeLower
        for (int i = 0; i < nSrcLen; ++i)
        {
            sTmp[i] = tolower(sSrc[i]);
        }

        t = sTmp;
        p = m_sPatLowers[nIndex].c_str();
    }
    else
    {
        p = m_sPats[nIndex].c_str();
        t = sSrc;
    }

    int i = 0; // 主串的位置
    int j = 0; // 模式串的位置

    while (i < nSrcLen && j < nCmpLen)
    {
        if (j == -1 || t[i] == p[j] || '?' == p[j])
        {
            // 当j为-1时，要移动的是i，当然j也要归0
            i++;
            j++;
        }
        else
        {
            // i不需要回溯了
            // i = i - j + 1;
            j = m_nNexts[nIndex][j]; // j回到指定位置
        }
    }

    int nRes = -1;

    if (j == nCmpLen)
    {
        nRes = i - j;
    }

    if (sTmp)
    {
        delete[]sTmp;
    }

    return nRes;
}

