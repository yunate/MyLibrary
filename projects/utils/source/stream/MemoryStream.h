
#ifndef __MEMORYSTREAM_H_
#define __MEMORYSTREAM_H_

#include "IDogStream.h"

/** 内存流，最大内存：min(4G, 系统定义)
*/
class MemoryStream :
    public IDogStream
{
public:
    /** 构造函数
    */
    MemoryStream();

    /** 构造函数
    @param [in] size 大小
    */
    MemoryStream(u32 size);

    /** 构造函数
    @param [in] pBuff 内存
    @param [in] size 大小
    */
    MemoryStream(s8* pBuff, u32 size);

    /** 构造函数
    @param [in] stream 流
    */
    MemoryStream(MemoryStream&& stream);

    /** 构造函数
    @param [in] stream 流
    */
    MemoryStream(const IDogStream& stream);

    /** 复制运算符
    @param [in] stream 流
    */
    MemoryStream& operator=(const IDogStream& stream);

    /** 析构函数
    */
    virtual ~MemoryStream();

    /** 获得当前位置 seek
    @return 当前位置
    */
    virtual s64 Pos();

    /** 设置当前位置
    @param [int] offset 相对于 start的偏移
    @param [int] start 开始位置
    @return 实际设置的位置
    */
    virtual s64 Seek(s64 offset, s64 start);

    /** 获得流的大小
    @return 流的大小
    */
    virtual s64 Size();

    /** 设置流的大小，内存不够时候会自动分配，但是不会初始化内存
    @param [in] newSize 流的大小
    @return 实际分配的大小
    */
    virtual s64 ReSize(s64 newSize);

    /** 获得实际buff大小，区别于GetSize
    @return 所使用的内存
    */
    u32 Capacity();

    /** 清空数据
    */
    void Clear();

    /** 从pos开始读取流 (会改变pos)
    @param [out] buff 输出buff，内存需要自己管理
    @param [in] count 读取的大小
    @return 读取的实际大小
    */
    virtual s32 Read(u8* const buff, s32 count);

    /** 从pos开始写入流 (会改变pos)
    @param [in] buff 写入buff，内存需要自己管理
    @param [in] count 写入的大小
    @return 写入的实际大小
    */
    virtual s32 Write(const u8* const buff, s32 count);

protected:
    /** 重新分配内存(虽然newSize是64位的，但是这个函数分配内存不会超过32位也就是4G)
    @param [in] newSize 新的大小
    @return 实际分配的大小
    */
    u32 ReallocMemory(u32 newSize);

    /** 重新计算即将分配的内存大小
    @param [in] newSize 用户输入
    @return 计算后的大小
    */
    u32 CalNewSize(u32 newSize);

protected:
    /** 当前位置
    */
    u32 m_pos;

    /** 实际使用的大小
    */
    u32 m_size;

    /** 总大小
    */
    u32 m_capacity;

    /** 缓存
    */
    s8* m_pBuff;
};

#endif //__MEMORYSTREAM_H_
