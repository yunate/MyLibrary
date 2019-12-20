
#include "SimpleTaskQueue.h"

/** 简单事件
*/
class SimpleEvent :
    public NonCopyable
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

    /** 是否有信号，只是记录是否有信号，但是不记录信号次数
    @note 主要是为了先调用SetEvent()，然后调用wait的情况。考虑在Wait()前加上::Sleep(1000);
    */
    bool m_hasSignal = false;
};

SimpleTaskQueue::SimpleTaskQueue() :
    m_stop(false),
    m_pThread(nullptr)
{
}

SimpleTaskQueue::~SimpleTaskQueue()
{
    if (m_pThread != nullptr)
    {
        StopAll();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool SimpleTaskQueue::Start()
{
    m_pThread = new (std::nothrow) std::thread(&SimpleTaskQueue::ThreadCallBack, this);
    return m_pThread != NULL;
}

void SimpleTaskQueue::StopAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    ClearAll();
    m_stop = true;
    m_event.SetEvent();
}

void SimpleTaskQueue::StopCurrent()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr)
    {
        m_currentTask->Stop();
    }
}

void SimpleTaskQueue::ClearAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    StopCurrent();
    ClearQueue();
}

void SimpleTaskQueue::ClearQueue()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::queue<std::shared_ptr<ITask> > tmp = std::queue<std::shared_ptr<ITask> >();
    m_taskQue.swap(tmp);
}

void SimpleTaskQueue::PushTask(const std::shared_ptr<ITask>& task)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_taskQue.push(task);
    m_event.SetEvent();
}

void SimpleTaskQueue::PushTask(const std::function<void()>& task)
{
    PushTask(std::shared_ptr<ITask>(new SimpleFunTask(task)));
}

void SimpleTaskQueue::ThreadCallBack()
{
    while (true)
    {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop)
            {
                break;
            }
        }

        m_event.Wait();

        // 将队列里的全部执行掉
        while (true)
        {
            // 取出队首
            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);

                if (m_taskQue.empty())
                {
                    break;
                }

                m_currentTask = m_taskQue.front();
                m_taskQue.pop();

                if (m_currentTask == nullptr)
                {
                    continue;
                }
            }

            // 执行任务
            m_currentTask->DoTask();

            // 准备销毁
            std::shared_ptr<ITask> tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }
    }
}
