
#ifndef __ISIMPLEFUNCTIONTASK_H_
#define __ISIMPLEFUNCTIONTASK_H_

#include "ITask.h"
#include <functional>

class SimpleFunctionTask :
    public ITask
{
public:
    SimpleFunctionTask(const std::function<void()>& callback) :
        m_callback(callback)
    {

    }

    virtual ~SimpleFunctionTask()
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

#endif // __ISIMPLEFUNCTIONTASK_H_

