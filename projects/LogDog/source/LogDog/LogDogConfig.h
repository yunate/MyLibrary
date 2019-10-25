
#ifndef _LOGCONFIG_H_
#define _LOGCONFIG_H_

#include "Export/LogDogDef.h"
#include "noncopyable.h"

/** 日志的配置文件
*/
class LogDogConfig :
    public NonCopyable
{
public:
    /** 构造函数
    */
    LogDogConfig();

    /** 构造函数，并初始化
    @param [in] path 配置文件路径
    @param [in] name 在配置中查找的日志名称
    */
    LogDogConfig(const std::wstring& path, const std::wstring& name);

public:
    /** 初始化
    @param [in] path 配置文件路径
    */
    void ReLoad(const std::wstring& path, const std::wstring& name);

    /* 分析配置文件是否有错误
    @return 错误码 返回LDC_NO_ERROR表示成功
    */
    inline LogDogConfigErrorCode GetErrorCode()
    {
        return m_errorCode;
    }

private:
    /** 错误码
    */
    LogDogConfigErrorCode m_errorCode = LogDogConfigErrorCode::LDC_NO_ERROR;

    /** 当前数据条目
    */
    LogDogConfigEntry m_configEntry;
};

#endif // !_LOGCONFIG_H_


