#include "producer_consumer.h"

#include "misc/cpu_thread_count.h"
#include "base/singleton.hpp"
#include <functional>
#include <assert.h>

BEG_NSP_DDM

/** ��Ʒ�������
*/
const long MAX_SEMAPHORE_COUNT = 0x7FFFFFFF;

/** ��BEFORE_TIME_PASS����֮��ʼƽ���߳�����
*/
const long BEFORE_TIME_PASS = 3000;

p_c_model::p_c_model(iproducer* pProducer, iconsumer* pconsumer) :
    m_pProducer(pProducer),
    m_pconsumer(pconsumer),
    m_pMutex(nullptr),
    m_hSemaphore(nullptr),
    m_isproductEnd(false),
    m_maxThreadCount(0),
    m_pTimerRecoder(nullptr),
    m_notUsedThreadCount(0),
    m_sleepThreadCount(0),
    m_maxProducerCount(AUTO_THREAD_COUNT)
{
    m_maxThreadCount = cpu_thread_count::get_thread_count();

    // �����ȡʧ���˻���֧�ֵ��߳�ֻ��1������ô����̱߳��������������������߸�һ����
    if (m_maxThreadCount < 2)
    {
        m_maxThreadCount = 2;
    }
}

p_c_model::~p_c_model()
{
    if (m_goodsVec.size() > 0)
    {
        for (auto it : m_goodsVec)
        {
            delete it;
        }

        m_goodsVec.clear();
    }
}

void p_c_model::Start()
{
    if (m_pProducer == nullptr ||
        m_pconsumer == nullptr)
    {
        return;
    }

    m_pMutex = new (std::nothrow) std::mutex();

    if (m_pMutex == nullptr)
    {
        return;
    }

    m_hSemaphore = ::CreateSemaphore(nullptr, 0, MAX_SEMAPHORE_COUNT, nullptr);

    if (m_hSemaphore == nullptr)
    {
        return;
    }

    m_pTimerRecoder = new (std::nothrow) xtimer();

    if (m_pTimerRecoder == nullptr)
    {
        return;
    }

    Startproduct();
    StartConsume();

    // �ȴ������߶�����
    for (auto it : m_producerThreadVec)
    {
        it->join();
    }

    m_isproductEnd = true;

    // �ȴ������߶�����
    for (unsigned int i = 0; i < m_consumerThreadVec.size(); ++i)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, nullptr);
    }

    for (auto it : m_consumerThreadVec)
    {
        it->join();
    }

    // ��Դ����
    for (auto it : m_producerThreadVec)
    {
        delete it;
    }

    m_producerThreadVec.clear();

    for (auto it : m_consumerThreadVec)
    {
        delete it;
    }

    m_consumerThreadVec.clear();
    ::CloseHandle(m_hSemaphore);
    delete m_pMutex;
    m_pMutex = nullptr;
}

void p_c_model::productCallBack(igoods* pGoods)
{
    if (pGoods == nullptr)
    {
        return;
    }

    m_pMutex->lock();
    int tmp = (int)m_maxProducerCount;

    if (tmp == AUTO_THREAD_COUNT)
    {
        tmp = (int)m_producerThreadVec.size();
    }

    tmp = (int)m_maxThreadCount - tmp - (int)m_notUsedThreadCount;

    // ���ж���δʹ���߳�&&(��Ʒ��ʣ||�������߳�������û�дﵽ���)����������������
    if ((int)m_consumerThreadVec.size() < tmp &&
        (m_goodsVec.size() > m_consumerThreadVec.size() || m_producerThreadVec.size() < m_maxProducerCount))
    {
        if (!m_isproductEnd && m_pTimerRecoder->get_time_pass() > BEFORE_TIME_PASS)
        {
            AddConsumeThread();
        }
    }

    m_goodsVec.push_back(pGoods);

    // �����߹���,��������ģʽ������
    assert(m_goodsVec.size() < MAX_SEMAPHORE_COUNT);

    if (m_sleepThreadCount > 0)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, nullptr);
    }

    m_pMutex->unlock();
}

void p_c_model::ConsumeCallBack()
{
    while (true)
    {
        m_pMutex->lock();

        // ����̫����
        if (m_goodsVec.size() == 0)
        {
            m_pMutex->unlock();

            if (m_isproductEnd)
            {
                break;
            }
 
            m_pMutex->lock();
 
            // ��������������
            int tmp = (int)m_maxProducerCount;
 
            if (tmp == AUTO_THREAD_COUNT)
            {
                tmp = (int)m_maxThreadCount - (int)m_consumerThreadVec.size() - (int)m_notUsedThreadCount;
            }
 
            if ((int)m_producerThreadVec.size() < tmp && !m_isproductEnd)
            {
                if (m_pTimerRecoder->get_time_pass() > BEFORE_TIME_PASS)
                {
                    AddproductThread();
                }
            }
 
            ++m_sleepThreadCount;
            m_pMutex->unlock();
 
            ::WaitForSingleObject(m_hSemaphore, INFINITE);
            m_pMutex->lock();
            --m_sleepThreadCount;
 
            // ���Ǳ������ˣ������Ļ�ֱ�ӷ���
            if (m_goodsVec.size() == 0)
            {
                m_pMutex->unlock();
                continue;
            }
        }

        igoods* pGoods = m_goodsVec.back();
        m_goodsVec.pop_back();
        m_pMutex->unlock();
        m_pconsumer->consumer(pGoods);

        // ��Ҫ��������
        delete pGoods;
    }
}

bool p_c_model::AddproductThread()
{
    // �ȿ���һ���߳�
    std::thread* pThread = new (std::nothrow) std::thread([this]()
    {
        m_pProducer->product([this](igoods* pGoods)
        {
            productCallBack(pGoods);
        });
    });

    if (pThread == nullptr)
    {
        return false;
    }

    m_producerThreadVec.push_back(pThread);
    return true;
}

bool p_c_model::AddConsumeThread()
{
    // �ȿ���һ���߳�
    std::thread* pThread = new (std::nothrow) std::thread([&]()
    {
        ConsumeCallBack();
    });

    if (pThread == nullptr)
    {
        return false;
    }

    m_consumerThreadVec.push_back(pThread);
    return true;
}

bool p_c_model::Startproduct()
{
    // һ��������
    if (m_maxProducerCount == 0)
    {
        m_pProducer->product([&](igoods* pGoods)
        {
            if (pGoods == nullptr)
            {
                return;
            }

            m_goodsVec.push_back(pGoods);
        });

        return true;
    }

    return AddproductThread();
}

bool p_c_model::StartConsume()
{
    // m_maxProducerCountҲ����ΪMAX_THREAD_COUNT
    // ΪMAX_THREAD_COUNTʱ����߳�������Ȼ�������߳�һ��������
    if (m_maxProducerCount == MAX_THREAD_COUNT)
    {
        for (auto it : m_goodsVec)
        {
            m_pconsumer->consumer(it);
        }

        return true;
    }
    
    return AddConsumeThread();
}
END_NSP_DDM