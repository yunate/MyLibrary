
#ifndef __LOGDOGDEF_H_
#define __LOGDOGDEF_H_

#include <string>

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
    std::wstring m_path;

    /** 日志名称，如果需要写文件的话，它是文件的上一层目录名称
    */
    std::wstring m_name;

    /** 日志等级
    */
    LogDogConfigLevel m_level = LogDogConfigLevel::LDC_LEVEL_4;

    /** 是否需要写入文件
    */
    bool m_isNeedDmpToFile = false;
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

    /** 配置文件中没有找到响应的名字
    */
    LDC_NO_MATCH_NAME
};

#endif //__LOGDOGDEF_H_
