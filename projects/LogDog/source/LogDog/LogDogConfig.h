
#ifndef _LOGDOGCONFIG_H__
#define _LOGDOGCONFIG_H__

#include "LogDogDef.h"

/** 日志的配置文件
*/
class LogDogConfig
{
public:
    /** 构造函数，并初始化
    @param [in] path 配置文件路径
    @param [in] name 在配置中查找的日志名称
    */
    LogDogConfig(const DogString& path, const DogString& name);

public:
    /** 初始化
    @param [in] path 配置文件路径
    */
    void ReLoad(const DogString& path, const DogString& name);

    /* 分析配置文件是否有错误
    @return 错误码 返回LDC_NO_ERROR表示成功
    */
    LogDogConfigErrorCode GetErrorCode();

    /** 获得日志配置
    @return 日志配置
    */
    LogDogConfigEntry& GetLogDogConfigEntry();

private:
    /** 错误码
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** 当前数据条目
    */
    LogDogConfigEntry m_configEntry;
};

#endif
