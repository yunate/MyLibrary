
#include "SimpleTaskQueue.h"

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

void SimpleTaskQueue::Start()
{
    m_pThread = new (std::nothrow) std::thread(&SimpleTaskQueue::ThreadCallBack, this);
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
    m_taskQue.swap(std::queue<std::shared_ptr<ITask> >());
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
