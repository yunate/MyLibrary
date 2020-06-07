
#ifndef _LOGDOGCONFIG_H__
#define _LOGDOGCONFIG_H__

#include "timer_recorder/timer_recorder.h"

#include "base/g_def.h"

#include <unordered_map>
BEG_NSP_DDM
/** ���������ļ��Ĵ�����
*/
enum class LogDogConfigErrorCode
{
    /** û�д���
    */
    LDC_NO_ERROR = 0,

    /** �����ļ�������
    */
    LDC_NO_CONFIG_FILE,

    /** �����ļ���û���ҵ���Ӧ������
    */
    LDC_NO_MATCH_NAME
};

/** ��־�������ļ�
*/
class LogDogConfig
{
public:
    /** ���캯��������ʼ��
    @param [in] path �����ļ�·��
    @param [in] name �������в��ҵ���־����
    */
    LogDogConfig(const ddstr& path, const ddstr& name);

public:
    /** �������¼���
    @param [in] atonce false ʱ�����ʱ���������Ƶ���ļ��ػᱻ�ܾ���true���̼���
    */
    void TryReload(bool atonce = false);

    /* ���������ļ��Ƿ��д���
    @return ������ ����LDC_NO_ERROR��ʾ�ɹ�
    */
    LogDogConfigErrorCode GetErrorCode();

    /** ��������ļ�·��
    @return �����ļ�·��
    */
    ddstr& GetConfigPath();

    /** ��������ļ�����
    @return �����ļ�����
    */
    ddstr& GetConfigName();

    /** ��������ļ��е��ַ���ֵ
    @param [in] key key
    @param [out] ���ڵķ���ֵ
    @reutrn �Ƿ�ɹ�
    */
    bool GetStrVal(const ddstr& key, ddstr& val);

    /** ���boolֵ
    @note : ���Դ�Сд�� "false" ����0��Ϊ��false����������Ϊ��true
    @param [in] key key
    @reutrn ������key��Ӧ��ֵ�������ڷ���false
    */
    bool GetBool(const ddstr& key);

    /** �����������������ڻ��߲���ת��Ϊ��������0
    @param [in] key key
    @param [out] ���ڵķ���ֵ
    @reutrn �Ƿ�ɹ�
    */
    int GetInt32(const ddstr& key);

private:
    /** ��ʼ��
    */
    void ReLoad();

private:
    /** �����ļ�·��
    */
    ddstr m_path;

    /** ��־���ƣ������Ҫд�ļ��Ļ��������ļ�����һ��Ŀ¼����
    */
    ddstr m_name;

    /** ������
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** ��־�е�����
    */
    std::unordered_map<ddstr, ddstr> m_keyValue;

    /** ��ʱ��
    */
    TimerRecorder m_timer;
};
END_NSP_DDM
#endif
