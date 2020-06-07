
//////////////////////////////////////////////////////////////////////////
// �ṩһ����־ʵ����࣬�Լ�һЩ���õ�ʵ��                                     //
//////////////////////////////////////////////////////////////////////////

#ifndef __ILOG_H_
#define __ILOG_H_

#include "ILogExecutor.h"
#include "base/nocopyable.hpp"
#include "LogDogDef.h"

#include "thread/task/i_ddtask.h"

#include <assert.h>
#include <memory>
#include <vector>

BEG_NSP_DDM
/** ��־ʵ��
*/
class ILog :
    public i_ddtask,
    public nocopyable
{
public:
    ILog();

    virtual ~ILog();

    /** ִ������
    */
    virtual void do_task() override;

    /** ��־����
    */
    virtual void Log() = 0;

    /** ֹͣ����
    */
    virtual void stop() override
    {
        // ɾ��
    };
};

/** �ṩһ���򵥻��࣬����־�����Ϊ�����֣��ַ�����format���Դ������ַ��������ļ���¼�����紫��ȣ�
*/
class ISimpleLog :
    public ILog
{
public:
    /** ���캯��
    @param [in] level ��־�Ȼ�
    @param [in] logStr ��־��������
    */
    ISimpleLog(LogDogConfigLevel level, const ddstr& logStr);

    /** ��������
    */
    virtual ~ISimpleLog();

    /** ��־
    */
    virtual void Log();

    /** ���һ��ִ����
    @param [in] executor ִ����
    */
    void PushExecutor(const std::shared_ptr<ILogExecutor>& executor);

private:
    /** ��ʽ����־�ַ���
    @param [out] outLogStr ����ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool MakeLogStr(ddstr& outLogStr) = 0;

protected:
    /** ��־�ȼ�
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_5;

    /** ��־����
    */
    ddstr m_logStr;

    /** ����ִ����
    */
    std::vector<std::shared_ptr<ILogExecutor> > m_executors;
};

/** һ������־�����࣬����־���˻�����Ϣ���ļ�����������־�ȼ�����formate
*/
class SimpleLog :
    public ISimpleLog
{
public:
    /** ���캯��
    @param [in] logStr ��־��������
    */
    SimpleLog(LogDogConfigLevel level, const ddstr& logStr);

    /** ��������
    */
    ~SimpleLog();

private:
    /** ��ʽ����־�ַ���
    @param [out] outLogStr ����ַ���
    @return �Ƿ�ɹ�
    */
    virtual bool MakeLogStr(ddstr& outLogStr);
};

END_NSP_DDM
#endif //__ILOG_H_
