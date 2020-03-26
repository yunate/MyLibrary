
#ifndef __SIMPLE_TASK_QUEUE_H_
#define __SIMPLE_TASK_QUEUE_H_

#include "ISimpleTask.h"

#include "noncopyable/noncopyable.h"

#include <mutex>
#include <memory>
#include <queue>
#include <thread>

/** 前置声明，简单事件，只SimpleTaskQueue用
*/
class SimpleEvent;

/** 简单线程任务模型
@note 有点像生产者消费者模型，只是消费者只有一个
*/
class SimpleTaskQueue :
    public NonCopyable
{
public:
    /** 构造函数
    */
    SimpleTaskQueue();

    /** 析构函数
    */
    ~SimpleTaskQueue();

public:
    /** 开始循环
    @return 是否成功
    */
    bool Start();

    /** 停止所有任务
    */
    void StopAll();

    /** 停止当前的任务
    */
    void StopCurrent();

    /** 清空所有任务包括当前的，但不停止循环
    */
    void ClearAll();

    /** 清空所有任务不包括当前的，但不停止循环
    */
    void ClearQueue();

    /** 添加一个任务
    @param [in] task 任务
    */
    void PushTask(const std::shared_ptr<ITask>& task);

    /** 添加一个函数任务
    @param [in] task 任务
    */
    void PushTask(const std::function<void()>& task);

    /** 获得当前队列中的数量，包含当前正在执行的，返回0说明队列空闲
    @return 当前队列中的数量
    */
    size_t GetTaskCount();
public:
    /** 线程回调
    */
    virtual void ThreadCallBack();

private:
    /** 线程
    */
    std::thread* m_pThread;

    /** 互斥量
    */
    std::recursive_mutex m_mutex;

    /** 线程事件
    */
    std::shared_ptr<SimpleEvent> m_spEvent;

    /** 任务队列
    */
    std::queue<std::shared_ptr<ITask> > m_taskQue;

    /** 是否停止了
    */
    bool m_stop;

    /** 当前正在执行的
    */
    std::shared_ptr<ITask> m_currentTask;
};


#endif // __SIMPLE_TASK_QUEUE_H_


