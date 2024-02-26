//
// Created by zysko on 25.02.2024.
//

#ifndef TIMER_H
#define TIMER_H
#include "raylib.h"

struct Timer
{
    float lifetime;
};

inline void SetTimer(Timer* timer, float life_time)
{
    if(!timer)
        return;
    timer->lifetime = life_time;
}

inline void UpdateTimer(Timer* timer)
{
    if(!timer)
        return;
    if(timer->lifetime == 0)
        return;
    timer->lifetime -= GetFrameTime();
}

inline bool TimerDone(Timer* timer)
{
    if(timer)
        return timer->lifetime <= 0;
}
#endif //TIMER_H
