
#ifndef __LOCKFREE_QUEUE_H_
#define __LOCKFREE_QUEUE_H_

#include "lockfree_data.h"
#include "spin_mutex.h"
namespace lockfree
{
/** 无锁队列
*/
template<class ty>
class lockfree_queue
{
    using ty_data = lockfree_data<ty>;

public:
    /** 构造/析构函数
    */
    lockfree_queue() :
        m_size(0),
        m_head(nullptr),
        m_tail(nullptr)
    {
        // 构造的时候不会有线程安全问题
        m_head = new(std::nothrow) ty_data();
        m_tail = m_head;
    }

    ~lockfree_queue()
    {
        // 析构的时候不会有线程安全问题
        m_spinLock.unlock();
        m_tail = nullptr;

        while (m_head != nullptr)
        {
            ty_data* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

public:
    /** 弹出队首
    @param [out] data数据
    @return 失败返回NULL，否则返回队首，这个是一份复制
    */
    bool pop(ty& out)
    {
        m_spinLock.lock();

        if (m_head->m_pNext == nullptr)
        {
            m_spinLock.unlock();
            return false;
        }

        --m_size;
        ty_data* p = m_head;
        m_head = m_head->m_pNext;
        out = p->m_pNext->m_val;
        m_spinLock.unlock();
        delete p;
        return true;
    }

    /** 压入对尾
    @param [in] data数据
    @return 是否成功
    */
    bool push(const ty& data)
    {
        ty_data* q = new(std::nothrow) ty_data(data);

        if (q == nullptr)
        {
            return false;
        }

        m_spinLock.lock();
        m_tail->m_pNext = q;
        m_tail = q;
        ++m_size;
        m_spinLock.unlock();
        return true;
    }

    /** 获得大小
    */
    int size()
    {
        return m_size;
    }

protected:
    /** 容器的大小
    */
    int m_size;

    /** 队列头部，这个只是标记头部，不保存数据
    */
    ty_data* m_head;

    /** 队列尾部
    */
    ty_data* m_tail;

    /** 自旋锁
    */
    spin_mutex m_spinLock;
};
}
#endif //__LOCKFREE_QUEUE_H_
