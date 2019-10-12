
#ifndef __LOCKFREE_QUEUE_H_
#define __LOCKFREE_QUEUE_H_

#include "LockFreeData.h"

#include <new>
#include <atomic>

/** 无锁队列
*/
template<class ty>
class LockFreeQueue
{
public:
    /** 构造/析构函数
    */
    LockFreeQueue() :
        m_size(0),
        m_head(nullptr),
        m_tail(nullptr)
    {
        // 构造的时候不会有线程安全问题
        m_head = new(std::nothrow) LockFreeData();
        m_tail = m_head;
    }

    ~LockFreeQueue()
    {
        // 析构的时候不会有线程安全问题
        m_tail = nullptr;

        while (m_head != nullptr)
        {
            ILockFreeData* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

public:
    /** 弹出队首
    @param [out] data数据
    @return 失败返回NULL，否则返回队首，这个是一份复制
    */
    template<class ty>
    bool Pop(ty& out)
    {
        if (m_head == nullptr)
        {
            return false;
        }

        LockFreeData* p = nullptr;

        do
        {
            p = m_head;

            if (p->m_pNext == NULL)
            {
                return false;
            }

        } while (m_head.compare_exchange_strong(p, p->m_pNext));

        --m_size;
        out = p->m_pNext->m_val;
        delete p;
    }

    /** 压入对尾
    @param [in] data数据
    @return 是否成功
    */
    template<class ty>
    bool Push(const ty& data)
    {
        LockFreeData* q = new(std::nothrow) LockFreeData(data);

        if (q == nullptr)
        {
            return false;
        }

        LockFreeData* p = m_tail;
        LockFreeData* rawTail = p;
        int i = 0;

        do
        {
            if (i == 2)
            {
                while (p->next != nullptr)
                {
                    p = p->next;
                }
            }
            else
            {
                ++i;
                p = m_tail;
            }
        } while (p->m_pNext.compare_exchange_strong(nullptr, q));
        
        m_tail.compare_exchange_strong(i == 2 ? rawTail : p, q);
        ++m_size;
    }

    /** 获得大小
    */
    int Size()
    {
        return m_size;
    }

protected:
    /** 容器的大小
    */
    std::atomic<int> m_size;

    /** 队列头部，这个只是标记头部，不保存数据
    */
    LockFreeData* m_head;

    /** 队列尾部
    */
    LockFreeData* m_tail;
};

#endif //__LOCKFREE_QUEUE_H_
