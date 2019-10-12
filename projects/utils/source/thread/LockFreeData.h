
#ifndef __LOCKFREE_DATA_H_
#define __LOCKFREE_DATA_H_

template<class ty>
class LockFreeData
{
public:
    /** 构造函数
    */
    LockFreeData(const ty& val) :
        m_val(val),
        m_pNext(NULL)
    {

    }

    /** 构造函数
    */
    LockFreeData() :
        m_pNext(NULL)
    {

    }

    /** 不允许复制
    */
    LockFreeData(const LockFreeData&) = delete;
    LockFreeData(LockFreeData&&) = delete;
    LockFreeData& operator =(const LockFreeData&) = delete;

    ~LockFreeData()
    {
        m_pNext = NULL;
    }

public:
    /** 数据
    */
    ty m_val;

    /** 下一个指针
    */
    LockFreeData* m_pNext;
};

#endif //__LOCKFREE_DATA_H_
