
#ifndef heartbeat_task_thread_h_
#define heartbeat_task_thread_h_ 1

#include "i_heartbeat_task.h"
#include "base/g_def.h"
#include "base/nocopyable.hpp"

#include <list>
#include <thread>
#include <mutex>
BEG_NSP_DDM
struct heartbeat_task_wraper;
using sp_heartbeat_taskWraper = std::shared_ptr<heartbeat_task_wraper>;

/** 心跳线程任务模型
*/
class heartbeat_task_thread :
    public nocopyable
{
public:
    /** 构造函数
    */
    heartbeat_task_thread();

    /** 析构函数
    */
    ~heartbeat_task_thread();

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
    void push_task(const sp_heartbeat_task& task);

    /** 添加一个函数任务
    @param [in] task 任务
    @param [in] timeOut 时间间隔
    @param [in] times 执行次数，为-1代表执行无数次，默认为-1
    */
    void push_task(const std::function<bool()>& task, uint32_t timeOut, int32_t times = -1);

    /** 获得当前队列中的数量，包含当前正在执行的
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

    /** 任务队列
    */
    std::list<sp_heartbeat_taskWraper > m_taskList;

    /** 是否停止了
    */
    bool m_stop;

    /** 当前正在执行的
    */
    sp_heartbeat_taskWraper m_currentTask;
};

END_NSP_DDM
#endif // heartbeat_task_thread_h_
