
#ifndef __IHEARTBEATTASK_h_
#define __IHEARTBEATTASK_h_ 1

#include "ITask.h"

#include <functional>
#include <memory>

/** 心跳任务，为心跳任务队列准备
*/
class IHeartBeatTask :
    public ITask
{
public:
    /** 构造函数
    */
    IHeartBeatTask()
    {
    }

    /** 析构函数
    */
    virtual ~IHeartBeatTask()
    {
    }

    /** 任务执行完成后是否移除该任务
    @return 为true时候，执行完该任务将从任务队列中移除
    */
    virtual bool RemoveAfterExcute()
    {
        return false;
    };

    /** 获得心跳间隔，单位ms
    @return 心跳间隔
    */
    virtual uint32_t GetTimeOut() = 0;
};

/** 任务智能指针
*/
using SPHeartBeatTask = std::shared_ptr<IHeartBeatTask>;

/** 回调任务，特别为lambda准备，考虑改为模板
*/
class HeartBeatFunTask :
    public IHeartBeatTask
{
public:
    /** 构造函数
    @param [callback] 可执行回调
    @param [in] timeOut 时间间隔
    @param [in] times 执行次数，为-1代表执行无数次，默认为-1
    */
    HeartBeatFunTask(const std::function<bool()>& callback, uint32_t timeOut, int32_t times = -1) :
        m_callback(callback),
        m_timeOut(timeOut),
        m_times(times),
        m_curTimes(0)
    {
    }

    /** 析构函数
    */
    virtual ~HeartBeatFunTask()
    {
    }

    /** 执行任务
    @return 是否成功
    */
    virtual void DoTask()
    {
        if (m_callback != nullptr)
        {
            if (m_times != -1)
            {
                ++m_curTimes;
            }

            m_callback();
        }
    }

    /** 停止任务
    */
    virtual void Stop()
    {
        //
    }

    /** 任务执行完成后是否移除该任务
    @return 为true时候，执行完该任务将从任务队列中移除
    */
    virtual bool RemoveAfterExcute()
    {
        if (m_callback == nullptr)
        {
            return true;
        }

        if (m_times == -1 || m_curTimes != m_times)
        {
            return false;
        }

        return true;
    };

    /** 获得心跳间隔，单位ms
    @return 心跳间隔
    */
    virtual uint32_t GetTimeOut()
    {
        return m_timeOut;
    }

private:
    /** 回调
    */
    std::function<bool()> m_callback;

    /** 执行间隔
    */
    uint32_t m_timeOut;

    /** 执行次数
    */
    int32_t m_times;

    /** 当前执行次数
    */
    int32_t m_curTimes;
};

#endif // __IHEARTBEATTASK_h_
