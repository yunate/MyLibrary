
#ifndef __ILOGDOG_H_
#define __ILOGDOG_H_

#include "LogDogDef.h"

#include "task/ISimpleTask.h"

class ILog : public ITask
{
public:
    ILog() :
        m_configEntry(NULL)
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

private:
    /** 日志中的配置信息
    */
    LogDogConfigEntry* m_configEntry;
};


#endif //__ILOGDOG_H_
