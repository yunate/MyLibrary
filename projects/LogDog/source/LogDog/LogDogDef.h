
#ifndef __LOGDOGDEF_H_
#define __LOGDOGDEF_H_

#include "typedef/DogString.h"

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

struct LogDogConfigEntry
{
    /** 配置文件路径
    */
    DogString m_path;

    /** 日志名称，如果需要写文件的话，它是文件的上一层目录名称
    */
    DogString m_name;

    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_4;

    /** 是否需要写入文件
    */
    bool m_isNeedDmpToFile = false;

    /** 是否需要上传
    */
    bool m_isNeedUpload = false;
};

/** 解析配置文件的错误码
*/
enum class LogDogConfigErrorCode
{
    /** 没有错误
    */
    LDC_NO_ERROR = 0,

    /** 配置文件不存在
    */
    LDC_NO_CONFIG_FILE,

    /** 配置文件中没有找到对应的名字
    */
    LDC_NO_MATCH_NAME
};

/** 初始化
@param [in] path 配置文件路径
@param [in] name 配置文件中对应的secsion
*/
void LOG_INIT(const DogString& path, const DogString& name);

/** 反初始化
*/
void LOG_UNINIT();

/** 简单日志
@param [in] level 日志等级
@param [in] logStr 日志具体内容
*/
inline void SIMPLE_LOG(LogDogConfigLevel level, const DogString& logStr);

/** 调试信息
*/
#define LOG_DEBUG(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_6, logStr)

/** 普通信息
*/
#define LOG_INFO(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_5, logStr)

/** 警告
*/
#define LOG_WARNING(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_4, logStr)

/** assert 比如判空/分母为0
*/
#define LOG_ASSERT(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_3, logStr)

/** 严重的错误，比如资源不足了等
*/
#define LOG_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_2, logStr)

/** 极其严重的错误，我不知道和崩溃有啥区别o_0
*/
#define LOG_VERY_SERIOUS_ERROR(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_1, logStr)

/** 程序崩溃错误，崩溃了为什么能够打日志？其实我也不知道
@note try catch 中的崩溃上报
*/
#define LOG_CRASH(logStr) SIMPLE_LOG(LogDogConfigLevel::LDC_LEVEL_0, logStr)

#endif // __LOGDOGDEF_H_
