
#ifndef __HEARTBEAD_TASK_THREAD_
#define __HEARTBEAD_TASK_THREAD_ 1

#include "IHeartBeatTask.h"

#include "noncopyable/noncopyable.h"

#include <list>
#include <thread>
#include <mutex>

struct HeartBeatTaskWraper;
using SPHeartBeatTaskWraper = std::shared_ptr<HeartBeatTaskWraper>;

/** 心跳线程任务模型
*/
class HeartBeatTaskThread :
    public NonCopyable
{
public:
    /** 构造函数
    */
    HeartBeatTaskThread();

    /** 析构函数
    */
    ~HeartBeatTaskThread();

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
    void PushTask(const SPHeartBeatTask& task);

    /** 添加一个函数任务
    @param [in] task 任务
    @param [in] timeOut 时间间隔
    @param [in] times 执行次数，为-1代表执行无数次，默认为-1
    */
    void PushTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times = -1);

    /** 获得当前队列中的数量，包含当前正在执行的
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

    /** 任务队列
    */
    std::list<SPHeartBeatTaskWraper > m_taskList;

    /** 是否停止了
    */
    bool m_stop;

    /** 当前正在执行的
    */
    SPHeartBeatTaskWraper m_currentTask;
};

#endif // __HEARTBEAD_TASK_THREAD_
