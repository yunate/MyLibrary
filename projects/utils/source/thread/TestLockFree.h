#pragma once

#include "lockfree_queue.h"
#include <thread>
#include <mutex>
#include <queue>
#include <assert.h>
#include "timer_recorder/timer_recorder.h"

namespace utilstest
{
    void Test_NormalQue(int tdCount, int taskCount)
    {
        std::queue<int> que;
        std::mutex mu;
        mu.lock();

        auto ThreadCall = [&]()
        {
            // 等着进程一起开始
            mu.lock();
            mu.unlock();

            for (int i = 0; i < taskCount; ++i)
            {
                int x = i;

                if ((i & 1) == 0)
                {
                    mu.lock();
                    que.push(x);
                    mu.unlock();
                }
                else
                {
                    mu.lock();

                    if (que.size() > 0)
                    {
                        x = que.front();
                        que.pop();
                    }

                    mu.unlock();
                }
            }
        };

        std::vector<std::thread*> tds;

        for (int i = 0; i < tdCount; ++i)
        {
            tds.push_back(new std::thread(ThreadCall));
        }

        mu.unlock();

        for (int i = 0; i < (int)tds.size(); ++i)
        {
            tds[i]->join();
            delete tds[i];
        }

        tds.clear();

//         int i = 0;
//         int size = que.size();
// 
//         while (!que.empty())
//         {
//             que.pop();
//             ++i;
//         }
// 
//         // 如果每一个都指向下一个，证明线程安全
//         assert(i == size);
    }

    void Test_NormalQue1(int tdCount, int taskCount)
    {
        std::queue<int> que;
        lockfree::spin_mutex mu;
        mu.lock();

        auto ThreadCall = [&]()
        {
            // 等着进程一起开始
            mu.lock();
            mu.unlock();

            for (int i = 0; i < taskCount; ++i)
            {
                int x = i;

                if ((i & 1) == 0)
                {
                    mu.lock();
                    que.push(x);
                    mu.unlock();
                }
                else
                {
                    mu.lock();

                    if (que.size() > 0)
                    {
                        x = que.front();
                        que.pop();
                    }

                    mu.unlock();
                }
            }
        };

        std::vector<std::thread*> tds;

        for (int i = 0; i < tdCount; ++i)
        {
            tds.push_back(new std::thread(ThreadCall));
        }

        mu.unlock();

        for (int i = 0; i < (int)tds.size(); ++i)
        {
            tds[i]->join();
            delete tds[i];
        }

        tds.clear();

        //         int i = 0;
        //         int size = que.size();
        // 
        //         while (!que.empty())
        //         {
        //             que.pop();
        //             ++i;
        //         }
        // 
        //         // 如果每一个都指向下一个，证明线程安全
        //         assert(i == size);
    }

    void Test_LockFreeQue(int tdCount, int taskCount)
    {
        lockfree::lockfree_queue<int> que;
        std::mutex mu;
        mu.lock();

        auto ThreadCall = [&]()
        {
            // 等着进程一起开始
            mu.lock();
            mu.unlock();

            for (int i = 0; i < taskCount; ++i)
            {
                int x = i;

                if ((i & 1) == 0)
                {
                    que.push(x);
                }
                else
                {
                    que.pop(x);
                }
            }
        };

        std::vector<std::thread*> tds;

        for (int i = 0; i < tdCount; ++i)
        {
            tds.push_back(new std::thread(ThreadCall));
        }

        mu.unlock();

        for (int i = 0; i < (int)tds.size(); ++i)
        {
            tds[i]->join();
            delete tds[i];
        }

        tds.clear();

//         int size = lockFreeQue.Size();
//         int i = 0;
// 
//         while (1)
//         {
//             int x;
//             if (!lockFreeQue.Pop(x))
//             {
//                 break;
//             }
// 
//             ++i;
//         }
// 
//         // 如果每一个都指向下一个，证明线程安全
//         assert(i == size);
    }

    void TestSpeed()
    {
        int tdCount = 4;
        int taskCount = 40000;

        {
            TimerRecorder timer;
            Test_NormalQue(tdCount, taskCount);
            printf("Test_NormalQue:\t%lld\r\n", timer.GetTimePass());
        }

        {
            TimerRecorder timer;
            Test_LockFreeQue(tdCount, taskCount);
            printf("Test_LockFreeQue:\t%lld\r\n", timer.GetTimePass());
        }
  
        {
            TimerRecorder timer;
            Test_NormalQue1(tdCount, taskCount);
            printf("Test_NormalQue__:\t%lld\r\n", timer.GetTimePass());
        }
    }
}

