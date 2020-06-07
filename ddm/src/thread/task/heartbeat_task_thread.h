
#ifndef heartbeat_task_thread_h_
#define heartbeat_task_thread_h_ 1

#include "i_heartbeat_task.h"
#include "base/g_def.h"
#include "base/nocopyable.hpp"

#include <list>
#include <thread>
#include <mutex>
BEG_NSP_DDM
struct heartbeat_task_wraper;
using sp_heartbeat_taskWraper = std::shared_ptr<heartbeat_task_wraper>;

/** �����߳�����ģ��
*/
class heartbeat_task_thread :
    public nocopyable
{
public:
    /** ���캯��
    */
    heartbeat_task_thread();

    /** ��������
    */
    ~heartbeat_task_thread();

public:
    /** ��ʼѭ��
    @return �Ƿ�ɹ�
    */
    bool start();

    /** ֹͣ��������
    */
    void stop_all();

    /** ֹͣ��ǰ������
    */
    void stop_current();

    /** ����������������ǰ�ģ�����ֹͣѭ��
    */
    void clear_all();

    /** ����������񲻰�����ǰ�ģ�����ֹͣѭ��
    */
    void clear_queue();

    /** ���һ������
    @param [in] task ����
    */
    void push_task(const sp_heartbeat_task& task);

    /** ���һ����������
    @param [in] task ����
    @param [in] timeOut ʱ����
    @param [in] times ִ�д�����Ϊ-1����ִ�������Σ�Ĭ��Ϊ-1
    */
    void push_task(const std::function<bool()>& task, uint32_t timeOut, int32_t times = -1);

    /** ��õ�ǰ�����е�������������ǰ����ִ�е�
    @return ��ǰ�����е�����
    */
    size_t get_task_count();

public:
    /** �̻߳ص�
    */
    virtual void thread_callback();

private:
    /** �߳�
     */
    std::thread* m_pThread;

    /** ������
    */
    std::recursive_mutex m_mutex;

    /** �������
    */
    std::list<sp_heartbeat_taskWraper > m_taskList;

    /** �Ƿ�ֹͣ��
    */
    bool m_stop;

    /** ��ǰ����ִ�е�
    */
    sp_heartbeat_taskWraper m_currentTask;
};

END_NSP_DDM
#endif // heartbeat_task_thread_h_
