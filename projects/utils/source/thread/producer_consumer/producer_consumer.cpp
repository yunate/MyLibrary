#include "producer_consumer.h"

#include "cpu/cpu_thread_count.h"
#include "singleton/singleton.h"
#include <functional>
#include <assert.h>

/** 商品最大数量
*/
const long MAX_SEMAPHORE_COUNT = 0x7FFFFFFF;

/** 在BEFORE_TIME_PASS毫秒之后开始平衡线程数量
*/
const long BEFORE_TIME_PASS = 3000;

PAndCModel::PAndCModel(IProducer* pProducer, IConsumer* pConsumer) :
    m_pProducer(pProducer),
    m_pConsumer(pConsumer),
    m_pMutex(NULL),
    m_hSemaphore(NULL),
    m_isProductEnd(false),
    m_maxThreadCount(0),
    m_pTimerRecoder(NULL),
    m_notUsedThreadCount(0),
    m_sleepThreadCount(0),
    m_maxProducerCount(AUTO_THREAD_COUNT)
{
    m_maxThreadCount = 
        Singleton<CpuCoreThreadCount>::GetInstance().GetCount();

    // 如果获取失败了或者支持的线程只有1个，那么最大线程保持两个（生产者消费者各一个）
    if (m_maxThreadCount < 2)
    {
        m_maxThreadCount = 2;
    }
}

PAndCModel::~PAndCModel()
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

void PAndCModel::Start()
{
    if (m_pProducer == NULL ||
        m_pConsumer == NULL)
    {
        return;
    }

    m_pMutex = new (std::nothrow) std::mutex();

    if (m_pMutex == NULL)
    {
        return;
    }

    m_hSemaphore = ::CreateSemaphore(NULL, 0, MAX_SEMAPHORE_COUNT, NULL);

    if (m_hSemaphore == NULL)
    {
        return;
    }

    m_pTimerRecoder = new (std::nothrow) TimerRecorder();

    if (m_pTimerRecoder == NULL)
    {
        return;
    }

    StartProduct();
    StartConsume();

    // 等待生产者都结束
    for (auto it : m_producerThreadVec)
    {
        it->join();
    }

    m_isProductEnd = true;

    // 等待消费者都结束
    for (unsigned int i = 0; i < m_consumerThreadVec.size(); ++i)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, NULL);
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
    m_pMutex = NULL;
}

void PAndCModel::ProductCallBack(IGoods* pGoods)
{
    if (pGoods == NULL)
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
        if (!m_isProductEnd && m_pTimerRecoder->GetTimePass() > BEFORE_TIME_PASS)
        {
            AddConsumeThread();
        }
    }

    m_goodsVec.push_back(pGoods);

    // 生产者过快,这个情况本模式不适用
    assert(m_goodsVec.size() < MAX_SEMAPHORE_COUNT);

    if (m_sleepThreadCount > 0)
    {
        ::ReleaseSemaphore(m_hSemaphore, 1, NULL);
    }

    m_pMutex->unlock();
}

void PAndCModel::ConsumeCallBack()
{
    while (true)
    {
        m_pMutex->lock();

        // 消费太快了
        if (m_goodsVec.size() == 0)
        {
            m_pMutex->unlock();

            if (m_isProductEnd)
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
 
            if ((int)m_producerThreadVec.size() < tmp && !m_isProductEnd)
            {
                if (m_pTimerRecoder->GetTimePass() > BEFORE_TIME_PASS)
                {
                    AddProductThread();
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

        IGoods* pGoods = m_goodsVec.back();
        m_goodsVec.pop_back();
        m_pMutex->unlock();
        m_pConsumer->Consumer(pGoods);

        // 不要忘了销毁
        delete pGoods;
    }
}

bool PAndCModel::AddProductThread()
{
    // 先开启一个线程
    std::thread* pThread = new (std::nothrow) std::thread([this]()
    {
        m_pProducer->Product([this](IGoods* pGoods)
        {
            ProductCallBack(pGoods);
        });
    });

    if (pThread == NULL)
    {
        return false;
    }

    m_producerThreadVec.push_back(pThread);
    return true;
}

bool PAndCModel::AddConsumeThread()
{
    // 先开启一个线程
    std::thread* pThread = new (std::nothrow) std::thread([&]()
    {
        ConsumeCallBack();
    });

    if (pThread == NULL)
    {
        return false;
    }

    m_consumerThreadVec.push_back(pThread);
    return true;
}

bool PAndCModel::StartProduct()
{
    // 一次性生产
    if (m_maxProducerCount == 0)
    {
        m_pProducer->Product([&](IGoods* pGoods)
        {
            if (pGoods == NULL)
            {
                return;
            }

            m_goodsVec.push_back(pGoods);
        });

        return true;
    }

    return AddProductThread();
}

bool PAndCModel::StartConsume()
{
    // m_maxProducerCount也可以为MAX_THREAD_COUNT
    // 为MAX_THREAD_COUNT时候多线程生产，然后在主线程一次性消费
    if (m_maxProducerCount == MAX_THREAD_COUNT)
    {
        for (auto it : m_goodsVec)
        {
            m_pConsumer->Consumer(it);
        }

        return true;
    }
    
    return AddConsumeThread();
}
