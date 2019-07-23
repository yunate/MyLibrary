#pragma once

#include "timer_recorder.h"

namespace utilstest
{
    void Test_TimerRecorder()
    {
        TimerRecorder timer;

        for (size_t i = 0; i < 10000; ++i)
        {
            // do something
        }

        timer.GetTimePass();
    }
}
