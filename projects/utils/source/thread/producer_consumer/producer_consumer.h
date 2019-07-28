
#ifndef __PRODUCER_CONSUMER_H_
#define __PRODUCER_CONSUMER_H_

/************************************************************************************************
*生产者-消费者模型，主要为了用多线程加速来充分使用cpu资源。                                              *
*比如对于一个大文件的处理，可以指定一个线程专门读文件（一个线程基本上就可以将io占满了）,其余线程处理每次读的结果  *
************************************************************************************************/

#include "IProducer.h"
#include "IConsume.h"
#include <vector>
#include <thread>
#include <mutex>
#include <windows.h>
#include "timer_recorder/timer_recorder.h"

using GOODS_VEC = std::vector<IGoods*>;
using THREAD_VEC = std::vector<std::thread*>;

/** 线程最大数量，当一个标记使用，具体数值并没有实际意义
*/
#define MAX_THREAD_COUNT 10000

/** 线程未指定最大数量，当一个标记使用
*/
#define AUTO_THREAD_COUNT 100000

/** Producer_Consumer_Model 生产者消费者模型类
*/
class PAndCModel
{
public:
    PAndCModel(IProducer* pProducer, IConsumer* pConsumer);
    ~PAndCModel();

public:

    void Start();

    /** 有的时候不希望跑满cpu，这个时候可以指定剩余几个cpu线程。
    如果m_maxThreadCount为2，那么此参数无效
    @param [in] count 数量
    */
    inline void SetNotUseThreadCount(unsigned int count)
    {
        if (m_maxThreadCount <= 2)
        {
            m_notUsedThreadCount = 0;
        }
        else
        {
            m_notUsedThreadCount = count;
        }
    }

    /** 有的时候因为某种原因还需要指定生产者/消费者最大数量
    @param [in] count 数量，该数量可以为0，为0的时候主线程一次性生产所有商品，然后再多线程消费，
                也可以为MAX_THREAD_COUNT，为MAX_THREAD_COUNT时候多线程生产，然后在主线程一次性消费
                也可以为AUTO_THREAD_COUNT，为AUTO_THREAD_COUNT时候自动调整线程数量
    */
    inline void SetMaxProducerCount(unsigned int count)
    {
        m_maxProducerCount = count;
    }

private:
    /** 生产者线程回调
    */
    void ProductCallBack(IGoods* pGoods);

    /** 生消费者线程回调
    */
    void ConsumeCallBack();

    /** 添加一个生产者线程
    */
    bool AddProductThread();

    /** 添加一个消费者线程
    */
    bool AddConsumeThread();

private:
    /** 开始生产
    @return 是否成功
    */
    bool StartProduct();

    /** 开始消费
    @return 是否成功
    */
    bool StartConsume();

private:
    /** 生产者
    */
    IProducer* m_pProducer;

    /** 消费者
    */
    IConsumer* m_pConsumer;

    /** 生产者线程池
    */
    THREAD_VEC m_producerThreadVec;

    /** 消费者线程池
    */
    THREAD_VEC m_consumerThreadVec;

    /** 商品缓存
    */
    GOODS_VEC m_goodsVec;

    /** 是否生产结束
    */
    bool m_isProductEnd;

    /** 互斥量
    */
    std::mutex* m_pMutex;

    /** 生产者消费者同步量
    */
    HANDLE m_hSemaphore;

    /** 最大线程数量
    */
    unsigned int m_maxThreadCount;

    /** 不使用的线程数量
    */
    unsigned int m_notUsedThreadCount;

    /** 最大生产者数量
    */
    unsigned int m_maxProducerCount;

    /** 计时器
    */
    TimerRecorder* m_pTimerRecoder;

    /** 等待中的线程数量
    */
    int m_sleepThreadCount;
};



#endif


