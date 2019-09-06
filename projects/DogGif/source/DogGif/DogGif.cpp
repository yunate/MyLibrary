#include "DogGif.h"
#include <memory.h>

namespace DogGifNSP
{

DogGif::DogGif()
{
}

DogGif::~DogGif()
{
}

bool DogGif::DogGif::Init(u8 * pBuff, u32 buffLen)
{
    if (pBuff == nullptr)
    {
        return false;
    }

    if (!ReadHead(&pBuff, buffLen))
    {
        return false;
    }

    if (!ReadLsd(&pBuff, buffLen))
    {
        return false;
    }

    if (!ReadGolColorTable(&pBuff, buffLen))
    {
        return false;
    }

    return true;
}

bool DogGif::ReadHead(u8** ppBuff, u32& buffLen)
{
    // 不要去判读pBuff null 了
    u8* pBuff = *ppBuff;
    GifHead head;
    u8 headSize = sizeof(GifHead);

    if (buffLen < (u32)(headSize))
    {
        return false;
    }

    ::memcpy(&head, pBuff, headSize);
    *ppBuff += headSize;
    buffLen -= headSize;

    if (!head.IsGifFile())
    {
        return false;
    }

    m_gifGolInfo.m_gifHeadSignaturl.append((const char*)&head, headSize);
    return true;
}

bool DogGif::ReadLsd(u8 ** ppBuff, u32 & buffLen)
{
    // 不要去判读pBuff null 了
    u8* pBuff = *ppBuff;
    GifLogicalScreenDescriptor lsd;
    u8 lsdSize = sizeof(GifLogicalScreenDescriptor);

    if (buffLen < (u32)(lsdSize))
    {
        return false;
    }

    ::memcpy(&lsd, pBuff, lsdSize);
    *ppBuff += lsdSize;
    buffLen -= lsdSize;
    m_gifGolInfo.m_width = lsd.m_width;
    m_gifGolInfo.m_height = lsd.m_height;
    m_gifGolInfo.m_hasGolColorTable = (lsd.m_colorDes >> 7) & 0x01;
    m_gifGolInfo.m_colorDepth = (lsd.m_colorDes >> 4) & 0x07;
    m_gifGolInfo.m_isGolColorTableSorted = (lsd.m_colorDes >> 3) & 0x01;
    m_gifGolInfo.m_golColorTableBit = 2 << ((lsd.m_colorDes & 0x07));
    m_gifGolInfo.m_bgColorIndex = lsd.m_bgColor;
    m_gifGolInfo.m_pixelToWidthHeight = lsd.m_pixelTo;
    return true;
}

bool DogGif::ReadGolColorTable(u8 ** ppBuff, u32 & buffLen)
{
    if (!m_gifGolInfo.m_hasGolColorTable)
    {
        return true;
    }

    u8 * pBuff = *ppBuff;
    m_gifGolInfo.m_golColorTable.resize(m_gifGolInfo.m_golColorTableBit);

    if (buffLen < m_gifGolInfo.m_golColorTableBit * 3)
    {
        return false;
    }

    for (size_t i = 0; i < m_gifGolInfo.m_golColorTable.size(); ++i)
    {
        m_gifGolInfo.m_golColorTable[i].m_r = pBuff[i * 3];
        m_gifGolInfo.m_golColorTable[i].m_g = pBuff[i * 3 + 1];
        m_gifGolInfo.m_golColorTable[i].m_b = pBuff[i * 3] + 2;
    }

    *ppBuff += m_gifGolInfo.m_golColorTableBit * 3;
    buffLen -= m_gifGolInfo.m_golColorTableBit * 3;
    return true;
}

DogGifFrame * DogGif::ReadFrameData(u8 ** ppBuff, u32 & buffLen)
{
    DogGifFrame * pFrame = new DogGifFrame();
    u8 * pBuff = *ppBuff;
    bool isOk = true;

    if (m_gifGolInfo.m_gifHeadSignaturl[4] == '9')
    {
        for (u32 i = 0; i < buffLen; ++i)
        {
            if (pBuff[0] == 0x21)
            {
                if (*ppBuff + buffLen <= pBuff)
                {
                    isOk = false;
                    break;
                }

                if (pBuff[1] == 0xf9)
                {
                    ExtendBlock extend;
                    u8 extendSize = (u8)sizeof(ExtendBlock);

                    if (buffLen < extendSize)
                    {
                        isOk = false;
                        break;
                    }

                    ::memcpy(&extend, pBuff, extendSize);
                    pBuff += extendSize;
                    pFrame->m_isNeedUserInput = extend.m_userFlag;
                    pFrame->m_delayTime = extend.m_delayTime;
                    pFrame->m_tranColorIndex = extend.m_TranColorIndex;
                }
            }

            if (pBuff[i] == 0x2c)
            {
                ImageDescriptor imgDes;
                u8 imgDesSize = (u8)sizeof(imgDes);

                if (buffLen < imgDesSize)
                {
                    isOk = false;
                    break;
                }

                ::memcpy(&imgDes, pBuff, imgDesSize);
                pBuff += imgDesSize;
                pFrame->m_xFix = imgDes.m_xFix;
                pFrame->m_yFix = imgDes.m_yFix;
                pFrame->m_width = imgDes.m_width;
                pFrame->m_height = imgDes.m_height;
                pFrame->m_hasLocalColorTable = imgDes.m_localColorFlag >> 7;
                pFrame->m_interlaceFlag = imgDes.m_localColorFlag >> 6;
                pFrame->m_sortFlag = imgDes.m_localColorFlag >> 5;
                pFrame->m_LocalColorTableBit = 2 << (imgDes.m_localColorFlag & 0x07 + 1);

                if (pFrame->m_hasLocalColorTable)
                {
                    pFrame->m_localColorTable.resize(pFrame->m_LocalColorTableBit);

                    for (size_t j = 0; j < pFrame->m_localColorTable.size(); ++j)
                    {
                        m_gifGolInfo.m_golColorTable[j].m_r = pBuff[j * 3];
                        m_gifGolInfo.m_golColorTable[j].m_g = pBuff[j * 3 + 1];
                        m_gifGolInfo.m_golColorTable[j].m_b = pBuff[j * 3] + 2;
                    }

                    pBuff += m_gifGolInfo.m_golColorTableBit * 3;
                }

                if (*ppBuff + buffLen <= pBuff)
                {
                    isOk = false;
                    break;
                }

                u8* pTmp = pBuff;
                u32 allSize = 1;
                u8 blockSize = pBuff[0];
                ++pBuff;

                while (blockSize != 0)
                {
                    allSize += blockSize;
                    pBuff += blockSize;

                    if (*ppBuff + buffLen <= pBuff)
                    {
                        isOk = false;
                        break;
                    }
                }

                break;
            }

            ++pBuff;
        }
    }
    
    if (!isOk)
    {
        delete pFrame;
        pFrame = nullptr;
    }

    return pFrame;
}

}