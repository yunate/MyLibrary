#pragma once

#include "SimpleTaskThread.h"
#include "ITask.h"

class TestTaskQue
{
public:
    TestTaskQue() {}
    ~TestTaskQue() {}

    void Do()
    {
        m_simpleTaskQue.Start();
        ::Sleep(1000);
    }
public:
private:
    SimpleTaskThread m_simpleTaskQue;
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
        SimpleTaskThread simpleTaskQue;
        simpleTaskQue.Start();

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

