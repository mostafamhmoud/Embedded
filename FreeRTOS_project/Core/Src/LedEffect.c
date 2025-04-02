

#include "main.h"

GPIO_TypeDef * LEDPort[4] = {LED1_PORT , LED2_PORT , LED3_PORT , LED4_PORT};

uint16_t LEDPin[4] = {LED1_PIN , LED2_PIN , LED3_PIN , LED4_PIN};

static void LedControl(uint8_t led_num);
static void TurnOnEvenLeds(void);
static void TurnOnOddLeds(void);


void LedEffectStop(void)
{
    uint8_t local_counter ;

    /* stop all timers , this  stops all led effects */
    for(local_counter = 0 ; local_counter < 4 ; local_counter++)
    {
        xTimerStop(handle_led_timer[local_counter] , portMAX_DELAY);
    }
}


void LedEffectStart(uint8_t effect_num)
{
    /* stop all sw timers at begining */
    LedEffectStop();

    xTimerStart(handle_led_timer[effect_num-1] , portMAX_DELAY);
}

void LedEffectAction1(void)
{
    uint8_t local_counter ;
    /* toggle all leds */
    for(local_counter = 0 ; local_counter < 4 ; local_counter ++)
    {
        HAL_GPIO_TogglePin(LEDPort[local_counter] , LEDPin[local_counter]);
    }

}
void LedEffectAction2(void)
{
    static uint8_t local_flag = 0 ;
    
    if(local_flag == 0)
    {
        TurnOnEvenLeds();
    }
    else
    {
        TurnOnOddLeds();
    }

    local_flag ^= 1 ;
}
void LedEffectAction3(void)
{   
    /* shift left */
    static uint8_t local_led_num = 0 ;

    LedControl(1 << local_led_num);

    local_led_num++;
    local_led_num %= 4 ;
}
void LedEffectAction4(void)
{   
    /* shift right */
    static uint8_t local_led_num = 0 ;

    LedControl(8 >> local_led_num);

    local_led_num++;
    local_led_num %= 4 ;
}

static void TurnOnEvenLeds(void)
{
    HAL_GPIO_WritePin(LED1_PORT , LED1_PIN , GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED2_PORT , LED2_PIN , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_PORT , LED3_PIN , GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED4_PORT , LED4_PIN , GPIO_PIN_RESET);
    
}

static void TurnOnOddLeds(void)
{
    HAL_GPIO_WritePin(LED1_PORT , LED1_PIN , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_PORT , LED2_PIN , GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED3_PORT , LED3_PIN , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED4_PORT , LED4_PIN , GPIO_PIN_SET);
    
}


static void LedControl(uint8_t led_num)
{
    uint8_t local_counter ; 

    for(local_counter = 0 ; local_counter < 4 ; local_counter++)
    {
        HAL_GPIO_WritePin(LEDPort[local_counter] , LEDPin[local_counter] , ((led_num >> local_counter) & 1));
    }
}
