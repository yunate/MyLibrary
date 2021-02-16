
#ifndef __TIMER_RECORDER_H_
#define __TIMER_RECORDER_H_

#include "base/g_def.h"
#include <chrono>

BEG_NSP_DDM

// ƒ…√Î
class xtimer
{
public:
    xtimer()
    {
        reset();
    }

    ~xtimer() = default;

    inline u64 now()
    {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

    void reset()
    {
        m_epoch = now();
    }

    u64 get_time_pass()
    {
        return now() - m_epoch;
    }

private:
    //  ±º‰¥¡
    u64 m_epoch = 0;
};

END_NSP_DDM
#endif //__TIMER_RECORDER_H_
