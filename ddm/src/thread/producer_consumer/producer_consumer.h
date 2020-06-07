
#ifndef producer_consumer_h_
#define producer_consumer_h_ 1

/************************************************************************************************
*������-������ģ�ͣ���ҪΪ���ö��̼߳��������ʹ��cpu��Դ��                                              *
*�������һ�����ļ��Ĵ�������ָ��һ���߳�ר�Ŷ��ļ���һ���̻߳����ϾͿ��Խ�ioռ���ˣ�,�����̴߳���ÿ�ζ��Ľ��  *
************************************************************************************************/

#include "iproducer.h"
#include "iconsumer.h"
#include <vector>
#include <thread>
#include <mutex>
#include <windows.h>
#include "timer_recorder/timer_recorder.h"

BEG_NSP_DDM
using goods_vec = std::vector<igoods*>;
using thread_vec = std::vector<std::thread*>;

/** �߳������������һ�����ʹ�ã�������ֵ��û��ʵ������
*/
#define MAX_THREAD_COUNT 10000

/** �߳�δָ�������������һ�����ʹ��
*/
#define AUTO_THREAD_COUNT 100000

/** Producer_consumer_Model ������������ģ����
*/
class p_c_model
{
public:
    p_c_model(iproducer* pProducer, iconsumer* pconsumer);
    ~p_c_model();

public:

    void Start();

    /** �е�ʱ��ϣ������cpu�����ʱ�����ָ��ʣ�༸��cpu�̡߳�
    ���m_maxThreadCountΪ2����ô�˲�����Ч
    @param [in] count ����
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

    /** �е�ʱ����Ϊĳ��ԭ����Ҫָ��������/�������������
    @param [in] count ����������������Ϊ0��Ϊ0��ʱ�����߳�һ��������������Ʒ��Ȼ���ٶ��߳����ѣ�
                Ҳ����ΪMAX_THREAD_COUNT��ΪMAX_THREAD_COUNTʱ����߳�������Ȼ�������߳�һ��������
                Ҳ����ΪAUTO_THREAD_COUNT��ΪAUTO_THREAD_COUNTʱ���Զ������߳�����
    */
    inline void SetMaxProducerCount(unsigned int count)
    {
        m_maxProducerCount = count;
    }

private:
    /** �������̻߳ص�
    */
    void productCallBack(igoods* pGoods);

    /** ���������̻߳ص�
    */
    void ConsumeCallBack();

    /** ���һ���������߳�
    */
    bool AddproductThread();

    /** ���һ���������߳�
    */
    bool AddConsumeThread();

private:
    /** ��ʼ����
    @return �Ƿ�ɹ�
    */
    bool Startproduct();

    /** ��ʼ����
    @return �Ƿ�ɹ�
    */
    bool StartConsume();

private:
    /** ������
    */
    iproducer* m_pProducer;

    /** ������
    */
    iconsumer* m_pconsumer;

    /** �������̳߳�
    */
    thread_vec m_producerThreadVec;

    /** �������̳߳�
    */
    thread_vec m_consumerThreadVec;

    /** ��Ʒ����
    */
    goods_vec m_goodsVec;

    /** �Ƿ���������
    */
    bool m_isproductEnd;

    /** ������
    */
    std::mutex* m_pMutex;

    /** ������������ͬ����
    */
    HANDLE m_hSemaphore;

    /** ����߳�����
    */
    unsigned int m_maxThreadCount;

    /** ��ʹ�õ��߳�����
    */
    unsigned int m_notUsedThreadCount;

    /** �������������
    */
    unsigned int m_maxProducerCount;

    /** ��ʱ��
    */
    TimerRecorder* m_pTimerRecoder;

    /** �ȴ��е��߳�����
    */
    int m_sleepThreadCount;
};

END_NSP_DDM
#endif // producer_consumer_h_


