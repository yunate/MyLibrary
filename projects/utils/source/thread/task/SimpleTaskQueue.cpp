
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
        m_event.SetEvent();
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
    m_mutex.lock();
    ClearAll();
    m_stop = true;
    m_mutex.unlock();
}

void SimpleTaskQueue::StopCurrent()
{
    m_mutex.lock();

    if (m_currentTask != nullptr)
    {
        m_currentTask->Stop();
    }

    m_mutex.unlock();
}

void SimpleTaskQueue::ClearAll()
{
    m_mutex.lock();
    StopCurrent();
    ClearQueue();
    m_mutex.unlock();
}

void SimpleTaskQueue::ClearQueue()
{
    m_mutex.lock();
    m_taskQue.swap(std::queue<std::shared_ptr<ITask> >());
    m_mutex.unlock();
}

void SimpleTaskQueue::PushTask(const std::shared_ptr<ITask>& task)
{
    m_mutex.lock();
    m_taskQue.push(task);
    m_event.SetEvent();
    m_mutex.unlock();
}

void SimpleTaskQueue::PushTask(const std::function<void()>& task)
{
    PushTask(std::shared_ptr<ITask>(new SimpleFunTask(task)));
}

void SimpleTaskQueue::ThreadCallBack()
{
    while (true)
    {
        m_mutex.lock();
        bool stop = m_stop;
        m_mutex.unlock();

        if (stop)
        {
            break;
        }

        m_event.Wait();

        while (true)
        {
            m_mutex.lock();
            bool isQueEmpty = m_taskQue.empty();
            m_mutex.unlock();

            if (isQueEmpty)
            {
                break;
            }

            m_mutex.lock();
            m_currentTask = m_taskQue.front();
            m_taskQue.pop();
            m_mutex.unlock();
            m_currentTask->DoTask();
            m_mutex.lock();
            m_currentTask = nullptr;
            m_mutex.unlock();
        }
    }
}
