#pragma once

#include "LockFreeQueue.h"
#include <thread>
#include <mutex>
#include <assert.h>
namespace utilstest
{
    void Test_LockFreeQue()
    {
        LockFreeQueue<int> lockFreeQue;
        std::mutex mu;
        mu.lock();
        auto ThreadCall = [&]()
        {
            // 等着进程一起开始
            mu.lock();
            mu.unlock();

            for (int i = 0; i < 2500; ++i)
            {
                lockFreeQue.Push(1);
                lockFreeQue.Push(1);
                lockFreeQue.Push(1);
                lockFreeQue.Push(1);
            }
        };

        std::thread trd1(ThreadCall);
        std::thread trd2(ThreadCall);
        std::thread trd3(ThreadCall);
        std::thread trd4(ThreadCall);
        std::thread trd5(ThreadCall);
        std::thread trd6(ThreadCall);
        std::thread trd7(ThreadCall);
        std::thread trd8(ThreadCall);
        mu.unlock();

        trd1.join();
        trd2.join();
        trd3.join();
        trd4.join();
        trd5.join();
        trd6.join();
        trd7.join();
        trd8.join();

        int i = 0;

        while (1)
        {
            int x;
            if (!lockFreeQue.Pop(x))
            {
                break;
            }

            ++i;
        }

        // 如果每一个都指向下一个，证明线程安全
        assert(i == 80000);
    }
}

