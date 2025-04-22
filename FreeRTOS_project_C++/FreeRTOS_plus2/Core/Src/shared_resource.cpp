#include "main.h"
#include "shared_resources.hpp"
#include "TaskHandler.hpp"
#include "Queue_Wrapper.hpp"
#include "FreeRTOS_Timer.hpp"


namespace Messages {
    // Menu messages
    const char* menu_message =
        "====================\n"
        "            menu         \n"
        "====================\n"
        "led effect             ----> 0\n"
        "Date and time           ----> 1\n"
        "exit                  ----> 2\n"
        "Enter your choice here:   \n";

    const char* ledEffect_message =
        "===================================\n"
        "              Led effect           \n"
        "===================================\n"
        "(none , e1 , e2 , e3 , e4)\n"
        "Enter your choice here:   \n";

    // RTC messages
    const char* rtcMenu_message =
        "====================\n"
        "            RTC         \n"
        "====================\n"
        "Configure Time                  ----> 0\n"
        "Configure Date                  ----> 1\n"
        "Enable reporting                ----> 2\n"
        "Exit                            ----> 3\n"
        "Enter your choice here:  \n";

    const char* rtcEnterHour_message   = "Enter hours (0-23): \n";
    const char* rtcEnterMinute_message = "Enter minutes (0-59): \n";
    const char* rtcEnterSecond_message = "Enter seconds (0-59): \n";

    
    const char* rtcEnterDay_message    = "Enter day (1-31): \n";
    const char* rtcEnterMonth_message  = "Enter month (1-12): \n";
    const char* rtcEnterYear_message   = "Enter year (e.g., 2025): \n";    

    const char* invalid_message =
        "===================================\n"
        "    !!!!!  Invalid Message !!!!         \n"
        "===================================\n";

    // Success messages
    const char* ledEffect_success =
        "===================================\n"
        "  ✅ LED effect applied successfully\n"
        "===================================\n";

    const char* time_config_success =
        "===================================\n"
        "   ✅ Time configured successfully\n"
        "===================================\n";

    const char* date_config_success =
        "===================================\n"
        "   ✅ Date configured successfully\n"
        "===================================\n";

    const char* reporting_enabled_success =
        "===========================================\n"
        " ✅ RTC reporting enabled successfully\n"
        "===========================================\n";

    const char* task_start_success =
        "=======================================\n"
        "    ✅ Task started successfully\n"
        "=======================================\n";

    const char* general_success =
        "===========================================\n"
        "  ✅ Operation completed successfully\n"
        "===========================================\n";

}


namespace Shared {
    State_t current_state = MAIN_MENU_STATE;
}


// Define the queues (define size as per your needs)
Queue<const char*> Q_print(10);  // Queue with a size of 10 for printing messages
Queue<char> Q_data(10);          // Queue with a size of 10 for data

// Define the task objects
MenuTask menu_task;              // Task object for MenuTask
PrintTask print_task;            // Task object for PrintTask
CmdHandleTask cmd_handle_task;   // Task object for CmdHandleTask
LedTask led_task;                // Task object for LedTask
RTCTask rtc_task;

  





