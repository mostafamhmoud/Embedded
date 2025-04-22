#include "main.h"
#include "stm32f4xx_hal_rtc.h"
#include "TaskHandler.hpp"
#include "FreeRTOS_Timer.hpp"
#include "Queue_Wrapper.hpp"
#include "shared_resources.hpp"


#include <string.h>
#include <stdio.h>

/**
 * *********************************************
 * *******base task class function definitions *******************
 * ********************************************
 */



extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;

/**
 * *********************************************
 * *******led_on task  task class function definitions *******************
 * ********************************************
 */

//extern FreeRTOSTimer timer[4];

void callBackFunc(TimerHandle_t xtimer)
{
    uint8_t timer_id = reinterpret_cast<uintptr_t>(pvTimerGetTimerID(xtimer));

    led_task.ledEffectAction(timer_id);
}

FreeRTOSTimer timer[4] = {
	FreeRTOSTimer("timer", pdMS_TO_TICKS(1000), pdTRUE, (void*)1, callBackFunc),
	FreeRTOSTimer("timer", pdMS_TO_TICKS(1000), pdTRUE, (void*)2, callBackFunc),
	FreeRTOSTimer("timer", pdMS_TO_TICKS(1000), pdTRUE, (void*)3, callBackFunc),
	FreeRTOSTimer("timer", pdMS_TO_TICKS(1000), pdTRUE, (void*)4, callBackFunc),
};



MenuTask::MenuTask() 
: BaseTask("Menu Task" , 250 , 2){}

uint8_t task_state = 1 ;

void MenuTask::run()
{
    Cmd_t* local_cmdPtr ;
    BaseType_t local_return;
    uint32_t notif_value ;
    while (1)
    {
        Q_print.send(Messages::menu_message, portMAX_DELAY);

        /* we recieve notification value which is the address of the command */
        local_return = xTaskNotifyWait(0 , 0 , &notif_value , portMAX_DELAY);

        local_cmdPtr = reinterpret_cast<Cmd_t*>(notif_value);

        /* command length should be 1 */
        if(local_cmdPtr->len == 1)
        {
            switch(local_cmdPtr->Payload[0])
            {
                case '0' :
                    Shared::current_state = LED_EFFECT_STATE ;
                    xTaskNotify(led_task.GetTaskHandle() , 0 , eNoAction);
                    break;
                case '1' :
                    Shared::current_state = RTC_MENU_STATE ;
                    xTaskNotify(rtc_task.GetTaskHandle() , 0 , eNoAction);
                    break;
                case '2' :
                    break;
                default:
                    Q_print.send(Messages::invalid_message); continue;
            }
        }
        else
        {
            Q_print.send(Messages::invalid_message);continue;
        }

        /*wait to run again until other task notifies */
        xTaskNotifyWait(0 , 0 , NULL , portMAX_DELAY);
    } 
}

PrintTask::PrintTask()
: BaseTask("Print Task" , 250 , 2){}

void PrintTask::run()
{
    const char* local_msg;
    while (1)
    {
        Q_print.receive(local_msg , portMAX_DELAY);

        HAL_UART_Transmit(&huart2 , (uint8_t*)local_msg , strlen((char*)local_msg) , HAL_MAX_DELAY);
    }
    
}


CmdHandleTask::CmdHandleTask() 
: BaseTask("Cmd Handle Task" , 250 , 2){}

uint32_t notify_value;
void CmdHandleTask::run()
{
    BaseType_t local_return ;

    Cmd_t cmd ;
    while (1)
    {
        local_return = xTaskNotifyWait(0, 0, &notify_value , portMAX_DELAY);
        
        if(local_return == pdTRUE)
        {
              ProcessCmd(cmd);
        }
    }
}

void CmdHandleTask::ProcessCmd(Cmd_t& cmd)
{
    ExtractCmd(cmd);
    Cmd_t* cmdPtr = &cmd ;
    switch(Shared::current_state)
    {
        case MAIN_MENU_STATE:
             xTaskNotify(menu_task.GetTaskHandle() ,reinterpret_cast<uint32_t>(cmdPtr), eSetValueWithOverwrite); break;
        case LED_EFFECT_STATE:
             xTaskNotify(led_task.GetTaskHandle() ,reinterpret_cast<uint32_t>(cmdPtr), eSetValueWithOverwrite);
        	 break;
        case RTC_MENU_STATE:
        case RTC_TIME_CFG_STATE:
        case RTC_DATE_CFG_STATE:
             /*notify rtc task of the cmd */
             xTaskNotify(rtc_task.GetTaskHandle() ,reinterpret_cast<uint32_t>(cmdPtr), eSetValueWithOverwrite);
        	 break;
    }

}

void CmdHandleTask::ExtractCmd(Cmd_t& cmd)
{
    UBaseType_t local_num_messgs ;
    uint8_t local_counter ;

    local_num_messgs = Q_data.getQueueSize();

    for(local_counter = 0 ; local_counter < local_num_messgs ; local_counter++)
    {
        Q_data.receive(cmd.Payload[local_counter]);

        if(cmd.Payload[local_counter] == '\n')
        {
            break;
        }
    }

    /* put null char at the end of cmd to make it string */
    cmd.Payload[local_counter] = '\0';

    /* save len of cmd excluding null char*/
    cmd.len = local_counter ;
}


LedTask::LedTask()
: BaseTask("Led Task" , 250 , 2){}

void LedTask::run()
{
    BaseType_t local_return;
    uint32_t notif_value;
    Cmd_t* local_cmdPtr;

    while (1)
    {
    	// Wait for external trigger to enter LED task
        local_return = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        if (local_return == pdTRUE)
        {
            // Show the LED effects menu
            Q_print.send(Messages::ledEffect_message);
            // Wait for the user's command
            local_return = xTaskNotifyWait(0, 0, &notif_value, portMAX_DELAY);

            if (local_return == pdTRUE)
            {
                local_cmdPtr = reinterpret_cast<Cmd_t*>(notif_value);

                // Process the Led Command
                if (handleLedCommand(local_cmdPtr) == true)
                {
                    Q_print.send(Messages::ledEffect_success);
                }
                else
                {
                    Q_print.send(Messages::invalid_message);
                }
            }
        }
        else
        {
            // Optional: handle timeout
        }

        // Set system state back to MAIN MENU
        Shared::current_state = MAIN_MENU_STATE;
        // Return to Menu Task
        xTaskNotify(menu_task.GetTaskHandle(), 0, eNoAction);
    }

}

bool LedTask::handleLedCommand(Cmd_t*& cmd)
{
    if (cmd->len <= 4)  // Check if command length is within acceptable limits
    {
        if (strcmp(cmd->Payload, "none") == 0)
        {
            ledEffectStop();
            return true;  // Command successfully handled
        }
        else if (strcmp(cmd->Payload, "e1") == 0)
        {
            ledEffectStart(1);
            return true;  // Command successfully handled
        }
        else if (strcmp(cmd->Payload, "e2") == 0)
        {
            ledEffectStart(2);
            return true;  // Command successfully handled
        }
        else if (strcmp(cmd->Payload, "e3") == 0)
        {
            ledEffectStart(3);
            return true;  // Command successfully handled
        }
        else if (strcmp(cmd->Payload, "e4") == 0)
        {
            ledEffectStart(4);
            return true;  // Command successfully handled
        }
        else
        {
            // Invalid command
            return false;  // Invalid command, return false
        }
    }
    else
    {
        // Invalid length of the command
        return false;  // Return false if length is greater than 4
    }
}


/* stopp all timers*/
void LedTask::ledEffectStop()
{
    for(int id = 0 ; id < 4 ; id++)
    {
        timer[id].Stop();
    }
}


/* enter num from 1 > 4*/
void LedTask::ledEffectStart(int action_num)
{
    /* stop all timers */
    led_task.ledEffectStop();

    timer[action_num-1].Start();
}


void LedTask::ledEffectAction(int action_num)
{
    switch (action_num)
    {
    case 1:
        HAL_GPIO_TogglePin(LED1_PORT , LED1_PIN);
        break;
    case 2:
        HAL_GPIO_TogglePin(LED2_PORT , LED2_PIN);
        break;
    case 3:
        HAL_GPIO_TogglePin(LED3_PORT , LED3_PIN);
        break;
    case 4:
        HAL_GPIO_TogglePin(LED4_PORT , LED4_PIN);
        break;
    default:
        break;
    }
}


/**
* *********************************************
* *******RTC task class function definitions *******************
* ********************************************
*/


RTCTask::RTCTask()
: BaseTask("RTC Task" , 250 , 2){}

void RTCTask::run()
{
    BaseType_t local_return;
    uint32_t notif_value;
    Cmd_t* local_cmdPtr;

   while (1)
   {
       /* wait for entering the rtc menu */
       xTaskNotifyWait(0 , 0 , NULL , portMAX_DELAY);
       Q_print.send(Messages::rtcMenu_message);
       
       /* wait for user to enter config type ( time , date , exit )*/
       local_return = xTaskNotifyWait(0, 0, &notif_value, portMAX_DELAY);
       local_cmdPtr = reinterpret_cast<Cmd_t*>(notif_value);

       /*  process config type */
       uint8_t configTypeReturn = processConfigType(local_cmdPtr);

       if(configTypeReturn == CONFIG_TIME)
       {
            handleTimeConfig();
       }

       else if(configTypeReturn == CONFIG_DATE)
       {
            handleDateConfig();
       }
       else if(configTypeReturn == EXIT)
       {
            /* Do Nothing */
       }
       
       else
       {
            Q_print.send(Messages::invalid_message);
       }

        // Set system state back to MAIN MENU
        Shared::current_state = MAIN_MENU_STATE;
        // Return to Menu Task
        xTaskNotify(menu_task.GetTaskHandle(), 0, eNoAction);
   }

}

void RTCTask::handleTimeConfig()
{
    Shared::current_state = RTC_TIME_CFG_STATE;

    uint8_t hour = getUserInput(Messages::rtcEnterHour_message);
    uint8_t min  = getUserInput(Messages::rtcEnterMinute_message);
    uint8_t sec  = getUserInput(Messages::rtcEnterSecond_message);

    if (processHour(hour) == VALID && processMin(min) == VALID && processSec(sec) == VALID)
    {
        Time.Hours   = hour;
        Time.Minutes = min;
        Time.Seconds = sec;

        HAL_RTC_SetTime(&hrtc, &Time, RTC_FORMAT_BIN) ;

        Q_print.send(Messages::time_config_success);

        printDateTime();

    }
    else
    {
        Q_print.send(Messages::invalid_message);
    }
}

void RTCTask::handleDateConfig()
{
    Shared::current_state = RTC_DATE_CFG_STATE;

    uint8_t date  = getUserInput(Messages::rtcEnterDay_message);
    uint8_t month = getUserInput(Messages::rtcEnterMonth_message);
    uint8_t year  = getUserInput(Messages::rtcEnterYear_message);

    if (processDate(date) == VALID && processMonth(month) == VALID && processYear(year) == VALID)
    {
        Date.Date  = date;
        Date.Month = month;
        Date.Year  = year;

        HAL_RTC_SetDate(&hrtc, &Date, RTC_FORMAT_BIN);

        Q_print.send(Messages::date_config_success);

        printDateTime();
    }
    else
    {
        Q_print.send(Messages::invalid_message);
    }
}

uint8_t RTCTask::getUserInput(const char* message)
{
    Q_print.send(message);
    uint32_t notif_value;
    xTaskNotifyWait(0, 0, &notif_value, portMAX_DELAY);
    Cmd_t* local_cmdPtr = reinterpret_cast<Cmd_t*>(notif_value);
    return GetNumber(local_cmdPtr);
}




uint8_t RTCTask::processConfigType(Cmd_t*& cmd)
{
    if(cmd->len == 1)
    {
        switch(cmd->Payload[0])
        {
            case '0' :
                return CONFIG_TIME ;
                break;
            case '1' :
                return CONFIG_DATE ;
                break;
            case '2' :
                return EXIT ;
                break;
            default:
                return NONE ;
        }
    }
    else
    {
        return NONE ;
    }
}

uint8_t RTCTask::GetNumber(Cmd_t*& cmd)
{
    if(cmd->len == 2)
    {
        return (((cmd->Payload[0] - '0')*10) + (cmd->Payload[1] - '0'));
    }
    else if(cmd->len == 1)
    {
        return (cmd->Payload[0] - '0');
    }

    return NONE ;
}


CheckValid_En RTCTask::processHour(uint8_t hour)
{
    if (hour >= 0 && hour <= 23)
    {
        return VALID;
    }
    return INVALID;
}

CheckValid_En RTCTask::processMin(uint8_t min)
{
    if (min >= 0 && min <= 59)
    {
        return VALID;
    }
    return INVALID;
}

CheckValid_En RTCTask::processSec(uint8_t sec)
{
    if (sec >= 0 && sec <= 59)
    {
        return VALID;
    }
    return INVALID;
}


CheckValid_En RTCTask::processDate(uint8_t date)
{
    if (date >= 1 && date <= 31)
    {
        return VALID;
    }
    else
    {
        return INVALID;
    }
}

CheckValid_En RTCTask::processMonth(uint8_t month)
{
    if (month >= 1 && month <= 12)
    {
        return VALID;
    }
    else
    {
        return INVALID;
    }
}

CheckValid_En RTCTask::processYear(uint8_t year)
{
    if (year <= 99)  // Assuming two-digit year (e.g., 24 for 2024)
    {
        return VALID;
    }
    else
    {
        return INVALID;
    }
}



void RTCTask::printDateTime()
{
    static char buffer[50];

    snprintf(buffer, sizeof(buffer),
             "Time: %02d:%02d:%02d | Date: %02d-%02d-20%02d",
             Time.Hours, Time.Minutes, Time.Seconds,
             Date.Date, Date.Month, Date.Year);

    const char* temp = buffer;
    Q_print.send(temp);
}









