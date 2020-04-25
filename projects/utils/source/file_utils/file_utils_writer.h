
#ifndef __FILE_UTILS_WRITER_H_
#define __FILE_UTILS_WRITER_H_

#include <string>
#include <memory>

/** 文件读取类，每次读取wchar
*/
class FileWriter
{
public:
    /** 构造函数
    @param [in] path 路径
    @param [in] header 文件头检查
    @param [in] 文件头大小
    */
    FileWriter(const std::wstring& path, const unsigned char * header, const size_t headSize);

    /** 析构函数
    */
    virtual ~FileWriter();

    /** 是否有错误（打开文件是否成功）
    @return 是否成功
    */
    inline bool HasError()
    {
        return m_pFile == NULL;
    }

    /** 写wchar
    @param [in] buff 输入数组
    @param [in] size 数组大小
    @return 是否成功
    */
    bool WriteBuffW(const wchar_t* buff, const size_t size);

    /** 写char
    @param [out] line 输出
    @return 是否成功
    */
    bool WriteBuffA(const char* buff, const size_t size);

protected:
    FILE* m_pFile;
};

using SPFileWriter = std::shared_ptr<FileWriter>;

/** 创建一个UCS-2 Little Endian 编码的文件 使用WriteBuffW()
@return FileReader的shared_ptr
*/
inline SPFileWriter CreateUCS2FileWriter(const std::wstring& path)
{
    unsigned char header[] = {0xff, 0xfe, '\0'};
    FileWriter* pFileWriter = new (std::nothrow) FileWriter(path, header, 2);

    if (pFileWriter == NULL)
    {
        return NULL;
    }

    if (pFileWriter->HasError())
    {
        delete pFileWriter;
        return NULL;
    }

    return SPFileWriter(pFileWriter);
}

/** 创建一个UTF8 编码的文件 使用WriteBuffA()
@return FileReader的shared_ptr
*/
inline SPFileWriter CreateUTF8FileWriter(const std::wstring& path)
{
    FileWriter* pFileWriter = new (std::nothrow) FileWriter(path, NULL, 0);

    if (pFileWriter == NULL)
    {
        return NULL;
    }

    if (pFileWriter->HasError())
    {
        delete pFileWriter;
        return NULL;
    }

    return SPFileWriter(pFileWriter);
}

/** 创建一个UTF8 BOM 编码的文件 使用WriteBuffA()
@return FileReader的shared_ptr
*/
inline SPFileWriter CreateUTF8BomFileWriter(const std::wstring& path)
{
    unsigned char header[] = {0xef, 0xbb, 0xbf, '\0'};
    FileWriter* pFileWriter = new (std::nothrow) FileWriter(path, header, 3);

    if (pFileWriter == NULL)
    {
        return NULL;
    }

    if (pFileWriter->HasError())
    {
        delete pFileWriter;
        return NULL;
    }

    return SPFileWriter(pFileWriter);
}

#endif // __FILE_UTILS_WRITER_H_
