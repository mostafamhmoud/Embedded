#include "main.h"


void RTC_ShowTimeDate(void)
{
    RTC_DateTypeDef local_RTCdate ;
    RTC_TimeTypeDef local_RTCtime ;

    static char ShowTime[50];
    static char ShowDate[50];

    char* local_pTime = ShowTime;
    char* local_pDate = ShowDate;

    char* local_TimeFormat;

    (void)HAL_RTC_GetTime(&hrtc , &local_RTCtime , RTC_FORMAT_BIN);

    (void)HAL_RTC_GetDate(&hrtc , &local_RTCdate , RTC_FORMAT_BIN);

    /* prapare the format */
    if(local_RTCtime.TimeFormat == RTC_HOURFORMAT12_AM)
    {
        local_TimeFormat = "AM";
    }
    else
    {
        local_TimeFormat = "PM";
    }

    /*convert the time format into formatted string : HH:MM:SS*/
    sprintf((char*)ShowTime , "%s: \t%02d : %02d : %02d [%s]" , "\nCurrent Time & Date" ,
            local_RTCtime.Hours , local_RTCtime.Minutes , local_RTCtime.Seconds , local_TimeFormat);
    
    /*print the current time */
    xQueueSend(Q_print , &local_pTime , portMAX_DELAY);  
    
    
    /*convert the Date format into formatted string : Day-Month-Year*/
    (void)sprintf((char*)ShowDate , " \t%02d : %02d : %02d " ,
    		      local_RTCdate.Date , local_RTCdate.Month , (2000 + local_RTCdate.Year));
    
    /*print the current Date */
    (void)xQueueSend(Q_print , &local_pDate , portMAX_DELAY);     

}

void RTC_ConfigTime(uint8_t hours , uint8_t min , uint8_t sec)
{
    RTC_TimeTypeDef local_RTCTime;

    local_RTCTime.Hours = hours ;
    local_RTCTime.Minutes = min ;
    local_RTCTime.Seconds = sec ;

    HAL_RTC_SetTime(&hrtc , &local_RTCTime , RTC_FORMAT_BIN);
}

void RTC_ConfigDate(uint8_t day , uint8_t month , uint8_t year)
{
    RTC_DateTypeDef local_RTCDate;

    local_RTCDate.Date = day ;
    local_RTCDate.Month = month ;
    local_RTCDate.Year = year ;

    HAL_RTC_SetDate(&hrtc , &local_RTCDate , RTC_FORMAT_BIN);
}

uint8_t RTC_ValidateRTCTimeConfig(uint8_t hour , uint8_t min , uint8_t sec)
{
    uint8_t LocalValidateState;

    if((hour > 12) || (min > 59) || (sec > 59))
    {
        LocalValidateState = 0 ;
    }
    else
    {
        LocalValidateState = 1 ;
    }

    return LocalValidateState ;
}

uint8_t RTC_ValidateRTCDateConfig(uint8_t day , uint8_t month , uint8_t Year)
{
    uint8_t LocalValidateState;

    if((day > 31) || (month > 12) || (Year > 99))
    {
        LocalValidateState = 0 ;
    }
    else
    {
        LocalValidateState = 1 ;
    }

    return LocalValidateState ;
}
