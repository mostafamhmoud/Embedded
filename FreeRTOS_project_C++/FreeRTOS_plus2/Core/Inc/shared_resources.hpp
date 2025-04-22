#ifndef SHARED_RESOURCES_HPP
#define SHARED_RESOURCES_HPP

#include "Queue_Wrapper.hpp"
#include "TaskHandler.hpp"

namespace Messages {
    // Menu messages
    extern const char* menu_message;
    extern const char* ledEffect_message;
    extern const char* rtcMenu_message;
    extern const char* rtcOptions_message;

    extern const char* rtcEnterHour_message   ;
    extern const char* rtcEnterMinute_message ;
    extern const char* rtcEnterSecond_message ;
 
    extern const char* rtcEnterDay_message    ;
    extern const char* rtcEnterMonth_message  ;
    extern const char* rtcEnterYear_message   ;

    extern const char* invalid_message;
    extern const char* ledEffect_success;
    extern const char* time_config_success;
    extern const char* date_config_success;
}

namespace Shared {
    extern State_t current_state;
}


// Declare the queues as shared resources
extern Queue<const char*> Q_print;    // Queue for printing messages
extern Queue<char> Q_data;            // Queue for data

// Declare the task objects as shared resources
extern MenuTask menu_task;            // Menu task
extern PrintTask print_task;          // Print task
extern CmdHandleTask cmd_handle_task; // Command handling task
extern LedTask led_task;              // LED task
extern RTCTask rtc_task;


#define CONFIG_TIME    0    
#define CONFIG_DATE    1
#define EXIT           2  

#define NONE           11


#endif // SHARED_RESOURCES_HPP
