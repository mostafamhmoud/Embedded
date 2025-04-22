#include "main.h"
#include "FreeRTOS_Timer.hpp"


FreeRTOSTimer::FreeRTOSTimer(const char* name, TickType_t period_ticks, UBaseType_t auto_reload, void* timer_id, TimerCallbackFunction_t callback)
{
    timerHandle = xTimerCreate(
        name,
        period_ticks,
        auto_reload,
        timer_id,
        callback
    );
}

bool FreeRTOSTimer::Start(TickType_t block_time)
{
    return xTimerStart(timerHandle, block_time) == pdPASS;
}

bool FreeRTOSTimer::Stop(TickType_t block_time)
{
    return xTimerStop(timerHandle, block_time) == pdPASS;
}

TimerHandle_t FreeRTOSTimer::GetHandle() const
{
    return timerHandle;
}
