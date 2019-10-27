
#ifndef __ILOG_H_
#define __ILOG_H_

#include "task/ISimpleTask.h"
#include "noncopyable.h"

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
    virtual void DoTask()
    {
        Log();
    }

    /** 日志任务
    */
    virtual void Log() = 0;

    /** 停止任务
    */
    virtual void Stop()
    {
        // 删除
    };
};


#endif //__ILOG_H_
