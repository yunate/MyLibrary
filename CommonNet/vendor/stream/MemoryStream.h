
#ifndef __MEMORYSTREAM_H_
#define __MEMORYSTREAM_H_

#include "IDogStream.h"

/** �ڴ���������ڴ棺min(4G, ϵͳ����)
*/
class MemoryStream :
    public IDogStream
{
public:
    /** ���캯��
    */
    MemoryStream();

    /** ���캯��
    @param [in] size ��С
    */
    MemoryStream(u32 size);

    /** ���캯��
    @param [in] pBuff �ڴ�
    @param [in] size ��С
    */
    MemoryStream(const s8* const pBuff, u32 size);

    /** ���캯��
    @param [in] stream ��
    */
    MemoryStream(MemoryStream&& stream);

    /** ���캯��
    @param [in] stream ��
    */
    MemoryStream(const IDogStream& stream);

    /** ���캯��
    @param [in] stream ��
    */
    MemoryStream(const MemoryStream& stream);

    /** ���������
    @param [in] stream ��
    */
    MemoryStream& operator=(const IDogStream& stream);

    /** ���������
    @param [in] stream ��
    */
    MemoryStream& operator=(const MemoryStream& stream);

    /** ��������
    */
    virtual ~MemoryStream();

    /** ��õ�ǰλ�� seek
    @return ��ǰλ��
    */
    virtual s64 Pos();

    /** ���õ�ǰλ��
    @param [int] offset ƫ��
    @param [int] origin ȡ����ֵSEEK_CUR SEEK_END SEEK_SET
    @return ʵ�����õ�λ��
    */
    virtual s64 Seek(s64 offset, int origin);

    /** ������Ĵ�С
    @return ���Ĵ�С
    */
    virtual s64 Size();

    /** �������Ĵ�С���ڴ治��ʱ����Զ����䣬���ǲ����ʼ���ڴ�
    @param [in] newSize ���Ĵ�С
    @return ʵ�ʷ���Ĵ�С
    */
    virtual s64 ReSize(s64 newSize);

    /** ���ʵ��buff��С��������GetSize
    @return ��ʹ�õ��ڴ�
    */
    u32 Capacity();

    /** �������
    */
    void Clear();

    /** ��pos��ʼ��ȡ�� (��ı�pos)
    @param [out] buff ���buff���ڴ���Ҫ�Լ�����
    @param [in] count ��ȡ�Ĵ�С
    @return ��ȡ��ʵ�ʴ�С
    */
    virtual s32 Read(u8* const buff, s32 count);

    /** ��pos��ʼд���� (��ı�pos)
    @param [in] buff д��buff���ڴ���Ҫ�Լ�����
    @param [in] count д��Ĵ�С
    @return д���ʵ�ʴ�С
    */
    virtual s32 Write(const u8* const buff, s32 count);

protected:
    /** ���·����ڴ�(��ȻnewSize��64λ�ģ�����������������ڴ治�ᳬ��32λҲ����4G)
    @param [in] newSize �µĴ�С
    @return ʵ�ʷ���Ĵ�С
    */
    u32 ReallocMemory(u32 newSize);

    /** ���¼��㼴��������ڴ��С
    @param [in] newSize �û�����
    @return �����Ĵ�С
    */
    u32 CalNewSize(u32 newSize);

protected:
    /** ��ǰλ��
    */
    u32 m_pos;

    /** ʵ��ʹ�õĴ�С
    */
    u32 m_size;

    /** �ܴ�С
    */
    u32 m_capacity;

    /** ����
    */
    s8* m_pBuff;
};

#endif //__MEMORYSTREAM_H_
