
#ifndef __IDOGSTREAM_H_
#define __IDOGSTREAM_H_

#include <stdio.h>

/** �޷���8λ
*/
using u8 = unsigned char;

/** �޷���16λ
*/
using u16 = unsigned short;

/** �޷���32λ
*/
using u32 = unsigned long;

/** �޷���64λ
*/
using u64 = unsigned long long;

/** �з���8λ
*/
using s8 = char;

/** �з���16λ
*/
using s16 = short;

/** �з���32λ
*/
using s32 = long;

/** �з���64λ
*/
using s64 = long long;

/** ��� (n * b) �� a <= (n * b) <= a + b
@param [in] a ���ܳ���0xffffffff - (b - 1)���򷵻�С��a
@param [in] b
@return b�������ڵ���a����С�Ͻ磬���С��a��˵��ʧ��
*/
inline u32 GetMinUpper(u64 a, u64 b)
{
    --b;
    return (u32)((a + b) & (~b));
}

/** ���ݿ��С��λ 1 K
*/
#define MET_DATA_SIZE 0x400

/** 32λ�з��������ֵ
*/
#define  MAX_S32 0x7fffffff

/** 32λ�޷��������ֵ
*/
#define  MAX_U32 0xffffffff

/** ���Ļ���
*/
class  IDogStream
{
public:
    /** ��������
    */
    virtual ~IDogStream() { };

    /** ��õ�ǰλ�� seek
    @return ��ǰλ�� 
    */
    virtual s64 Pos() = 0;

    /** ���õ�ǰλ��
    @param [int] offset ƫ��
    @param [int] origin ȡ����ֵSEEK_CUR SEEK_END SEEK_SET
    @return ʵ�����õ�λ��
    */
    virtual s64 Seek(s64 offset, int origin) = 0;

    /** ������Ĵ�С
    @return ���Ĵ�С
    */
    virtual s64 Size()
    {
        s64 curPos = Pos();
        s64 end = Seek(0, SEEK_END);
        Seek(curPos, SEEK_SET);
        return end;
    }

    /** �������Ĵ�С
    @param [in] newSize ���Ĵ�С
    @return ʵ�ʷ���Ĵ�С
    */
    virtual s64 ReSize(s64 newSize) = 0;

    /** ��pos��ʼ��ȡ��,����ȡ���ڴ�����˲��ܳ���2^31λ (��ı�pos)
    @param [out] buff ���buff���ڴ���Ҫ�Լ�����
    @param [in] count ��ȡ�Ĵ�С
    @return ��ȡ��ʵ�ʴ�С
    */
    virtual s32 Read(u8* const buff, s32 count) = 0;

    /** ��pos��ʼд������һ����д�벻�ܳ���32λ(��ı�pos)
    @param [in] buff д��buff���ڴ���Ҫ�Լ�����
    @param [in] count д��Ĵ�С
    @return д���ʵ�ʴ�С
    */
    virtual s32 Write(const u8* const buff, s32 count) = 0;

    /** ��ȡ�� (��ı�pos)
    @param [out] buff ���buff���ڴ���Ҫ�Լ�����
    @param [in] count ��ȡ�Ĵ�С
    @return ��ȡ��ʵ�ʴ�С
    */
    virtual s32 ReadW(u16* const buff, s32 count)
    {
        return Read((u8*)buff, count * 2) / 2;
    }

    /** д���� (��ı�pos)
    @param [in] buff д��buff���ڴ���Ҫ�Լ�����
    @param [in] count д��Ĵ�С
    @return д���ʵ�ʴ�С
    */
    virtual s32 WriteW(const u16* const buff, s32 count)
    {
        return Write((const u8*)buff, count * 2) / 2;
    }

    /** ��ȡȫ��������ȡ���ڴ�����˲��ܳ���2^31λ�����ʵ�ʴ�С����2^31λ����ô�˺���ֻ��ȡǰ2^31λ (��ı�pos)
    @param [out] buff ���buff���ڴ���Ҫ�Լ�����
    @return ��ȡ��ʵ�ʴ�С
    */
    virtual s32 ReadAllA(u8* const buff)
    {
        Seek(0, SEEK_SET);
        return Read(buff, (s32)Size());
    }

    /** ��ȡȫ�� (��ı�pos)
    @param [out] buff ���buff���ڴ���Ҫ�Լ�����
    @return ��ȡ��ʵ�ʴ�С
    */
    virtual s32 ReadAllW(u16* const buff)
    {
        return ReadAllA((u8*)buff) / 2;
    }
};


#endif //__IDOGSTREAM_H_
