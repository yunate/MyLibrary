
#include "heartbeat_task_thread.h"

BEG_NSP_DDM

/** 心跳任务的一层封装
*/
struct heartbeat_task_wraper
{
    /** 构造函数
    @param [in] spHeartBeatTask 任务，这个参数用户应该保证不为空，该文件内不会再去判断空
    */
    heartbeat_task_wraper(const sp_heartbeat_task& spHeartBeatTask) :
        m_spHeartBeatTask(spHeartBeatTask) {
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

        if (nowTime - m_preExecuteTime >= m_spHeartBeatTask->get_timeout()) {
            m_preExecuteTime = nowTime;
            return true;
        }

        return false;
    }

    /** 任务的智能指针
    */
    sp_heartbeat_task m_spHeartBeatTask;

    /** 上次执行时间，如果一次都没有执行过为创建时间
    */
    long long m_preExecuteTime;
};

//////////////////////////////////////////////////////////////////////////

heartbeat_task_thread::heartbeat_task_thread():
    m_pThread(nullptr),
    m_stop(false)
{}

heartbeat_task_thread::~heartbeat_task_thread()
{
    if (m_pThread != nullptr) {
        stop_all();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool heartbeat_task_thread::start()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_pThread != nullptr) {
        return true;
    }

    m_pThread = new (std::nothrow) std::thread(&heartbeat_task_thread::thread_callback, this);
    return (m_pThread != nullptr);
}

void heartbeat_task_thread::stop_all()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_stop) {
        clear_all();
        m_stop = true;
    }
}

void heartbeat_task_thread::stop_current()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr) {
        m_currentTask->m_spHeartBeatTask->stop();
    }
}

void heartbeat_task_thread::clear_all()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    stop_current();
    clear_queue();
}

void heartbeat_task_thread::clear_queue()
{
    std::list<sp_heartbeat_taskWraper > tmp = std::list<sp_heartbeat_taskWraper >();

    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        m_taskList.swap(tmp);
    }
}

void heartbeat_task_thread::push_task(const sp_heartbeat_task& task)
{
    if (task == nullptr || m_stop) {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    sp_heartbeat_taskWraper tmp(new(std::nothrow) heartbeat_task_wraper(task));

    if (tmp != nullptr) {
        m_taskList.push_back(tmp);
    }
}

void heartbeat_task_thread::push_task(const std::function<bool()>& task, uint32_t timeOut, int32_t times)
{
    push_task(sp_heartbeat_task(new (std::nothrow) heartbeat_fun_task(task, timeOut, times)));
}

size_t heartbeat_task_thread::get_task_count()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_taskList.size() + (m_currentTask != nullptr ? 1 : 0);
}

void heartbeat_task_thread::thread_callback()
{
    std::list<sp_heartbeat_taskWraper > tmpList;

    while (true) {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop) {
                break;
            }

            for (auto it : tmpList) {
                m_taskList.push_back(it);
            }

            tmpList.clear();
            m_taskList.swap(tmpList);
        }

        // 将队列里的全部执行掉
        auto it = tmpList.begin();
        while (it != tmpList.end() && !m_stop) {
            auto tmpIt = it++;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = *tmpIt;
            }

            if (m_currentTask == nullptr) {
                tmpList.erase(tmpIt);
                continue;
            }

            // 执行任务
            if (m_currentTask->CanExecute()) {
                m_currentTask->m_spHeartBeatTask->do_task();

                if (m_currentTask->m_spHeartBeatTask->remove_after_excute()) {
                    tmpList.erase(tmpIt);
                }
            }

            // 这个主要是为了防止析构函数有长时间执行占用mutex
            sp_heartbeat_taskWraper tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

END_NSP_DDM