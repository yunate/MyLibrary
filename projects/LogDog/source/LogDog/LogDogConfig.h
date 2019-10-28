
#ifndef _LOGDOGCONFIG_H__
#define _LOGDOGCONFIG_H__

#include "LogDogDef.h"
#include "timer_recorder.h"

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
    /** 尝试重新加载
    @note 会有时间间隔，如果平凡的加载会被拒绝
    */
    void TryReload();

    /* 分析配置文件是否有错误
    @return 错误码 返回LDC_NO_ERROR表示成功
    */
    LogDogConfigErrorCode GetErrorCode();

    /** 获得日志配置
    @return 日志配置
    */
    LogDogConfigEntry& GetLogDogConfigEntry();

private:
    /** 初始化
    */
    void ReLoad();

private:
    /** 错误码
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** 当前数据条目
    */
    LogDogConfigEntry m_configEntry;

    /** 计时器
    */
    TimerRecorder m_timer;
};

#endif
