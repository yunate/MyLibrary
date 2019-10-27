
#ifndef __ILOGDOG_H_
#define __ILOGDOG_H_

#include "LogDogDef.h"
#include "task/ISimpleTask.h"
#include "noncopyable.h"

#include <assert.h>
#include <functional>
#include <memory>

class ILogDogConfig :
    public NonCopyable

{
public:
    /** 析构函数
    */
    virtual ~ILogDogConfig(){}

    /** 初始化
    @param [in] path 配置文件路径
    */
    virtual void ReLoad(const std::wstring& path, const std::wstring& name) = 0;

    /* 分析配置文件是否有错误
    @return 错误码 返回LDC_NO_ERROR表示成功
    */
    virtual LogDogConfigErrorCode GetErrorCode() = 0;

    /** 获得日志配置
    @return 日志配置
    */
    virtual LogDogConfigEntry& GetLogDogConfigEntry() = 0;

    /** 创建
    @param [in] path 配置文件路径
    @param [in] name 在配置中查找的日志名称
    */
    static std::shared_ptr<ILogDogConfig> Create(const std::wstring & path, const std::wstring & name);
};

/** 日志实体
*/
class ILog :
    public ITask,
    public NonCopyable
{
public:
    ILog()
    {
    }

    /** 执行任务
    */
    virtual void DoTask() = 0;

    /** 停止任务
    */
    virtual void Stop()
    {
        // 删除
    };

    inline void SetLogConfig(const std::shared_ptr <ILogDogConfig>& logConfig)
    {
        m_spConfig = logConfig;
    }

private:
    /** 日志中的配置信息
    */
    std::shared_ptr <ILogDogConfig> m_spConfig;
};

/** 日志记录执行者
*/
class ILogDog :
    public NonCopyable
{
public:
    /** 析构函数
    */
    virtual ~ILogDog(){}

    /** 压入日志
    @param [in] log 日志实体
    */
    virtual void Push(std::shared_ptr<ILog>& log) = 0;

    /** 创建具体日志对象
    @return 日志对象
    */
    static std::shared_ptr<ILogDog> Create(const DogString& path, const DogString& name);
};


#endif //__ILOGDOG_H_
