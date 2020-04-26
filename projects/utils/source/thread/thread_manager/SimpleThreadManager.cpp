
#include "SimpleThreadManager.h"
#include "thread/task/SimpleFunctionTask.h"

SimpleThreadManager::SimpleThreadManager()
{
}

SimpleThreadManager::~SimpleThreadManager()
{
}

uint32_t SimpleThreadManager::GetBlockTaskThreadCount()
{
    return 3;
}

void SimpleThreadManager::StopAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_spFastThreadTaskQueue != nullptr)
    {
        m_spFastThreadTaskQueue->StopAll();
        m_spFastThreadTaskQueue.reset();
    }

    for (auto& it : m_spBlockThreadTaskQueues)
    {
        it->StopAll();
    }

    m_spBlockThreadTaskQueues.clear();

    if (m_spHeartBeatThreadTaskQueue != nullptr)
    {
        m_spHeartBeatThreadTaskQueue->StopAll();
        m_spFastThreadTaskQueue.reset();
    }
}

std::weak_ptr<SimpleTaskThread> SimpleThreadManager::GetFastThreadTaskQueue()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_spFastThreadTaskQueue == nullptr)
    {
        m_spFastThreadTaskQueue.reset(new (std::nothrow) SimpleTaskThread());

        if (m_spFastThreadTaskQueue == nullptr)
        {
            return m_spFastThreadTaskQueue;
        }

        m_spFastThreadTaskQueue->Start();
    }

    return m_spFastThreadTaskQueue;
}

void SimpleThreadManager::PushFastTask(const std::shared_ptr<ITask>& task)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::weak_ptr<SimpleTaskThread> spFastTaskQueue = GetFastThreadTaskQueue();
    auto it = spFastTaskQueue.lock();

    if (it == nullptr)
    {
        return;
    }

    it->PushTask(task);
}

void SimpleThreadManager::PushFastTask(const std::function<bool()>& task)
{
    PushFastTask(std::shared_ptr<ITask>(new (std::nothrow) SimpleFunctionTask(task)));
}

void SimpleThreadManager::PushBlockTask(const std::shared_ptr<ITask>& task)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::shared_ptr<SimpleTaskThread> tmpQue;

    if (m_spBlockThreadTaskQueues.empty())
    {
        tmpQue.reset(new (std::nothrow) SimpleTaskThread());

        if (tmpQue != nullptr)
        {
            m_spBlockThreadTaskQueues.push_back(tmpQue);
            tmpQue->Start();
        }
    }
    else
    {
        tmpQue = m_spBlockThreadTaskQueues[0];

        for (size_t i = 1; i < m_spBlockThreadTaskQueues.size(); ++i)
        {
            if (tmpQue->GetTaskCount() > m_spBlockThreadTaskQueues[i]->GetTaskCount())
            {
                tmpQue = m_spBlockThreadTaskQueues[i];
            }
        }

        if (tmpQue->GetTaskCount() != 0 && m_spBlockThreadTaskQueues.size() < GetBlockTaskThreadCount())
        {
            SimpleTaskThread* pTaskThreadQueue = new (std::nothrow) SimpleTaskThread();

            if (pTaskThreadQueue != nullptr)
            {
                tmpQue.reset(pTaskThreadQueue);
                m_spBlockThreadTaskQueues.push_back(tmpQue);
                tmpQue->Start();
            }
        }
    }

    if (tmpQue != nullptr)
    {
        tmpQue->PushTask(task);
    }
}

void SimpleThreadManager::PushBlockTask(const std::function<bool()>& task)
{
    PushBlockTask(std::shared_ptr<ITask>(new (std::nothrow) SimpleFunctionTask(task)));
}

void SimpleThreadManager::PushHeartBeatTask(const SPHeartBeatTask& task)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_spHeartBeatThreadTaskQueue == nullptr)
    {
        m_spHeartBeatThreadTaskQueue.reset(new (std::nothrow) HeartBeatTaskThread());

        if (m_spHeartBeatThreadTaskQueue == nullptr)
        {
            return;
        }

        m_spHeartBeatThreadTaskQueue->Start();
    }

    m_spHeartBeatThreadTaskQueue->PushTask(task);
}

void SimpleThreadManager::PushHeartBeatTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times)
{
    PushHeartBeatTask(SPHeartBeatTask(new (std::nothrow) HeartBeatFunTask(task, timeOut, times)));
}

