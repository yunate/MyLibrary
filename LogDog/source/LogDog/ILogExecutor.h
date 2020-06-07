
#ifndef __LOG_EXECUTOR_H_
#define __LOG_EXECUTOR_H_

#include "base/g_def.h"
#include "LogDogConfig.h"
BEG_NSP_DDM
class ILogExecutor
{
public:
    virtual ~ILogExecutor()
    {
    }

    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const ddstr& logStr) = 0;
};

/** �ṩһ��д���ļ��Ĵ�����
*/
class DumpToFileExecutor :
    public ILogExecutor
{
public:
    /** ���캯��
    */
    DumpToFileExecutor();

    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const ddstr& logStr);

private:
    /** ��ȡ��־�ļ�·��������������򴴽�
    @param [in, out] logLen ��־����
    @param [in] baseDirBath Ŀ¼·��
    @return ��־�ļ�·��
    */
    ddstr GetAndCreateLogFile(size_t logLen, const ddstr& baseDirBath);

    /** ����ļ���С�Ƿ����Ԥ�ڣ�������������´����ļ�
    @param [in, out] logLen ��־����
    @param [in, out] filePath ��ǰ�ļ�·��
    @return �Ƿ�ɹ�
    */
    bool CheckFileSizeAndCreate(size_t logLen, ddstr& filePath);

    /** ���� "910",ִ�к��� "911"
    @param [in, out] ����
    @param [in] len ����
    @return �Ƿ�ɹ������buff�������ַ���false,����ﵽ���ֵ��ѭ����0
    */
    bool StrInc(ddchar* buff, int len);
};

/** �ṩһ����������Ĵ�����
*/
class UpLoadExecutor :
    public ILogExecutor
{
public:
    /** ��־��������
    @param [in] logStr ��־�ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool Executor(const ddstr& logStr);
};
END_NSP_DDM
#endif //__LOG_EXECUTOR_H_
