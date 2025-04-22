#ifndef FREERTOS_TIMER_HPP
#define FREERTOS_TIMER_HPP

#include "main.h"

class FreeRTOSTimer
{
    public:
        typedef void(*callbackFun_t)(void* arg);
        FreeRTOSTimer(const char* name, TickType_t period_ticks, UBaseType_t auto_reload, void* timer_id, TimerCallbackFunction_t callback);


        bool Start(TickType_t block_time = 0);
        bool Stop(TickType_t block_time = 0);
        bool Delete(TickType_t block_time = 0);
        TimerHandle_t GetHandle() const;  

    private:
        TimerHandle_t timerHandle;    
};



#endif // FREERTOS_TIMER_HPP