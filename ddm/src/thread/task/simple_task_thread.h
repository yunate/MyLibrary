
#ifndef simple_task_thread_h_
#define simple_task_thread_h_ 1

#include "base/g_def.h"
#include "base/nocopyable.hpp"
#include "i_ddtask.h"

#include <mutex>
#include <functional>
#include <memory>
#include <queue>
#include <thread>

BEG_NSP_DDM
/** 前置声明，简单事件，只simple_task_thread用
*/
class simple_event;

/** 简单线程任务模型
@note 有点像生产者消费者模型，只是消费者只有一个
*/
class simple_task_thread :
    public nocopyable
{
public:
    /** 构造函数
    */
    simple_task_thread();

    /** 析构函数
    */
    ~simple_task_thread();

public:
    /** 开始循环
    @return 是否成功
    */
    bool start();

    /** 停止所有任务
    */
    void stop_all();

    /** 停止当前的任务
    */
    void stop_current();

    /** 清空所有任务包括当前的，但不停止循环
    */
    void clear_all();

    /** 清空所有任务不包括当前的，但不停止循环
    */
    void clear_queue();

    /** 添加一个任务
    @param [in] task 任务
    */
    void push_task(const std::shared_ptr<i_ddtask>& task);

    /** 添加一个函数任务
    @param [in] task 任务
    */
    void push_task(const std::function<void()>& task);

    /** 获得当前队列中的数量，包含当前正在执行的，返回0说明队列空闲
    @return 当前队列中的数量
    */
    size_t get_task_count();

public:
    /** 线程回调
    */
    virtual void thread_callback();

private:
    /** 线程
    */
    std::thread* m_pThread;

    /** 互斥量
    */
    std::recursive_mutex m_mutex;

    /** 线程事件
    */
    std::shared_ptr<simple_event> m_spEvent;

    /** 任务队列
    */
    std::queue<std::shared_ptr<i_ddtask> > m_taskQue;

    /** 是否停止了
    */
    bool m_stop;

    /** 当前正在执行的
    */
    std::shared_ptr<i_ddtask> m_currentTask;
};

END_NSP_DDM
#endif // simple_task_thread_h_
