#ifndef __MEMORYSHARE_H_
#define __MEMORYSHARE_H_

#include <string>
#include <Windows.h>

/** 共享内存
*/
class ShareMemory
{
public:
    ShareMemory();
    ~ShareMemory();

    // 不允许拷贝
    ShareMemory(const ShareMemory&) = delete;
    ShareMemory(ShareMemory&&) = delete;
    ShareMemory& operator=(const ShareMemory&) = delete;

public:
    /** 创建共享内存，如果已经存在则打开
    @param [in] name 共享内存名称，为空时失败
    @param [in] size 大小
    @return 是否成功
    */
    bool Create(const std::wstring name, size_t size);

    /** 打开共享内存，如果不存在则打开失败
    @param [in] name 共享内存名称，为空时失败
    @return 是否成功
    */
    bool Open(const std::wstring name);

    /** 获得内存地址，失败返回NULL
    @param [in] offset 相对于开始的位置
    @return 返回映射的地址，失败返回NULL
    */
    void* GetBuff(size_t offset = 0);

private:
    /** 上一次的映射
    */
    void* m_pMapViewOfFile;

    /** m_pMapViewOfFile映射的位置，一般从0开始
    */
    size_t m_offset;

    /** 内存映射句柄，本类不会去close这个句柄，而是将他交给管理类管理
    */
    HANDLE m_hMap;
};

#endif
