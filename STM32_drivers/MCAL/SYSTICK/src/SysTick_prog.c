
#include <stdint.h>
#include "../../../Common/Stm32F446xx.h"
#include "../inc/SysTick_interface.h"


/* this functions work for SYSCLK with 16MHZ internal clock */
uint8_t SysTick_Delay_us(uint16_t time_us)
{
	CLEAR_BIT(SYSTICK->CTRL, ENABLE);  /* make sure timer is OFF */
	SYSTICK->LOAD = 2*(time_us) -1;     /* */

	CLEAR_BIT(SYSTICK->CTRL, CLKSOURCE); /* CLOCK SOURSE SELECTED AHB/8  */

	SET_BIT(SYSTICK->CTRL, ENABLE);

	while(READ_BIT(SYSTICK->CTRL, COUNTFLAG) == 0);

	SYSTICK->CTRL = 0;  /* Close the timer */
}
uint8_t SysTick_Delay_ms(uint16_t time_ms)
{
	CLEAR_BIT(SYSTICK->CTRL, ENABLE);  /* make sure timer is OFF */
	SYSTICK->LOAD = 2*(time_ms*1000) - 1;

	CLEAR_BIT(SYSTICK->CTRL, CLKSOURCE); /* CLOCK SOURSE SELECTED AHB/8  */

	SET_BIT(SYSTICK->CTRL, ENABLE);

	while (READ_BIT(SYSTICK->CTRL, COUNTFLAG) == 0);

	SYSTICK->CTRL = 0;  /* Close the timer */
}


uint8_t pulling_Delay_ms(uint16_t time_ms)
{
	uint32_t i = 0;

	while(i < (time_ms*100))
	{
		i++;
	}
}
