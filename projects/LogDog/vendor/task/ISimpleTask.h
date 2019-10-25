
#ifndef __ISIMPLETASK_H_
#define __ISIMPLETASK_H_

#include "ITask.h"
#include <functional>

class ISimpleTask :
    public ITask
{
public:
    ISimpleTask(const std::function<void(int)>& callback) :
        m_callback(callback)
    {

    }

    virtual ~ISimpleTask()
    {

    }

    /** 执行任务
    */
    virtual void DoTask() = 0;

    /** 停止任务
    */
    virtual void Stop() = 0;

    void CallBack(int val)
    {
        if (m_callback != NULL)
        {
            m_callback(val);
        }
    }

protected:
    /** 回调
    */
    std::function<void(int)> m_callback;
};

class SimpleFunTask :
    public ITask
{
public:
    SimpleFunTask(const std::function<void()>& callback) :
        m_callback(callback)
    {

    }

    virtual ~SimpleFunTask()
    {

    }

    /** 执行任务
    */
    virtual void DoTask()
    {
        if (m_callback != nullptr)
        {
            m_callback();
        }
    }

    /** 停止任务
    */
    virtual void Stop() {}

private:
    /** 回调
    */
    std::function<void()> m_callback;
};

#endif // __ITASK_H_

