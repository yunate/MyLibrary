
#ifndef lockfree_data_h_
#define lockfree_data_h_ 1
#include "base/g_def.h"

BEG_NSP_DDM
template<class ty>
class lockfree_data
{
public:
    /** 构造函数
    */
    lockfree_data(const ty& val) :
        m_val(val),
        m_pNext(nullptr) {}

    /** 构造函数
    */
    lockfree_data() :
        m_val(ty()),
        m_pNext(nullptr) {}

    /** 不允许复制
    */
    lockfree_data(const lockfree_data&) = delete;
    lockfree_data(lockfree_data&&) = delete;
    lockfree_data& operator =(const lockfree_data&) = delete;

    ~lockfree_data() {
        m_pNext = nullptr;
    }

public:
    /** 数据
    */
    ty m_val;

    /** 下一个指针
    */
    lockfree_data* m_pNext;
};

END_NSP_DDM
#endif // lockfree_data_h_
