
#include "main.h"

#define HH_STATE        0
#define MM_STATE        1
#define SS_STATE        3

#define DAY_STATE       0
#define MONTH_STATE     1
#define YEAR_STATE      3
 


static void ProcessCmd(Cmd_t* cmd);
static void ExtractCmd(Cmd_t* cmd);
static uint8_t Get_Number(const char* Ascii_Num , uint8_t Len);

const char * invalid_msg = "!!!!!! nvalid MSG !!!!!!! \r\n";


void MenuTask(void* parameter)
{
  Cmd_t* local_cmd;
  uint32_t local_cmd_address ;

  const char *menu_msg =    "====================\n"
                             "            menu         \n"   
                             "====================\n"  
                             "led effect             ----> 0\n"
		                         "Date and time           ----> 1\n"
		                         "exit                  ----> 2\n"
		                         "Enter your choice here:   ";
  //const char *menu_msg = "-led effect  -> 0 \n- ";

  
  while (1)
  {
    xQueueSend(Q_print , (void*)&menu_msg ,portMAX_DELAY);

    /* we recieve notification value which is the address of the command */
    xTaskNotifyWait(0 , 0 , &local_cmd_address , portMAX_DELAY);

    local_cmd = (Cmd_t*)local_cmd_address;

    /* command length should be 1 */
    if(local_cmd->len  == 1)
    {
      switch (local_cmd->Payload[0])
      {
      case '0':  current_state = LED_EFFECT_STATE ; xTaskNotify(handle_led_task , 0 , eNoAction); break;
      case '1':  current_state = RTC_MENU_STATE ; xTaskNotify(handle_rtc_task , 0 , eNoAction); break;
      case '2':  break;
      default : xQueueSend(Q_print , (void*)&invalid_msg, portMAX_DELAY); continue;
      }
    }
    else
    {
      /* invalid entry */
      xQueueSend(Q_print , (void*)&invalid_msg, portMAX_DELAY); continue;
    }

  }

  xTaskNotifyWait(0 , 0 , NULL , portMAX_DELAY);
  
}
void PrintTask(void* parameter)
{
  uint32_t* local_msg;
  while (1)
  {
    xQueueReceive(Q_print , &local_msg , portMAX_DELAY);
    HAL_UART_Transmit(&huart2 , (uint8_t*)local_msg , strlen((char*)local_msg) , HAL_MAX_DELAY);
  }
  
}
void RtcTask(void* parameter)
{
  const char* MsgRTC1 =    "====================\n"
                           "            RTC         \n"   
                           "====================\n" ;
                           
   const char* MsgRTC2 =       
                         "\nConfigure Time                  ----> 0\n"
                         "Configure Date                    ----> 1\n"
                         "Enable reporting                  ----> 2\n"
                         "Exit                              ----> 3\n"
                         "Enter your choice here:  ";

const char* MsgRTCHourConfig = "Enter Hours(1 - 12): ";     
const char* MsgRTCMinuteConfig = "Enter Minutes (0 - 59): "; 
const char* MsgRTCSecondsConfig = "Enter Seconds (0 - 59): "; 

const char* MsgRTCDayConfig = "Enter Day (1 - 31): ";  
const char* MsgRTCMonConfig = "Enter Mon (1 - 12): ";  
const char* MsgRTCYearConfig = "Enter Year (0 - 99): ";  

const char* MsgRTCConfigSuccess = "Configuration successful\n";
const char* MsgRTCConfigEnableReporting = "Enable Time date reporting(y/n)\n";

Cmd_t* local_cmd;
uint32_t local_cmd_address;
static uint8_t local_RTCCFGState = 0 ;

uint8_t local_hour , local_min , local_sec ;
uint8_t local_day , local_month , local_year ;
  while (1)
  {
    /* notify wait (wait till someone notify)*/
    xTaskNotifyWait(0 , 0 , NULL , portMAX_DELAY);

    /*print the menu , show current date and time info*/
    xQueueSend(Q_print , &MsgRTC1 , portMAX_DELAY);
    RTC_ShowTimeDate();
    xQueueSend(Q_print , &MsgRTC2 , portMAX_DELAY);

    /* wait for command notification*/
    xTaskNotifyWait(0 , 0 , &local_cmd_address , portMAX_DELAY);
    local_cmd = (Cmd_t*)local_cmd_address;

    /*loop until main menu state is invoked */
  while (current_state != MAIN_MENU_STATE)
  {
	  /* wait for command notification from command handle task */
	  xTaskNotifyWait(0 , 0 , &local_cmd_address , portMAX_DELAY);
    /*switch on the current state*/
    switch (current_state)
    {

          case RTC_MENU_STATE:
          if(local_cmd->len == 1)
          {
            switch(local_cmd->Payload[0])
            {
              case '0': current_state = RTC_TIME_CFG_STATE ; xQueueSend(Q_print , &MsgRTCHourConfig , HAL_MAX_DELAY);break;
              case '1': current_state = RTC_DATE_CFG_STATE ; xQueueSend(Q_print , &MsgRTCDayConfig , HAL_MAX_DELAY);break;
              case '2': current_state = RTC_REPORT_STATE ;   xQueueSend(Q_print , &MsgRTCConfigEnableReporting , HAL_MAX_DELAY);break;
              case '3': current_state = MAIN_MENU_STATE ; break;
              default :current_state = MAIN_MENU_STATE; xQueueSend(Q_print , &invalid_msg , portMAX_DELAY);break;
            }

          }
          else
          {
            current_state = MAIN_MENU_STATE; xQueueSend(Q_print , &invalid_msg , portMAX_DELAY);break;
          }
          break;
        case RTC_TIME_CFG_STATE: 
          /* get HH , MM , SS info and configure RtC*/
          /*take case of invalid entry */
        if(local_cmd->len <= 2)
        {
          switch (local_RTCCFGState)
          {
              case HH_STATE:
              local_hour = Get_Number((char*)local_cmd->Payload , local_cmd->len);
              xQueueSend(Q_print , &MsgRTCMinuteConfig , portMAX_DELAY);
              local_RTCCFGState = MM_STATE ;
              break;

              case MM_STATE:
              local_min = Get_Number((char*)local_cmd->Payload , local_cmd->len);
              xQueueSend(Q_print , &MsgRTCSecondsConfig , portMAX_DELAY);
              local_RTCCFGState = SS_STATE ;
              break;

              case SS_STATE :
              local_sec = Get_Number((char*)local_cmd->Payload , local_cmd->len);
              if(RTC_ValidateRTCTimeConfig(local_hour , local_min , local_sec))
              {
                /* valid inputs */
                RTC_ConfigTime(local_hour , local_min , local_sec);
                xQueueSend(Q_print , &MsgRTCConfigSuccess , portMAX_DELAY);
                RTC_ShowTimeDate();
              }
              else
              {
                xQueueSend(Q_print , &invalid_msg , portMAX_DELAY);break;
              }
              current_state = MAIN_MENU_STATE;
              local_RTCCFGState = 0 ;
              break;
          }
        }
        else
        {
          current_state = MAIN_MENU_STATE; xQueueSend(Q_print , &invalid_msg , portMAX_DELAY);break;
        }
        break;

   
        case RTC_DATE_CFG_STATE: 
          /* get Day , Month , year info and configure RtC*/
          /*take case of invalid entry */
        if(local_cmd->len <= 2)
        {
          switch (local_RTCCFGState)
          {
              case DAY_STATE:
              local_day = Get_Number((char*)local_cmd->Payload , local_cmd->len);
              xQueueSend(Q_print , &MsgRTCDayConfig , portMAX_DELAY);
              local_RTCCFGState = MONTH_STATE ;
              break;

              case MONTH_STATE:
              local_month = Get_Number((char*)local_cmd->Payload , local_cmd->len);
              xQueueSend(Q_print , &MsgRTCMonConfig , portMAX_DELAY);
              local_RTCCFGState = YEAR_STATE ;
              break;

              case YEAR_STATE :
              local_year = Get_Number((char*)local_cmd->Payload , local_cmd->len);
              if(RTC_ValidateRTCDateConfig(local_day , local_month , local_year))
              {
                /* valid inputs */
                RTC_ConfigDate(local_day , local_month , local_year);
                xQueueSend(Q_print , &MsgRTCConfigSuccess , portMAX_DELAY);
                RTC_ShowTimeDate();
              }
              else
              {
                xQueueSend(Q_print , &invalid_msg , portMAX_DELAY);break;
              }
              current_state = MAIN_MENU_STATE;
              local_RTCCFGState = 0 ;
              break;
          }
        }
        else
        {
          current_state = MAIN_MENU_STATE; xQueueSend(Q_print , &invalid_msg , portMAX_DELAY);break;
        }
        break;      
    }
  }

  xTaskNotify(handle_menu_task , 0 , eNoAction);

    /*case rtc menu state : process rtc menu commands */
  }
  
}

static uint8_t Get_Number(const char* Ascii_Num , uint8_t Len)
{
  uint8_t LocalDecNum ;
  if(Len == 0)
  {
    LocalDecNum = ((Ascii_Num[0] - '0') * 10) + (Ascii_Num[1] - '0');
  }
  else
  {
    LocalDecNum = Ascii_Num[0] - '0';
  }

  return LocalDecNum ;
}

void LedTask(void* parameter)
{
   Cmd_t* local_cmd;
  uint32_t local_cmd_address ;

  const char *led_msg = "===================================\n" 
                        "              Led effect           "
                        "===================================\n"
                        "(none , e1 , e2 , e3 , e4)\n"
                        "Enter your choice here:   " ;

  while (1)
  {
    /* wait for notification */
    xTaskNotifyWait(0 , 0 , NULL , portMAX_DELAY);

    /*print led menu */
    xQueueSend(Q_data , &led_msg , portMAX_DELAY);

    /*wait for command */
    xTaskNotifyWait(0 , 0 , &local_cmd_address , portMAX_DELAY);
    
    local_cmd = (Cmd_t*)local_cmd_address;

    /* command len should be less than or equal to 4 */
    if(local_cmd->len <= 4)
    {
      if(strcmp((char*)local_cmd->Payload , "none") == 0)
      {
        LedEffectStop();
      }
      else if(strcmp((char*)local_cmd->Payload , "e1") == 0)
      {
        LedEffectStart(1);
      }
      else if(strcmp((char*)local_cmd->Payload , "e2") == 0)
      {
        LedEffectStart(2);
      }
      else if(strcmp((char*)local_cmd->Payload , "e3") == 0)
      {
        LedEffectStart(3);
      }
      else if(strcmp((char*)local_cmd->Payload , "e4") == 0)
      {
        LedEffectStart(4);
      }
    }  
    
    else
    {
      /* invalid entry */
      xQueueSend(Q_print , (void*)&invalid_msg, portMAX_DELAY); continue;
    }

    /* update the state variable */
    current_state = MAIN_MENU_STATE ;

    xTaskNotify(handle_menu_task , 0 , eNoAction);
  }
  
}


void CmdHandleTask(void* parameter)
{
  BaseType_t local_return ;

  Cmd_t cmd ;
  while (1)
  {
    local_return = xTaskNotifyWait(0 , 0 , NULL , portMAX_DELAY);

    if(local_return == pdTRUE)
    {
      ProcessCmd(&cmd);
    }
  }
  
}

static void ProcessCmd(Cmd_t* cmd)
{
  ExtractCmd(cmd);

  switch (current_state)
  {
    case MAIN_MENU_STATE:
         xTaskNotify(handle_menu_task , (uint32_t)cmd , eSetValueWithOverwrite); break;
    case LED_EFFECT_STATE:
         xTaskNotify(handle_led_task , (uint32_t)cmd , eSetValueWithOverwrite); break;
    case RTC_MENU_STATE:
    case RTC_TIME_CFG_STATE:
    case RTC_DATE_CFG_STATE:
         /*notify rtc task of the cmd */
         xTaskNotify(handle_rtc_task , (uint32_t)cmd , eSetValueWithOverwrite); break;

  }

}

static void ExtractCmd(Cmd_t* cmd)
{
  UBaseType_t local_num_messgs ;
  uint8_t local_counter ;

  local_num_messgs = uxQueueMessagesWaiting(Q_data);

  for(local_counter = 0u ; local_counter < local_num_messgs ; local_counter++)
  {
    xQueueReceive(Q_data , (void*)&cmd->Payload[local_counter] , 0);

    if((char)cmd->Payload[local_counter] == '\n')
    {
      break;
    }
  }

  /* put null char at the end of cmd to make it string */
  cmd->Payload[local_counter] = '\0';

  /* save len of cmd excluding null char*/
  cmd->len = local_counter ;
}
