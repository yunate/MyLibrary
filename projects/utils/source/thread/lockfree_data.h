
#ifndef __LOCKFREE_DATA_H_
#define __LOCKFREE_DATA_H_

namespace lockfree
{
template<class ty>
class lockfree_data
{
public:
    /** 构造函数
    */
    lockfree_data(const ty& val) :
        m_val(val),
        m_pNext(NULL)
    {

    }

    /** 构造函数
    */
    lockfree_data() :
        m_pNext(NULL)
    {

    }

    /** 不允许复制
    */
    lockfree_data(const lockfree_data&) = delete;
    lockfree_data(lockfree_data&&) = delete;
    lockfree_data& operator =(const lockfree_data&) = delete;

    ~lockfree_data()
    {
        m_pNext = NULL;
    }

public:
    /** 数据
    */
    ty m_val;

    /** 下一个指针
    */
    lockfree_data* m_pNext;
};
}
#endif //__LOCKFREE_DATA_H_
