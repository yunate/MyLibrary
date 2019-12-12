
#ifndef __LOGDOGDEF_H_
#define __LOGDOGDEF_H_

#include "typedef/DogString.h"
#include <tchar.h>

#ifdef _UNICODE
#define _MY_FILE__ __FILEW__
#define _MY_FUNC__ __FUNCTIONW__
#else
#define _MY_FILE__ __FILE__
#define _MY_FUNC__ __FUNCTION__
#endif // 

/** 日志等级
*/
enum class LogDogConfigLevel
{
    /** 0 crash
    */
    LDC_LEVEL_0 = 0,

    /** 1 极其严重的
    */
    LDC_LEVEL_1,

    /** 2 严重的
    */
    LDC_LEVEL_2,

    /** 3 assert
    */
    LDC_LEVEL_3,

    /** 4 警告
    */
    LDC_LEVEL_4,

    /** 5 普通日志
    */
    LDC_LEVEL_5,

    /** 6 调试信息
    */
    LDC_LEVEL_6,

    /** 无效
    */
    LDC_LEVEL_END,
};

/** 初始化
@param [in] path 配置文件路径
@param [in] name 配置文件中对应的secsion
@eg :
///////////////////////////////test.ini///////////////////////////////////////////
//                              UCS-2 Little Endian                             //
//                              [测试]                                           //
//                              level=4                                         //
//                              dump_to_file=true                               //
//                              upload=1                                        //
///////////////////////////////test.ini///////////////////////////////////////////
*/
void LOG_INIT(const DogString& path, const DogString& name);

/** 反初始化
*/
void LOG_UNINIT();

/** 简单日志
@param [in] level 日志等级
@param [in] logStr 日志具体内容
*/
void SIMPLE_LOG(LogDogConfigLevel level, const DogString& logStr);

/** 加上文件名称和行号
@param [in] level 日志等级
@param [in] logStr 日志内容
@param [in] file 所在函数
@param [in] file 所在文件
@param [in] line 所在行数
*/
#define LOG_FILE_FUNC_LINE_PRI(level, logStr, file, func, line) \
{\
DogString tmp = _DogT("[log:\"");\
tmp += logStr;\
tmp += _DogT("\"] [file:\"");\
tmp += file;\
tmp += _DogT("\" func:\"");\
tmp += func;\
tmp += _DogT("\" line:\"");\
DogChar lineBuff[10] = { 0 };\
::_itot_s(line, lineBuff, 9, 10);\
tmp += lineBuff;\
tmp += _DogT("\"]");\
SIMPLE_LOG(level, tmp);\
}

#define LOG_FILE_FUNC_LINE(level, logStr) LOG_FILE_FUNC_LINE_PRI(level, logStr, _MY_FILE__, _MY_FUNC__,__LINE__)

/** 调试信息
*/
#define LOG_DEBUG(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_6, logStr)

/** 普通信息
*/
#define LOG_INFO(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_5, logStr)

/** 警告
*/
#define LOG_WARNING(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_4, logStr)

/** assert 比如判空/分母为0
*/
#define LOG_ASSERT(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_3, logStr)

/** 严重的错误，比如资源不足了等
*/
#define LOG_SERIOUS_ERROR(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_2, logStr)

/** 极其严重的错误，我不知道和崩溃有啥区别o_0
*/
#define LOG_VERY_SERIOUS_ERROR(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_1, logStr)

/** 程序崩溃错误，崩溃了为什么能够打日志？其实我也不知道
@note try catch 中的崩溃上报
*/
#define LOG_CRASH(logStr) LOG_FILE_FUNC_LINE(LogDogConfigLevel::LDC_LEVEL_0, logStr)
#endif // __LOGDOGDEF_H_
