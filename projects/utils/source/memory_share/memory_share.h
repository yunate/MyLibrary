#ifndef __MEMORYSHARE_H_
#define __MEMORYSHARE_H_

#include <string>
#include <Windows.h>

#define  BUF_SIZE 100
#define  FLAG 1

/** 线程间通信使用---------------------TODO 以后有空重新写
*/
class MemoryShare
{
public:
    /** 构造函数
    @param [in] sShareName 共享内存名称
    */
    MemoryShare(const std::string & sShareName);

    /** 析构函数
    */
    ~MemoryShare();

public:
    /** 写内存
    @param [in] pBuf 要写的数组，外部负责释放
    @param [in] nSize buff 大小
    @return 是否成功
    */
    bool Write(const void * pBuf, int nSize);

    /** 读内存
    @param [out] pBuf 大小为BUF_SIZE，内存需要自己解决
    @return 是否成功
    */
    bool Read(void * pBuf);

    /** 清空
    @return 是否成功
    */
    bool Clear();

    /** 可以写了吗
    @return 是否可以写了
    */
    bool IsReadToWrite();

    /** 可以读了吗
    @return 是否可以读了
    */
    bool IsReadToRead();

    /** 有多大
    @return 大小
    */
    int GetBuffSize();

private:
    /** 映射
    */
    HANDLE  m_hMapFile;

    /** m_lpBase
    */
    LPVOID    m_lpBase;
};

#endif
