
#ifndef __FILE_UTILS_READER_H_
#define __FILE_UTILS_READER_H_

#include <string>

/** 文件读取类，每次读取wchar
*/
class FileReader
{
public:
    /** 构造函数
    @param [in] path 路径
    @param [in] checker 文件头检查
    @param [in] 文件头大小
    */
    FileReader(const std::wstring& path, const unsigned char* checker, const size_t checkSize);

    /** 析构函数
    */
    virtual ~FileReader();

    /** 是否有错误（打开文件是否成功）
    @return 是否成功
    */
    inline bool HasError()
    {
        return m_pFile == NULL;
    }

    /** 获得一非空行（空行跳过）,调用这个之前先检查文件有效性，即HasError() == false,每次度wchar
    @param [out] line 输出
    @return 是否成功
    */
    bool GetLineW(std::wstring& line);

    /** 获得一非空行（空行跳过）,调用这个之前先检查文件有效性，即HasError() == false,每次度char
    @param [out] line 输出
    @return 是否成功
    */
    bool GetLineA(std::string& line);

    /** 获得size个数据，buff需要外部分配内存
    @param [out] buff 输出数组
    @param [in] size 大小
    @return 实际获得的大小
    */
    size_t GetBuff(char* buff, const size_t& size);

protected:
    FILE* m_pFile;
};

/** 创建一个UCS-2 Little Endian 编码的文件 使用GetLineW()
@return FileReader指针，别忘了自己释放
*/
inline FileReader* CreateUCS2FileReader(const std::wstring& path)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    FileReader* pFileReader = new (std::nothrow) FileReader(path, header, 2);

    if (pFileReader == NULL)
    {
        return NULL;
    }

    if (pFileReader->HasError())
    {
        delete pFileReader;
        return NULL;
    }

    return pFileReader;
}

/** 创建一个UTF8 编码的文件 使用GetLineA()
@return FileReader指针，别忘了自己释放
*/
inline FileReader* CreateUTF8FileReader(const std::wstring& path)
{
    FileReader* pFileReader = new (std::nothrow) FileReader(path, NULL, 0);

    if (pFileReader == NULL)
    {
        return NULL;
    }

    if (pFileReader->HasError())
    {
        delete pFileReader;
        return NULL;
    }

    return pFileReader;
}

/** 创建一个UTF8 BOM 编码的文件 使用GetLineA()
@return FileReader指针，别忘了自己释放
*/
inline FileReader* CreateUTF8BomFileReader(const std::wstring& path)
{
    unsigned char header[] = {0xef, 0xbb, 0xbf, '\0'};
    FileReader* pFileReader = new (std::nothrow) FileReader(path, header, 3);

    if (pFileReader == NULL)
    {
        return NULL;
    }

    if (pFileReader->HasError())
    {
        delete pFileReader;
        return NULL;
    }

    return pFileReader;
}

#endif // __FILE_UTILS_READER_H_
