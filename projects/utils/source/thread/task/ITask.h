
#ifndef __ITASK_H_
#define __ITASK_H_

class ITask
{
public:
    virtual ~ITask()
    {

    }

    /** 执行任务
    */
    virtual void DoTask() = 0;

    /** 停止任务
    */
    virtual void Stop() = 0;
};

#endif // __ITASK_H_

