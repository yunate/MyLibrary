#include "producer_consumer.h"

#include "misc/cpu_thread_count.h"
#include "base/singleton.hpp"
#include <functional>
#include <assert.h>

BEG_NSP_DDM

/** 商品最大数量
*/
const long MAX_SEMAPHORE_COUNT = 0x7FFFFFFF;

/** 在BEFORE_TIME_PASS毫秒之后开始平衡线程数量
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

    // 如果获取失败了或者支持的线程只有1个，那么最大线程保持两个（生产者消费者各一个）
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

    // 等待生产者都结束
    for (auto it : m_producerThreadVec)
    {
        it->join();
    }

    m_isproductEnd = true;

    // 等待消费者都结束
    for (unsigned int i = 0; i < m_consumerThreadVec.size(); ++i)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, nullptr);
    }

    for (auto it : m_consumerThreadVec)
    {
        it->join();
    }

    // 资源清理
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

    // 还有多余未使用线程&&(产品过剩||生产者线程数量还没有达到最高)，尝试增加消费者
    if ((int)m_consumerThreadVec.size() < tmp &&
        (m_goodsVec.size() > m_consumerThreadVec.size() || m_producerThreadVec.size() < m_maxProducerCount))
    {
        if (!m_isproductEnd && m_pTimerRecoder->get_time_pass() > BEFORE_TIME_PASS)
        {
            AddConsumeThread();
        }
    }

    m_goodsVec.push_back(pGoods);

    // 生产者过快,这个情况本模式不适用
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

        // 消费太快了
        if (m_goodsVec.size() == 0)
        {
            m_pMutex->unlock();

            if (m_isproductEnd)
            {
                break;
            }
 
            m_pMutex->lock();
 
            // 尝试增加生产者
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
 
            // 还是被消费了，这样的化直接返回
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

        // 不要忘了销毁
        delete pGoods;
    }
}

bool p_c_model::AddproductThread()
{
    // 先开启一个线程
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
    // 先开启一个线程
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
    // 一次性生产
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
    // m_maxProducerCount也可以为MAX_THREAD_COUNT
    // 为MAX_THREAD_COUNT时候多线程生产，然后在主线程一次性消费
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