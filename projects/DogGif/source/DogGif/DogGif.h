
#ifndef __DOGGIF_H_
#define __DOGGIF_H_

#include "DogGifDef.h"
#include <string>
#include <vector>

namespace DogGifNSP
{

struct DogGifColor
{
    DogGifColor(u8 r, u8 g, u8 b):
        m_r(r),
        m_g(g),
        m_b(b)
    {

    }

    DogGifColor()
    {

    }

    /** red
    */
    u8 m_r = 0;

    /** green
    */
    u8 m_g = 0;

    /** blue
    */
    u8 m_b = 0;
};

struct DogGifFrame
{
    /** 用户输入标记
    */
    u8 m_isNeedUserInput = 0;

    /** 播放时延
    */
    u16 m_delayTime = 0;

    /** 透明色索引
        置位表示使用透明颜色
    */
    u8 m_tranColorIndex = 0;

    /** x方向偏移量
    */
    u16 m_xFix = 0;

    /** y方向偏移量
    */
    u16 m_yFix = 0;

    /** 图像宽度
    */
    u16 m_width = 0;

    /** 图像高度
    */
    u16 m_height = 0;

    /** 是否有局部颜色表
    */
    u8 m_hasLocalColorTable = 0;

    /** 交织标志(Interlace Flag)，置位时图象数据使用交织方式排列，否则使用顺序排列。
    */
    u8 m_interlaceFlag = 0;

    /** 分类标志(Sort Flag)，如果置位表示紧跟着的局部颜色列表分类排列.
    */
    u8 m_sortFlag = 0;

    /** 局部颜色列表颜色个数
    */
    u16 m_LocalColorTableBit = 0;

    /** 局部色表
    */
    std::vector<DogGifColor> m_localColorTable;

    /** frame数据
    */
    std::vector<u8> m_frameData;
};

struct DogGifGolInfo
{
    /** gif标识 
        GIF89a 或者 GIF87a
    */
    std::string m_gifHeadSignaturl = "";

    /** 宽度
    */
    u16 m_width = 0;

    /** 高度度
    */
    u16 m_height = 0;

    /** 是否有全局颜色表
    */
    u8 m_hasGolColorTable = 0;

    /** 颜色深度
    */
    u8 m_colorDepth = 0;

    /** 全局颜色列表是否分类排列
    */
    u8 m_isGolColorTableSorted = 0;

    /** 全局颜色列表颜色个数
    */
    u16 m_golColorTableBit = 0;

    /** 背景色位置
    */
    u8 m_bgColorIndex;

    /** 象素的高宽比
        如果该字段的值为非0，则象素的高宽比由下面的公式计算：
        高宽比 = (象素高宽比 + 15) / 64
        该字段的取值范围从最宽的比值4：1到最高的比值1：4，递增的步幅为1/64。取值： 0 - 没有比值，1～255 - 用于计算的值。
    */
    u8 m_pixelToWidthHeight = 0;

    /** 全局色表
    */
    std::vector<DogGifColor> m_golColorTable;

    /** 每一帧数据
    */
    std::vector<DogGifFrame*> m_frameData;

    ~DogGifGolInfo()
    {
        for (auto it : m_frameData)
        {
            delete it;
        }

        m_golColorTable.clear();
    }
};

class DogGif
{
public:
    /** 构造函数
    */
    DogGif();

    /** 析构函数
    */
    ~DogGif();

public:
    bool Init(u8 * pBuff, u32 buffLen);

private:
    /** 读gif头
    @pram [in, out] ppBuff head的开始指针，读取过后自动向后移动响应位置
    @pram [in, out] buffLen ppBuff长度，读取过后自动减少读取的个数
    @return 是否成功
    */
    bool ReadHead(u8 ** ppBuff, u32& buffLen);

    /** 读LSD
    @pram [in, out] ppBuff head的开始指针，读取过后自动向后移动响应位置
    @pram [in, out] buffLen ppBuff长度，读取过后自动减少读取的个数
    @return 是否成功
    */
    bool ReadLsd(u8 ** ppBuff, u32& buffLen);

    /** 读全局色表
    @pram [in, out] ppBuff head的开始指针，读取过后自动向后移动响应位置
    @pram [in, out] buffLen ppBuff长度，读取过后自动减少读取的个数
    @return 是否成功
    */
    bool ReadGolColorTable(u8** ppBuff, u32& buffLen);

    /** 读一帧
    @pram [in, out] ppBuff head的开始指针，读取过后自动向后移动响应位置
    @pram [in, out] buffLen ppBuff长度，读取过后自动减少读取的个数
    @return 成功返回DogGifFrame对象，否则NULL
    */
    DogGifFrame* ReadFrameData(u8** ppBuff, u32& buffLen);

private:
    DogGifGolInfo m_gifGolInfo;
};


}
#endif // __DOGGIF_H_

