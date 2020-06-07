
#ifndef __FILE_STREAM_H_
#define __FILE_STREAM_H_

#include "IDogStream.h"
#include "typedef/DogString.h"

#include <stdio.h>

class FileStream :
    public IDogStream
{
public:
    /** ���캯��
    @param [in] path ·��
    @param [in] mode �򿪷�ʽ,mode == NULL ʱ��Ĭ��Ϊ"a+b"
    */
    FileStream(const DogChar* const path, const DogChar* const mode = NULL);

    /** �ƶ����칹�캯��
    @param [in] stream ��
    */
    FileStream(FileStream&& stream) noexcept;

    /** ��������
    */
    virtual ~FileStream();

    /** ��������
    */
    FileStream(const FileStream& stream) = delete;

    /** ��������
    */
    FileStream& operator=(const FileStream& stream) = delete;

public:
    /** ��õ�ǰλ�� seek
    @return ��ǰλ��,-1��ʾʧ�ܣ��μ�ftell
    */
    virtual s64 Pos();

    /** ���õ�ǰλ��
    @param [int] offset ƫ��
    @param [int] origin ȡ����ֵSEEK_CUR SEEK_END SEEK_SET
    @return ʵ�����õ�λ��
    */
    virtual s64 Seek(s64 offset, int origin);

    /** �������Ĵ�С
    @param [in] newSize ���Ĵ�С
    @return ʵ�ʷ���Ĵ�С
    */
    virtual s64 ReSize(s64 newSize);

    /** ��pos��ʼ��ȡ��,����ȡ���ڴ�����˲��ܳ���2^31λ (��ı�pos)
    @param [out] buff ���buff���ڴ���Ҫ�Լ�����
    @param [in] count ��ȡ�Ĵ�С
    @return ��ȡ��ʵ�ʴ�С
    */
    virtual s32 Read(u8* const buff, s32 count);

    /** ��pos��ʼд������һ����д�벻�ܳ���32λ(��ı�pos)
    @param [in] buff д��buff���ڴ���Ҫ�Լ�����
    @param [in] count д��Ĵ�С
    @return д���ʵ�ʴ�С
    */
    virtual s32 Write(const u8* const buff, s32 count);

protected:
    /** �ļ����
    */
    FILE* m_hFile;

    /** ·��
    */
    DogChar* m_pPath;
};


#endif //__FILE_STREAM_H_
