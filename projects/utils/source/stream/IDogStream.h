
#ifndef __IDOGSTREAM_H_
#define __IDOGSTREAM_H_

#include <stdio.h>

/** 无符号8位
*/
using u8 = unsigned char;

/** 无符号16位
*/
using u16 = unsigned short;

/** 无符号32位
*/
using u32 = unsigned long;

/** 无符号64位
*/
using u64 = unsigned long long;

/** 有符号8位
*/
using s8 = char;

/** 有符号16位
*/
using s16 = short;

/** 有符号32位
*/
using s32 = long;

/** 有符号64位
*/
using s64 = long long;

/** 获得 (n * b) 有 a <= (n * b) <= a + b
@param [in] a 不能超过0xffffffff - (b - 1)否则返回小于a
@param [in] b
@return b倍数大于等于a的最小上界，如果小于a，说明失败
*/
inline u32 GetMinUpper(u64 a, u64 b)
{
    --b;
    return (u32)((a + b) & (~b));
}

/** 数据块大小单位 1 K
*/
#define MET_DATA_SIZE 0x400

/** 32位有符号数最大值
*/
#define  MAX_S32 0x7fffffff

/** 32位无符号数最大值
*/
#define  MAX_U32 0xffffffff

/** 流的基类
*/
class  IDogStream
{
public:
    /** 析构函数
    */
    virtual ~IDogStream() { };

    /** 获得当前位置 seek
    @return 当前位置 
    */
    virtual s64 Pos() = 0;

    /** 设置当前位置
    @param [int] offset 偏移
    @param [int] origin 取如下值SEEK_CUR SEEK_END SEEK_SET
    @return 实际设置的位置
    */
    virtual s64 Seek(s64 offset, int origin) = 0;

    /** 获得流的大小
    @return 流的大小
    */
    virtual s64 Size()
    {
        s64 curPos = Pos();
        s64 end = Seek(0, SEEK_END);
        Seek(curPos, SEEK_SET);
        return end;
    }

    /** 设置流的大小
    @param [in] newSize 流的大小
    @return 实际分配的大小
    */
    virtual s64 ReSize(s64 newSize) = 0;

    /** 从pos开始读取流,由于取到内存中因此不能超过2^31位 (会改变pos)
    @param [out] buff 输出buff，内存需要自己管理
    @param [in] count 读取的大小
    @return 读取的实际大小
    */
    virtual s32 Read(u8* const buff, s32 count) = 0;

    /** 从pos开始写入流，一次性写入不能超过32位(会改变pos)
    @param [in] buff 写入buff，内存需要自己管理
    @param [in] count 写入的大小
    @return 写入的实际大小
    */
    virtual s32 Write(const u8* const buff, s32 count) = 0;

    /** 读取流 (会改变pos)
    @param [out] buff 输出buff，内存需要自己管理
    @param [in] count 读取的大小
    @param [int] start 开始位置(偏移)
    @return 读取的实际大小
    */
    virtual s32 ReadW(u16* const buff, s32 count, s64 start = 0)
    {
        return Read((u8*)buff, count * 2) / 2;
    }

    /** 写入流 (会改变pos)
    @param [in] buff 写入buff，内存需要自己管理
    @param [in] count 写入的大小
    @param [int] start 开始位置(偏移)
    @return 写入的实际大小
    */
    virtual s32 WriteW(const u16* const buff, s32 count, s64 start = 0)
    {
        return Write((const u8*)buff, count * 2) / 2;
    }

    /** 读取全部，由于取到内存中因此不能超过2^31位，如果实际大小超过2^31位，那么此函数只读取前2^31位 (会改变pos)
    @param [out] buff 输出buff，内存需要自己管理
    @return 读取的实际大小
    */
    virtual s32 ReadAllA(u8* const buff)
    {
        Seek(0, SEEK_SET);
        return Read(buff, (s32)Size());
    }

    /** 读取全部 (会改变pos)
    @param [out] buff 输出buff，内存需要自己管理
    @return 读取的实际大小
    */
    virtual s32 ReadAllW(u16* const buff)
    {
        return ReadAllA((u8*)buff) / 2;
    }
};


#endif //__IDOGSTREAM_H_
