
#include <stdint.h>


#include "../inc/SYSCFG_interface.h"
#include "../inc/SYSCFG_private.h"
#include "../../../Common/Stm32F446xx.h"
#include "../../../Common/Error_type.h"

uint8_t SYSCFG_Set_Line(EN_SYSCFG_Line_t copy_port, EN_SYSCFG_Line_t copy_line)
{
	uint8_t Local_u8_Error_State = OK;

	if ((copy_line >= 0) && (copy_line <= NUM_LINES) && ((copy_port >= PA) && (copy_port <= PH)))
	{
		SYSCFG->EXTICR[copy_line / 4] &= ~(SYSCFG_EXTI_LINE_MASK << ((copy_line % EXTI_CTRL_LINES) * EXTI_CTRL_LINES));
		SYSCFG->EXTICR[copy_line/4]   |= (copy_port << ((copy_line % EXTI_CTRL_LINES) * EXTI_CTRL_LINES));
	}
	else
	{
		Local_u8_Error_State = SYSCFG_LINE_NUM_ERR;
	}

	return Local_u8_Error_State;
}
