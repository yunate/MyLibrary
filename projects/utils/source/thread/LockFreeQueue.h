
#ifndef __LOCKFREE_QUEUE_H_
#define __LOCKFREE_QUEUE_H_

#include "LockFreeData.h"

#include <new>
#include <atomic>

/** 安全的push
*/
//#define LOCKFREE_QUEUE_SAFEPUSH

/** 无锁队列
*/
template<class ty>
class LockFreeQueue
{
    using tyData = LockFreeData<ty>;
public:
    /** 构造/析构函数
    */
    LockFreeQueue() :
        m_size(0),
        m_head(nullptr),
        m_tail(nullptr)
    {
        // 构造的时候不会有线程安全问题
        m_head = new(std::nothrow) tyData();
        m_tail = m_head;
    }

    ~LockFreeQueue()
    {
        // 析构的时候不会有线程安全问题
        m_tail = nullptr;

        while (m_head != nullptr)
        {
            tyData* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

public:
    /** 弹出队首
    @param [out] data数据
    @return 失败返回NULL，否则返回队首，这个是一份复制
    */
    bool Pop(ty& out)
    {
        if (m_head == nullptr)
        {
            return false;
        }

        tyData* p = nullptr;

        do
        {
            p = m_head;

            if (p->m_pNext == NULL)
            {
                return false;
            }

        } while (!__sync_bool_compare_and_swap(m_head, p, p->m_pNext));

        --m_size;
        out = p->m_pNext->m_val;
        delete p;
        return true;
    }

    /** 压入对尾
    @param [in] data数据
    @return 是否成功
    */
    bool Push(const ty& data)
    {
        if (m_tail == nullptr)
        {
            return false;
        }

        tyData* q = new(std::nothrow) tyData(data);

        if (q == nullptr)
        {
            return false;
        }

        tyData* p = m_tail;
#ifdef LOCKFREE_QUEUE_SAFEPUSH
        int i = 0;
#endif
        do
        {
#ifdef LOCKFREE_QUEUE_SAFEPUSH
            if (i == 3 && p->m_pNext != nullptr)
            {
                p = p->m_pNext;
                m_tail = p;
            }
            else
            {
                p = m_tail;
                ++i;
            }
#else
            p = m_tail;
#endif // LOCKFREE_QUEUE_SAFEPUSH
        } while (!__sync_bool_compare_and_swap(p->m_pNext, nullptr, q));
        
        __sync_bool_compare_and_swap(m_tail, p, q);
        ++m_size;
        return true;
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
    tyData* m_head;

    /** 队列尾部
    */
    tyData* m_tail;
};

#endif //__LOCKFREE_QUEUE_H_
