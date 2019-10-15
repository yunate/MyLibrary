
#ifndef __LOCKFREE_DATA_H_
#define __LOCKFREE_DATA_H_

#ifdef WIN32
    #include <windows.h>
    // PVOID __cdecl InterlockedCompareExchangePointer(
    //    _Inout_ PVOID volatile *Destination,
    //    _In_    PVOID          Exchange,
    //    _In_    PVOID          Comparand
    //    );
    //
    //Parameters
    //    Destination [in, out]
    //A pointer to a pointer to the destination value.
    //    Exchange [in]
    //The exchange value.
    //    Comparand [in]
    //The value to compare to Destination.
    //    Return value
    //    The function returns the initial value of the Destination parameter.
    //    Remarks
    //    The function compares the Destination value with the Comparand value. If the Destination value is equal to the Comparand value, the Exchange value is stored in the address specified by Destination. Otherwise, no operation is performed.
    //    On a 64-bit system, the parameters are 64 bits and must be aligned on 64-bit boundaries; otherwise, the function will behave unpredictably. On a 32-bit system, the parameters are 32 bits and must be aligned on 32-bit boundaries.
    //    The interlocked functions provide a simple mechanism for synchronizing access to a variable that is shared by multiple threads. This function is atomic with respect to calls to other interlocked functions.
#define __sync_bool_compare_and_swap(a, b, c) (InterlockedCompareExchangePointer((void*volatile*)&a, c, b) == b)
#endif

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
