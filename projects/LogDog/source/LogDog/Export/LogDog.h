
/****************************************************************************/
/* 提供一个使用的方法，用户可以根据需求重新改写该文件                               */
/****************************************************************************/

#ifndef _LOGDOG_H__
#define _LOGDOG_H__

#include "ILogDog.h"
#include "LogImpl.h"
#include "singleton.h"
#include <unordered_map>
#include <functional>

/** className 类要提供一个静态的std::shared_ptr<ILog> Create(...)函数,并且这个函数不能有重载,LOG调用的时候的参数要严格相同
不能有隐式强制转换发生，比如char* 转换为 std::string
*/
#define LOG_BIND(logType, className)\
{Singleton<LogDogManager>::GetInstance().Bind((int)logType, (void*)className::Create);}

/** 日志对象管理类，用户可以根据需求重新改写
*/
class LogDogManager :
    public NonCopyable
{
protected:
    LogDogManager()
    {
        m_logDog = ILogDog::Create(_DogT(""), _DogT("test"));
    }

    LogDogManager(const LogDogManager&) = delete;
    LogDogManager& operator=(const LogDogManager&) = delete;

public:
    inline std::shared_ptr<ILogDog>& GetLodDog()
    {
        return m_logDog;
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

private:
    /** 本类只创建一个日志对象，如果需要的话改为map以维护多个
    */
    std::shared_ptr<ILogDog> m_logDog;

    /** 日志实体创造者
    */
    std::unordered_map<int, void*> m_logCreators;
};

template <class ..._Types>
void LOG(int type, _Types... _Args)
{
    void* creator = Singleton<LogDogManager>::GetInstance().GetCreator(type);

    if (creator == NULL)
    {
        return;
    }

    std::shared_ptr<ILog> log = (((std::shared_ptr<ILog>(*)(_Types...))creator)(_Args...));

    if (log != NULL)
    {
        Singleton<LogDogManager>::GetInstance().GetLodDog()->Push(log);
    }
}

#endif

