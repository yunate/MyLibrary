#pragma once

#include "SimpleTaskQueue.h"
#include "ISimpleTask.h"

enum TaskEnum
{
    TE_1 = 0,
    TE_2,
    TE_3
};

class Task :
    public ISimpleTask
{
public:
    Task(const std::function<void(int)>& callback) :
        ISimpleTask(callback)
    {

    }

    virtual ~Task()
    {

    }

    /** 执行任务
    */
    virtual void DoTask()
    {
        CallBack(TE_1);
        CallBack(TE_2);
    }

    /** 停止任务
    */
    virtual void Stop()
    {
        CallBack(TE_3);
    }
};


class TestTaskQue
{
public:
    TestTaskQue() {}
    ~TestTaskQue() {}

    void Do()
    {
        m_simpleTaskQue.Start();
        ::Sleep(1000);

        {
            std::shared_ptr <ITask> ta(new Task(nullptr));
            m_simpleTaskQue.PushTask(std::move(ta));
        }
        

        {
            std::shared_ptr <ITask> ta(new Task([this](int ty)
            {
                this->Callback((TaskEnum)ty);
            }));
            m_simpleTaskQue.PushTask(std::move(ta));
        }

        {
            std::shared_ptr <ITask> ta(new Task([this](int ty)
            {
                this->Callback1((TaskEnum)ty);
            }));
            m_simpleTaskQue.PushTask(std::move(ta));
        }

    }

public:
    void Callback(TaskEnum ty)
    {
        switch (ty)
        {
        case TE_1:
            {
                int i = 0;
                ++i;
                break;
            }
        case TE_2:
            {
                int i = 0;
                ++i;
                break;
            }
        case TE_3:
            {
                int i = 0;
                ++i;
                break;
            }
        default:
            break;
        }
    }

    void Callback1(TaskEnum ty)
    {
        switch (ty)
        {
        case TE_1:
            {
                break;
            }
        case TE_2:
            {
                break;
            }
        case TE_3:
            {
                break;
            }
        default:
            break;
        }
    }
private:
    SimpleTaskQueue m_simpleTaskQue;
};

namespace utilstest
{
    void Test_taskQue()
    {
        TestTaskQue taskQue;
        taskQue.Do();

        while (true)
        {
            ::Sleep(1);
        }
    }

    void Test_taskQue1()
    {
        SimpleTaskQueue simpleTaskQue;
        simpleTaskQue.Start();

        ::Sleep(1000);

        bool ret = false;
        int t1 = 0;
        int t2 = 0;

        simpleTaskQue.PushTask([&]()
        {
            t1 = 1;
            t2 = 2;
            ret = true;
        });

        while (true)
        {
            ::Sleep(1);
        }
    }
}

