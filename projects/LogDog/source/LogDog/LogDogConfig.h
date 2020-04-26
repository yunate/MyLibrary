
#ifndef _LOGDOGCONFIG_H__
#define _LOGDOGCONFIG_H__

#include "timer_recorder/timer_recorder.h"

#include "typedef/DogString.h"

#include <unordered_map>

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
    @param [in] atonce false 时候会有时间间隔，如果频繁的加载会被拒绝，true立刻加载
    */
    void TryReload(bool atonce = false);

    /* 分析配置文件是否有错误
    @return 错误码 返回LDC_NO_ERROR表示成功
    */
    LogDogConfigErrorCode GetErrorCode();

    /** 获得配置文件路径
    @return 配置文件路径
    */
    DogString& GetConfigPath();

    /** 获得配置文件名称
    @return 配置文件名称
    */
    DogString& GetConfigName();

    /** 获得配置文件中的字符串值
    @param [in] key key
    @param [out] 对于的返回值
    @reutrn 是否成功
    */
    bool GetStrVal(const DogString& key, DogString& val);

    /** 获得bool值
    @note : 忽略大小写的 "false" 或者0认为是false，其他都认为是true
    @param [in] key key
    @reutrn 配置中key对应的值，不存在返回false
    */
    bool GetBool(const DogString& key);

    /** 获得整数，如果不存在或者不能转换为整数返回0
    @param [in] key key
    @param [out] 对于的返回值
    @reutrn 是否成功
    */
    int GetInt32(const DogString& key);

private:
    /** 初始化
    */
    void ReLoad();

private:
    /** 配置文件路径
    */
    DogString m_path;

    /** 日志名称，如果需要写文件的话，它是文件的上一层目录名称
    */
    DogString m_name;

    /** 错误码
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** 日志中的配置
    */
    std::unordered_map<DogString, DogString> m_keyValue;

    /** 计时器
    */
    TimerRecorder m_timer;
};

#endif
