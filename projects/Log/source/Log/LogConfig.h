
#ifndef _LOGCONFIG_H_
#define _LOGCONFIG_H_

#include <string>


/** 日志的配置文件
*/
class LogConfig
{
public:
    /** 构造函数
    */
    LogConfig();

    /** 构造函数，并初始化
    @param [in] path 配置文件路径
    */
    LogConfig(const std::wstring& path);

    LogConfig(const LogConfig&) = delete;
    LogConfig& operator=(const LogConfig&) = delete;

public:
    /** 初始化
    @param [in] path 配置文件路径
    */
    void Init(const std::wstring& path);

private:
    /** 日志名称，如果需要写文件的话，它是文件的上一层目录名称
    */
    std::wstring m_name;

    /** 日志等级
    */
    int m_level;


};

#endif // !_LOGCONFIG_H_


