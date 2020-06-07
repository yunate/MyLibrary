
#ifndef __LOGDOGDEF_H_
#define __LOGDOGDEF_H_

#include "base/g_def.h"
#include <tchar.h>
BEG_NSP_DDM

#ifdef _UNICODE
#define _MY_FILE__ __FILEW__
#define _MY_FUNC__ __FUNCTIONW__
#else
#define _MY_FILE__ __FILE__
#define _MY_FUNC__ __FUNCTION__
#endif // 

/** ��־�ȼ�
*/
enum class LogDogConfigLevel
{
    /** 0 crash
    */
    LDC_LEVEL_0 = 0,

    /** 1 �������ص�
    */
    LDC_LEVEL_1,

    /** 2 ���ص�
    */
    LDC_LEVEL_2,

    /** 3 assert
    */
    LDC_LEVEL_3,

    /** 4 ����
    */
    LDC_LEVEL_4,

    /** 5 ��ͨ��־
    */
    LDC_LEVEL_5,

    /** 6 ������Ϣ
    */
    LDC_LEVEL_6,

    /** ��Ч
    */
    LDC_LEVEL_END,
};

/** ��ʼ��
@param [in] path �����ļ�·��
@param [in] name �����ļ��ж�Ӧ��secsion
@eg :
///////////////////////////////test.ini///////////////////////////////////////////
//                              UCS-2 Little Endian                             //
//                              [����]                                           //
//                              level=4                                         //
//                              dump_to_file=true                               //
//                              upload=1                                        //
///////////////////////////////test.ini///////////////////////////////////////////
*/
void LOG_INIT(const ddstr& path, const ddstr& name);

/** ����ʼ��
*/
void LOG_UNINIT();

/** ����־
@param [in] level ��־�ȼ�
@param [in] logStr ��־��������
*/
void SIMPLE_LOG(LogDogConfigLevel level, const ddstr& logStr);

/** �����ļ����ƺ��к�
@param [in] level ��־�ȼ�
@param [in] logStr ��־����
@param [in] file ���ں���
@param [in] file �����ļ�
@param [in] line ��������
*/
#define LOG_FILE_FUNC_LINE_PRI(level, logStr, file, func, line) \
{\
ddstr tmp = _DDT("[log:\"");\
tmp += logStr;\
tmp += _DDT("\"] [file:\"");\
tmp += file;\
tmp += _DDT("\" func:\"");\
tmp += func;\
tmp += _DDT("\" line:\"");\
ddchar lineBuff[10] = { 0 };\
::_itot_s(line, lineBuff, 9, 10);\
tmp += lineBuff;\
tmp += _DDT("\"]");\
SIMPLE_LOG(level, tmp);\
}

#define LOG_FILE_FUNC_LINE(level, logStr) LOG_FILE_FUNC_LINE_PRI(level, logStr, _MY_FILE__, _MY_FUNC__,__LINE__)

/** ������Ϣ
*/
#define LOG_DEBUG(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_6, logStr)

/** ��ͨ��Ϣ
*/
#define LOG_INFO(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_5, logStr)

/** ����
*/
#define LOG_WARNING(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_4, logStr)

/** assert �����п�/��ĸΪ0
*/
#define LOG_ASSERT(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_3, logStr)

/** ���صĴ��󣬱�����Դ�����˵�
*/
#define LOG_SERIOUS_ERROR(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_2, logStr)

/** �������صĴ����Ҳ�֪���ͱ�����ɶ����o_0
*/
#define LOG_VERY_SERIOUS_ERROR(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_1, logStr)

/** ����������󣬱�����Ϊʲô�ܹ�����־����ʵ��Ҳ��֪��
@note try catch �еı����ϱ�
*/
#define LOG_CRASH(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_0, logStr)
END_NSP_DDM
#endif // __LOGDOGDEF_H_
