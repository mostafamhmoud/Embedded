#ifndef TASKHANDLER_HPP
#define TASKHANDLER_HPP

#include <main.h>
#include "BaseTask.hpp"



class MenuTask : public BaseTask
{
    public:
        MenuTask();
        void run() override;

};

class PrintTask : public BaseTask
{
    public:
        PrintTask();
        void run() override;    
};


typedef struct
{
  char Payload[10];
  uint8_t len ;
}Cmd_t;
class CmdHandleTask : public BaseTask
{
    public:
        CmdHandleTask();
        void run() override;

    private:
        void ProcessCmd(Cmd_t& cmd);
        void ExtractCmd(Cmd_t& cmd);
};

class LedTask : public BaseTask
{
    public:
        LedTask();
        void run() override;
        void ledEffectAction(int action_num);

    protected:
        void ledEffectStop();
        void ledEffectStart(int action_num);

        bool handleLedCommand(Cmd_t*& cmd);
};

class RTCTask : public BaseTask
{
    public:
        RTCTask();
        void run() override;


    private:    
        RTC_TimeTypeDef Time ;
        RTC_DateTypeDef Date ;

        void handleTimeConfig();
        void handleDateConfig();
        uint8_t getUserInput(const char* message);

        uint8_t processConfigType(Cmd_t*& cmd);
        uint8_t GetNumber(Cmd_t*& cmd);

        // Time validation
        CheckValid_En processHour(uint8_t hour);
        CheckValid_En processMin(uint8_t min);
        CheckValid_En processSec(uint8_t sec);
    
        // Date validation
        CheckValid_En processDate(uint8_t date);
        CheckValid_En processMonth(uint8_t month);
        CheckValid_En processYear(uint8_t year);

        void printDateTime();

};


#endif
