#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H



/********************************
 *  SysTick Control and Status Register pins *
 ********************************/
enum
{
	ENABLE,
	TICKINT,
	CLKSOURCE,

	COUNTFLAG = 16
};


uint8_t SysTick_Delay_us(uint16_t time_us);
uint8_t SysTick_Delay_ms(uint16_t time_ms);

uint8_t pulling_Delay_ms(uint16_t time_ms);

#endif // !SYSTICK_INTERFACE_H

