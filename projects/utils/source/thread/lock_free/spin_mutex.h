
#include <atomic>

namespace lockfree
{

/** 这下子再也不用::Sleep(0)了~~
*/
#define cpu_pause() __asm {pause}

/** 自旋锁
@note 这个只能当作试例看了，它的效率并不比mutex高
@note 感觉无锁编程，如果用到循环控制的话，就是在扯淡了，因为mutex windows下实现也是循环控制，但是
@note 它的汇编代码更少，
@note 除非有的地方仅仅使用CAS才有效率的提升可能
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
