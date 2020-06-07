
#ifndef simple_task_thread_h_
#define simple_task_thread_h_ 1

#include "base/g_def.h"
#include "base/nocopyable.hpp"
#include "i_ddtask.h"

#include <mutex>
#include <functional>
#include <memory>
#include <queue>
#include <thread>

BEG_NSP_DDM
/** ǰ�����������¼���ֻsimple_task_thread��
*/
class simple_event;

/** ���߳�����ģ��
@note �е���������������ģ�ͣ�ֻ��������ֻ��һ��
*/
class simple_task_thread :
    public nocopyable
{
public:
    /** ���캯��
    */
    simple_task_thread();

    /** ��������
    */
    ~simple_task_thread();

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
    void push_task(const std::shared_ptr<i_ddtask>& task);

    /** ���һ����������
    @param [in] task ����
    */
    void push_task(const std::function<void()>& task);

    /** ��õ�ǰ�����е�������������ǰ����ִ�еģ�����0˵�����п���
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

    /** �߳��¼�
    */
    std::shared_ptr<simple_event> m_spEvent;

    /** �������
    */
    std::queue<std::shared_ptr<i_ddtask> > m_taskQue;

    /** �Ƿ�ֹͣ��
    */
    bool m_stop;

    /** ��ǰ����ִ�е�
    */
    std::shared_ptr<i_ddtask> m_currentTask;
};

END_NSP_DDM
#endif // simple_task_thread_h_
