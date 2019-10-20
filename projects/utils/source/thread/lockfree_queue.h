
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
    lockfree_queue()
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

    lockfree_queue(const lockfree_queue& r)
    {
        // 构造的时候不会有线程安全问题
        ty_data* pSrc = r.m_head;
        ty_data* pDes = new(std::nothrow) ty_data();
        m_head = pDes;

        while (pSrc != nullptr && pDes != nullptr)
        {
            pDes->m_val = pSrc->m_val;
            pSrc = pSrc->m_pNext;

            if (pSrc != nullptr)
            {
                pDes->m_pNext = new(std::nothrow) ty_data();
                pDes = pDes->m_pNext;
                ++m_size;
            }
        }

        m_tail = pDes;
    }

    lockfree_queue(lockfree_queue&& r)
    {
        m_head = r.m_head;
        r.m_head = nullptr;
        m_tail = r.m_tail;
        r.m_tail = nullptr; 
        m_size = r.m_size;
        r.m_size = 0;
    }

    lockfree_queue& operator=(const lockfree_queue& r)
    {
        lockfree_queue tmp(r);
        swap(tmp);
        return *this;
    }

    void swap(lockfree_queue& r)
    {
        std::swap(m_head, r.m_head);
        std::swap(m_tail, r.m_tail);
        std::swap(m_size, r.m_size);
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
    int m_size = 0;

    /** 队列头部，这个只是标记头部，不保存数据
    */
    ty_data* m_head = nullptr;

    /** 队列尾部
    */
    ty_data* m_tail = nullptr;

    /** 自旋锁
    */
    spin_mutex m_spinLock;
};
}
#endif //__LOCKFREE_QUEUE_H_
