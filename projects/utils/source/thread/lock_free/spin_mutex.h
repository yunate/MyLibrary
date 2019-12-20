
#include <atomic>

namespace lockfree
{

/** 这下子再也不用::Sleep(0)了~~
*/
#define cpu_pause() __asm {pause}

/** 自旋锁
*/
class spin_mutex
{
public:
    /** 构造函数
    */
    spin_mutex()
    {
    }

    ~spin_mutex()
    {

    }

    /** 不允许复制
    */
    spin_mutex(spin_mutex&&) = delete;
    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator=(const spin_mutex&&) = delete;

public:
    void lock()
    {
        // test_and_set 返回m_falg的设置前的值
        while (m_flag.test_and_set() != false)
        {
            cpu_pause()
        }
    }

    void unlock()
    {
        m_flag.clear();
    }

private:
    /** 自旋锁标记
    */
    std::atomic_flag m_flag = ATOMIC_FLAG_INIT;
};
}
