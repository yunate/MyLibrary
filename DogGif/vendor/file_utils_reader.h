
#ifndef __FILE_UTILS_READER_H_
#define __FILE_UTILS_READER_H_

#include <string>

/** �ļ���ȡ�࣬ÿ�ζ�ȡwchar
*/
class FileReader
{
public:
    /** ���캯��
    @param [in] path ·��
    @param [in] checker �ļ�ͷ���
    @param [in] �ļ�ͷ��С
    */
    FileReader(const std::wstring& path, const unsigned char* checker, const size_t checkSize);

    /** ��������
    */
    virtual ~FileReader();

    /** �Ƿ��д��󣨴��ļ��Ƿ�ɹ���
    @return �Ƿ�ɹ�
    */
    inline bool HasError()
    {
        return m_pFile == NULL;
    }

    /** ���һ�ǿ��У�����������,�������֮ǰ�ȼ���ļ���Ч�ԣ���HasError() == false,ÿ�ζ�wchar
    @param [out] line ���
    @return �Ƿ�ɹ�
    */
    bool GetLineW(std::wstring& line);

    /** ���һ�ǿ��У�����������,�������֮ǰ�ȼ���ļ���Ч�ԣ���HasError() == false,ÿ�ζ�char
    @param [out] line ���
    @return �Ƿ�ɹ�
    */
    bool GetLineA(std::string& line);

    /** ���size�����ݣ�buff��Ҫ�ⲿ�����ڴ�
    @param [out] buff �������
    @param [in] size ��С
    @return ʵ�ʻ�õĴ�С
    */
    size_t GetBuff(char* buff, const size_t& size);

    /** ����ļ���С
    @return �ļ���С
    */
    size_t GetFileSize();

protected:
    FILE* m_pFile;
};

/** ����һ��UCS-2 Little Endian ������ļ� ʹ��GetLineW()
@return FileReaderָ�룬�������Լ��ͷ�
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

/** ����һ��UTF8 ������ļ� ʹ��GetLineA()
@return FileReaderָ�룬�������Լ��ͷ�
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

/** ����һ��UTF8 BOM ������ļ� ʹ��GetLineA()
@return FileReaderָ�룬�������Լ��ͷ�
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
