

#include "thread/thread_manager/simple_thread_manager.h"
#include "test_case_factory.h"
#include <iostream>
#include <atomic>
BEG_NSP_DDM

TEST(test_thread, simple_thread_manager)
{
    std::atomic_int count = 0;
    simple_thread_manager threadManager;
    threadManager.push_block_task([&count]() {
        //::Sleep(1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout << "push_block_task" << std::endl;
        ++count;
        return true;
    });

    threadManager.push_fast_task([&count]() {
        std::cout << "push_fast_task" << std::endl;
        ++count;
        return true;
    });

    threadManager.push_heartbeat_task([&count]() {
        std::cout << "push_heartbeat_task" << std::endl;
        ++count;
        return true;
    }, 1000, 3);

    while (true)
    {
        if (count == 5) {
            break;
        }

        // ::Sleep(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

END_NSP_DDM

