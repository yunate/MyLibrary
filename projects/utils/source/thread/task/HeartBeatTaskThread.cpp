
#include "HeartBeatTaskThread.h"

/** 心跳任务的一层封装
*/
struct HeartBeatTaskWraper
{
    /** 构造函数
    @param [in] spHeartBeatTask 任务，这个参数用户应该保证不为空，该文件内不会再去判断空
    */
    HeartBeatTaskWraper(const SPHeartBeatTask& spHeartBeatTask) :
        m_spHeartBeatTask(spHeartBeatTask)
    {
        auto dur = std::chrono::high_resolution_clock::now().time_since_epoch();
        m_preExecuteTime = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    }

    /** 是否可以执行了？返回true时候会更新时间戳
    @return 是否可以执行
    */
    bool CanExecute()
    {
        auto dur = std::chrono::high_resolution_clock::now().time_since_epoch();
        long long nowTime = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

        if (nowTime - m_preExecuteTime >= m_spHeartBeatTask->GetTimeOut())
        {
            m_preExecuteTime = nowTime;
            return true;
        }

        return false;
    }

    /** 任务的智能指针
    */
    SPHeartBeatTask m_spHeartBeatTask;

    /** 上次执行时间，如果一次都没有执行过为创建时间
    */
    long long m_preExecuteTime;
};

//////////////////////////////////////////////////////////////////////////

HeartBeatTaskThread::HeartBeatTaskThread():
    m_pThread(nullptr),
    m_stop(false)
{
}

HeartBeatTaskThread::~HeartBeatTaskThread()
{
    if (m_pThread != nullptr)
    {
        StopAll();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool HeartBeatTaskThread::Start()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_pThread != nullptr)
    {
        return true;
    }

    m_pThread = new (std::nothrow) std::thread(&HeartBeatTaskThread::ThreadCallBack, this);
    return (m_pThread != nullptr);
}

void HeartBeatTaskThread::StopAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_stop)
    {
        ClearAll();
        m_stop = true;
    }
}

void HeartBeatTaskThread::StopCurrent()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr)
    {
        m_currentTask->m_spHeartBeatTask->Stop();
    }
}

void HeartBeatTaskThread::ClearAll()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    StopCurrent();
    ClearQueue();
}

void HeartBeatTaskThread::ClearQueue()
{
    std::list<SPHeartBeatTaskWraper > tmp = std::list<SPHeartBeatTaskWraper >();

    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        m_taskList.swap(tmp);
    }
}

void HeartBeatTaskThread::PushTask(const SPHeartBeatTask& task)
{
    if (task == nullptr || m_stop)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    SPHeartBeatTaskWraper tmp(new(std::nothrow) HeartBeatTaskWraper(task));

    if (tmp != nullptr)
    {
        m_taskList.push_back(tmp);
    }
}

void HeartBeatTaskThread::PushTask(const std::function<bool()>& task, uint32_t timeOut, int32_t times)
{
    PushTask(SPHeartBeatTask(new (std::nothrow) HeartBeatFunTask(task, timeOut, times)));
}

size_t HeartBeatTaskThread::GetTaskCount()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_taskList.size() + (m_currentTask != nullptr ? 1 : 0);
}

void HeartBeatTaskThread::ThreadCallBack()
{
    std::list<SPHeartBeatTaskWraper > tmpList;

    while (true)
    {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop)
            {
                break;
            }

            for (auto it : tmpList)
            {
                m_taskList.push_back(it);
            }

            tmpList.clear();

            m_taskList.swap(tmpList);
        }

        // 将队列里的全部执行掉
        auto it = tmpList.begin();
        while (it != tmpList.end())
        {
            auto tmpIt = it++;
            if (tmpList.empty() || m_stop)
            {
                break;
            }

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = *tmpIt;
            }

            if (m_currentTask == nullptr)
            {
                tmpList.erase(tmpIt);
                continue;
            }

            // 执行任务
            if (m_currentTask->CanExecute())
            {
                m_currentTask->m_spHeartBeatTask->DoTask();

                if (m_currentTask->m_spHeartBeatTask->RemoveAfterExcute())
                {
                    tmpList.erase(tmpIt);
                }
            }

            // 这个主要是为了防止析构函数有长时间执行占用mutex
            SPHeartBeatTaskWraper tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
