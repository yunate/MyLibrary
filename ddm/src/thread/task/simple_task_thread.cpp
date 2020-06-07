
#include "simple_task_thread.h"
#include "thread/mutex/simple_event.h"
#include "simple_function_task.h"

BEG_NSP_DDM
simple_task_thread::simple_task_thread() :
    m_stop(false),
    m_pThread(nullptr)
{}

simple_task_thread::~simple_task_thread()
{
    if (m_pThread != nullptr) {
        stop_all();
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
}

bool simple_task_thread::start()
{
    m_spEvent.reset(new(std::nothrow) simple_event());
    m_pThread = new (std::nothrow) std::thread(&simple_task_thread::thread_callback, this);
    return (m_pThread != nullptr) & (m_spEvent != nullptr);
}

void simple_task_thread::stop_all()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    clear_all();
    m_stop = true;
    m_spEvent->set_event();
}

void simple_task_thread::stop_current()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_currentTask != nullptr) {
        m_currentTask->stop();
    }
}

void simple_task_thread::clear_all()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    stop_current();
    clear_queue();
}

void simple_task_thread::clear_queue()
{
    std::queue<std::shared_ptr<i_ddtask> > tmp = std::queue<std::shared_ptr<i_ddtask> >();
    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        m_taskQue.swap(tmp);
    }
}

void simple_task_thread::push_task(const std::shared_ptr<i_ddtask>& task)
{
    if (m_stop) {
        return;
    }

    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_taskQue.push(task);
    m_spEvent->set_event();
}

void simple_task_thread::push_task(const std::function<void()>& task)
{
    push_task(std::shared_ptr<i_ddtask>(new simple_function_task(task)));
}

size_t simple_task_thread::get_task_count()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_taskQue.size() + (m_currentTask != nullptr ? 1 : 0);
}

void simple_task_thread::thread_callback()
{
    while (true)
    {
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);

            if (m_stop) {
                break;
            }
        }

        m_spEvent->Wait();

        // 将队列里的全部执行掉
        while (true) {
            // 取出队首
            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);

                if (m_taskQue.empty()) {
                    break;
                }

                m_currentTask = m_taskQue.front();
                m_taskQue.pop();

                if (m_currentTask == nullptr) {
                    continue;
                }
            }

            // 执行任务
            m_currentTask->do_task();

            // 准备销毁
            std::shared_ptr<i_ddtask> tmp = m_currentTask;

            {
                std::lock_guard<std::recursive_mutex> lock(m_mutex);
                m_currentTask = nullptr;
            }
        }
    }
}

END_NSP_DDM

