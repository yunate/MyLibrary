
#ifndef __BIG_FILE_UTILS_H_
#define __BIG_FILE_UTILS_H_

#include "noncopyable/noncopyable.h"
#include "typedef/DogString.h"

#include <memory>

/** 默认文件块大小10M
*/
static const int g_file_block_default_size = 1024 * 1024 * 10;

class BigFileMapper;

/** 一个大文件的文件块
*/
class FileBlock :
    public NonCopyable
{
public:
    /** 析构函数
    */
    ~FileBlock();

    /** 获得文件块大小
    @return 文件块的大小
    */
    inline int GetSize()
    {
        return m_blockSize;
    }

    /** 获得真正的文件块起始地址
    @return 文件块的起始地址
    */
    inline char* GetBlockAddr()
    {
        return m_pBlock + m_offSet;
    }

private:
    /** 文件块起始地址
    */
    char* m_pBlock = NULL;

    /** 由于文件映射要求64k对齐，所以这儿的offset才是真正的开始
    */
    int m_offSet = 0;

    /** 文件块大小
    */
    int m_blockSize = 0;

    friend BigFileMapper;
};

using SPFileBlock = std::shared_ptr<FileBlock>;

/** 内存映射文件来处理大文件，可读写，但是在文件大小改变了的话需要重新映射
*/
class BigFileMapper :
    public NonCopyable
{
public:
    /** 构造函数
    */
    BigFileMapper();

    /** 析构函数
    */
    ~BigFileMapper();

public:
    /** 初始化，重复调用会清空上一次的数据
    @param [in] filePath 文件路径
    @return 是否成功
    */
    bool MapFile(const DogString& filePath);

    /** 获得文件大小
    @return 文件大小
    */
    inline long long GetFileSize()
    {
        return m_fileSize;
    }

    /** 获得文件块的下一块
    @param [in] size 指定大小（B），如果小于等于0或者大于1G的话使用默认大小，如果有末尾对齐（align != 0）返回的block大小可能要小于size
    @param [in] align size 指定的大小可能不在一个句子的尾巴，所以会向前找到第一个出现align（包括）的字符处,align == 0 说明不对齐，默认"\n"
    @return 文件块的share_ptr，如果为空说明map到文件尾部了
    */
    SPFileBlock GetNextBlock(int sizeRaw = g_file_block_default_size, char align = '\n');

    /** 获得文件块的下一块
    @param [in] beginPos 开始位置
    @param [in] size 指定大小（B），如果小于等于0或者大于1G的话使用默认大小，如果有末尾对齐（align != 0）返回的block大小可能要小于size
    @param [in] align size 指定的大小可能不在一个句子的尾巴，所以会向前找到第一个出现align（包括）的字符处,align == 0 说明不对齐，默认"\n"
    @return 文件块的share_ptr，如果为空说明map到文件尾部了
    */
    SPFileBlock GetBlock(__int64 beginPos, int sizeRaw = g_file_block_default_size, char align = '\n');

private:
    /** 文件映射内存的句柄
    */
    void* m_hFileMap;

    /** 映射的位置
    */
    long long m_bginPos;

    /** 文件小
    */
    long long m_fileSize;
};

#endif //__BIG_FILE_UTILS_H_
