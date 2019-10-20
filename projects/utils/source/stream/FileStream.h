
#ifndef __FILE_STREAM_H_
#define __FILE_STREAM_H_

#include "IDogStream.h"
#include <stdio.h>

class FileStream :
    public IDogStream
{
public:
    /** 构造函数
    @param [in] path 路径
    @param [in] mode 打开方式,mode == NULL 时候，默认为"a+b"
    */
    FileStream(const char* const path, const char* const mode = NULL);

    /** 移动构造构造函数
    @param [in] stream 流
    */
    FileStream(FileStream&& stream) noexcept;

    /** 析构函数
    */
    virtual ~FileStream();

    /** 不允许复制
    */
    FileStream(const FileStream& stream) = delete;

    /** 不允许复制
    */
    FileStream& operator=(const FileStream& stream) = delete;

public:
    /** 获得当前位置 seek
    @return 当前位置,-1表示失败，参见ftell
    */
    virtual s64 Pos();

    /** 设置当前位置
    @param [int] offset 偏移
    @param [int] origin 取如下值SEEK_CUR SEEK_END SEEK_SET
    @return 实际设置的位置
    */
    virtual s64 Seek(s64 offset, int origin);

    /** 设置流的大小
    @param [in] newSize 流的大小
    @return 实际分配的大小
    */
    virtual s64 ReSize(s64 newSize);

    /** 从pos开始读取流,由于取到内存中因此不能超过2^31位 (会改变pos)
    @param [out] buff 输出buff，内存需要自己管理
    @param [in] count 读取的大小
    @return 读取的实际大小
    */
    virtual s32 Read(u8* const buff, s32 count);

    /** 从pos开始写入流，一次性写入不能超过32位(会改变pos)
    @param [in] buff 写入buff，内存需要自己管理
    @param [in] count 写入的大小
    @return 写入的实际大小
    */
    virtual s32 Write(const u8* const buff, s32 count);

protected:
    /** 文件句柄
    */
    FILE* m_hFile;

    /** 路径
    */
    char* m_pPath;
};


#endif //__FILE_STREAM_H_
