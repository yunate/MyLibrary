
/****************************************************************************/
/* 提供一个使用的方法，用户可以根据需求重新改写该文件                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "LogImpl.h"
#include "LogDogConfig.h"

#include "singleton.h"
#include "task/SimpleTaskQueue.h"
#include <functional>
#include <unordered_map>
#include <thread>

/** className 类要提供一个静态的std::shared_ptr<ILog> Create(...)函数,并且这个函数不能有重载,LOG调用的时候的参数要严格相同
不能有隐式强制转换发生，比如char* 转换为 std::string
*/
#define LOG_BIND(logType, className)\
{Singleton<LogDog>::GetInstance().Bind((int)logType, (void*)className::Create);}

/** 日志对象管理类，用户可以根据需求重新改写
*/
class LogDog :
    public NonCopyable
{
protected:
    LogDog()
    {
    }

public:
    /** 初始化
    @param [in] path 配置文件路径
    @param [in] name 配置文件中对应的secsion
    @return 日志线程是否创建成功
    */
    inline bool Init(const DogString& path, const DogString& name)
    {
        // 初始化任务队列
        m_spLogQue.reset(new(std::nothrow) SimpleTaskQueue());

        // 初始化配置文件
        m_spConfig.reset(new(std::nothrow)LogDogConfig(path, name));

        return m_spLogQue != NULL;
    }

    inline void Push(const std::shared_ptr<ILog>& log)
    {
        if (m_spLogQue != NULL)
        {
            m_spLogQue->PushTask(log);
        }
    }

    inline void Bind(int type, void* creator)
    {
        if (creator != NULL)
        {
            m_logCreators[type] = creator;
        }
    }

    inline void* GetCreator(int type)
    {
        auto it = m_logCreators.find(type);

        if (it != m_logCreators.end())
        {
            return (it->second);
        }

        return NULL;
    }

    /** 释放资源，其实这个函数并不是很重要，因为单例在程序退出的时候会自己释放的，
    只是为了和init想对应
    */
    inline void UnInit()
    {
        m_spLogQue.swap(std::shared_ptr<SimpleTaskQueue>());
    }

private:
    /** 配置文件
    */
    std::shared_ptr <LogDogConfig> m_spConfig;

    /** 日志任务队列
    */
    std::shared_ptr<SimpleTaskQueue> m_spLogQue;

    /** 日志实体创造者
    */
    std::unordered_map<int, void*> m_logCreators;
};


/** 初始化
@param [in] path 配置文件路径
@param [in] name 配置文件中对应的secsion
*/
void LOG_INIT(const DogString& path, const DogString& name)
{
    if (!Singleton<LogDog>::GetInstance().Init(path, name))
    {
        return;
    }

    LOG_BIND(LOGTYPE::LOGTYPE_SIMPLE_LOG, SimpleLog);

    // 这个方法是一般的加入日志的方法，当然我们提供简便的LOG函数
    {
        // 将日志线程的优先级降低
        std::shared_ptr<ILog> log(new (std::nothrow)DecreasePriority());

        if (log != NULL)
        {
            Singleton<LogDog>::GetInstance().Push(log);
        }
    }
}

/** 反初始化
*/
void LOG_UNINIT()
{
    Singleton<LogDog>::GetInstance().UnInit();
}

/** 提供简便的LOG函数
@param [in] type 参考LOGTYPE
@param [in] __Args Create函数的参数，要和声明严格相同，不能有隐式强制转换发生，比如char* 转换为 std::string
*/
template <class ..._Types>
void LOG(int type, _Types... _Args)
{
    void* creator = Singleton<LogDog>::GetInstance().GetCreator(type);

    if (creator == NULL)
    {
        return;
    }

    std::shared_ptr<ILog> log = (((std::shared_ptr<ILog>(*)(_Types...))creator)(_Args...));

    if (log != NULL)
    {
        Singleton<LogDog>::GetInstance().Push(log);
    }
}

#endif

