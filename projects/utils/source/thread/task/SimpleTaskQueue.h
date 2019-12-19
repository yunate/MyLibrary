
#ifndef __SIMPLE_TASK_QUEUE_H_
#define __SIMPLE_TASK_QUEUE_H_

#include "ISimpleTask.h"

#include <mutex>
#include <memory>
#include <queue>
#include <thread>

class SimpleEvent
{
public:
    /** 等待一个信号
    */
    void Wait()
    {
        std::unique_lock<std::mutex> lck(m_mutex);

        if (!m_hasSignal)
        {
            // 不会死锁，考虑：
            // 1、m_mutex.unlock();
            // 2、wait()
            // 3、m_mutex.lock();
            // wait(lck) 相当于将1、2两步放到一个cpu周期内
            m_con.wait(lck);
        }

        m_hasSignal = false;
    }

    /** 设置一个信号
    */
    void SetEvent()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_hasSignal = true;
        m_con.notify_all();
    }

private:
    /** 互斥量
    */
    std::mutex m_mutex;

    /** condition_variable
    */
    std::condition_variable m_con;

    /** 是否有信号
    @note 主要是为了先调用SetEvent()，然后调用wait的情况。考虑在Wait()前加上::Sleep(1000);
    */
    bool m_hasSignal = false;
};

/** 简单线程任务模型
*/
class SimpleTaskQueue
{
public:
    /** 构造函数
    */
    SimpleTaskQueue();

    /** 析构函数
    */
    ~SimpleTaskQueue();

    // 不允许拷贝
    SimpleTaskQueue(const SimpleTaskQueue&) = delete;
    SimpleTaskQueue(SimpleTaskQueue&&) = delete;
    SimpleTaskQueue& operator=(const SimpleTaskQueue&) = delete;

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
    SimpleEvent m_event;

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


