
#ifndef __SIMPLE_THREAD_MANAGER_H_
#define __SIMPLE_THREAD_MANAGER_H_ 1

#include "thread/task/SimpleTaskThread.h"
#include "thread/task/HeartBeatTaskThread.h"

/** 简单线程管理类
@note !!!!!!!!!!! 析构函数/uninit 中不应该有东西再线程中执行
*/
class SimpleThreadManager
{
public:
    /** 构造函数
    */
    SimpleThreadManager();

    /** 析构函数
    */
    virtual ~SimpleThreadManager();

public:
    /** 获得阻塞线程数量，如果需要更多数量，继承改类并重载该函数
    @return 返回阻塞任务队列数量
    */
    virtual uint32_t GetBlockTaskThreadCount();

    /** 停止所有，子类重载该函数时候应该显示再次调用该函数
    */
    virtual void StopAll();

public:
    /** 添加一个快速任务
    @param [in] task 任务
    */
    void PushFastTask(const std::shared_ptr<ITask>& task);

    /** 添加一个快速函数任务
    @param [in] task 任务
    */
    void PushFastTask(const std::function<bool()>& task);

    /** 获得快速队列，如果还没初始化的话，该函数会自动初始化
    @return 快速队列
    */
    std::weak_ptr <SimpleTaskThread> GetFastThreadTaskQueue();

    /** 添加一个阻塞任务
    @param [in] task 任务
    */
    void PushBlockTask(const std::shared_ptr<ITask>& task);

    /** 添加一个阻塞函数任务
    @param [in] task 任务
    */
    void PushBlockTask(const std::function<bool()>& task);

    /** 添加一个心跳务
    @param [in] task 任务
    */
    void PushHeartBeatTask(const SPHeartBeatTask& task);

    /** 添加一个心跳函数任务
    @param [in] task 任务
    @param [in] timeOut 时间间隔
    @param [in] times 执行次数，为-1代表执行无数次，默认为-1
    */
    void PushHeartBeatTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times = -1);

protected:
    /** 快速任务线程一条
    */
    std::shared_ptr<SimpleTaskThread> m_spFastThreadTaskQueue;

    /** 阻塞任务线程数组
    @note TODO: 暂时用数组存储多个任务队列，以后可以考虑将内部的que封装成线程安全的，然后添加支持多个线程的队列
    */
    std::vector<std::shared_ptr<SimpleTaskThread>> m_spBlockThreadTaskQueues;

    /** 心跳任务一条
    */
    std::shared_ptr<HeartBeatTaskThread> m_spHeartBeatThreadTaskQueue;

    /** 互斥量
    */
    std::recursive_mutex m_mutex;
};

#endif // __SIMPLE_THREAD_MANAGER_H_
