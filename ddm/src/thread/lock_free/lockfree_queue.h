
#ifndef lockfree_queue_h_
#define lockfree_queue_h_ 1

#include "lockfree_data.h"
#include "spin_mutex.h"
#include "base/g_def.h"

BEG_NSP_DDM
/** ��������
@note ���ֻ�ܵ���ʵ�����ˣ�����Ч�ʲ�����mutex��
*/
template<class ty>
class lockfree_queue
{
    using ty_data = lockfree_data<ty>;

public:
    /** ����/��������
    */
    lockfree_queue() {
        // �����ʱ�򲻻����̰߳�ȫ����
        m_head = new(std::nothrow) ty_data();
        m_tail = m_head;
    }

    ~lockfree_queue() {
        // ������ʱ�򲻻����̰߳�ȫ����
        m_spinLock.unlock();
        m_tail = nullptr;

        while (m_head != nullptr) {
            ty_data* pTmp = m_head;
            m_head = m_head->m_pNext;
            delete pTmp;
        }
    }

    lockfree_queue(const lockfree_queue& r) {
        // �����ʱ�򲻻����̰߳�ȫ����
        ty_data* pSrc = r.m_head;
        ty_data* pDes = new(std::nothrow) ty_data();
        m_head = pDes;

        while (pSrc != nullptr && pDes != nullptr) {
            pDes->m_val = pSrc->m_val;
            pSrc = pSrc->m_pNext;

            if (pSrc != nullptr) {
                pDes->m_pNext = new(std::nothrow) ty_data();
                pDes = pDes->m_pNext;
                ++m_size;
            }
        }

        m_tail = pDes;
    }

    lockfree_queue(lockfree_queue&& r) noexcept {
        m_head = r.m_head;
        r.m_head = nullptr;
        m_tail = r.m_tail;
        r.m_tail = nullptr; 
        m_size = r.m_size;
        r.m_size = 0;
    }

    lockfree_queue& operator=(const lockfree_queue& r) {
        lockfree_queue tmp(r);
        swap(tmp);
        return *this;
    }

    void swap(lockfree_queue& r)  {
        std::swap(m_head, r.m_head);
        std::swap(m_tail, r.m_tail);
        std::swap(m_size, r.m_size);
    }

public:
    /** ��������
    @param [out] data����
    @return ʧ�ܷ���nullptr�����򷵻ض��ף������һ�ݸ���
    */
    bool pop(ty& out) {
        m_spinLock.lock();

        if (m_head->m_pNext == nullptr) {
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

    /** ѹ���β
    @param [in] data����
    @return �Ƿ�ɹ�
    */
    bool push(const ty& data) {
        ty_data* q = new(std::nothrow) ty_data(data);

        if (q == nullptr) {
            return false;
        }

        m_spinLock.lock();
        m_tail->m_pNext = q;
        m_tail = q;
        ++m_size;
        m_spinLock.unlock();
        return true;
    }

    /** ��ô�С
    */
    int size()  {
        return m_size;
    }

protected:
    /** �����Ĵ�С
    */
    int m_size = 0;

    /** ����ͷ�������ֻ�Ǳ��ͷ��������������
    */
    ty_data* m_head = nullptr;

    /** ����β��
    */
    ty_data* m_tail = nullptr;

    /** ������
    */
    spin_mutex m_spinLock;
};
END_NSP_DDM
#endif // lockfree_queue_h_
