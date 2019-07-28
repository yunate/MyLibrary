
#ifndef __CPU_THREAD_COUNT_H_
#define __CPU_THREAD_COUNT_H_

/** 获得cpu核心线从数量,这是一个单例
*/
class CpuCoreThreadCount
{
protected:
    /** 构造函数
    */
    CpuCoreThreadCount();

    /** 拷贝构造函数删除掉
    */
    CpuCoreThreadCount(const CpuCoreThreadCount&) = delete;

    /** 赋值构造函数删除掉
    */
    CpuCoreThreadCount& operator= (const CpuCoreThreadCount&) = delete;

public:
    inline unsigned int GetCount()
    {
        return m_cpuCoreThreadCount;
    }

private:
    /** cpu最大逻辑线程数，为0的时候说明获取失败，外部自己处理
    */
    unsigned int m_cpuCoreThreadCount;
};

#endif // __CPU_THREAD_COUNT_H_


