
#include <stdint.h>
#include "../inc/EXTI_interface.h"
#include "../inc/EXTI_private.h"
#include "../../../Common/Stm32F446xx.h"
#include "../../../Common/Error_type.h"

void(*EXTI_Callback[NUM_EXTI_LINES])(void) = { NULL };



uint8_t EXTI_init(ST_EXTI_Config_t* copy_EXTI_config)
{
	uint8_t Local_u8_Error_State = OK;

	if ((copy_EXTI_config->line_num >= 0) && (copy_EXTI_config->line_num <= NUM_EXTI_LINES))
	{
		switch (copy_EXTI_config->init_state)
		{
		case ENABLE  :  SET_BIT(EXTI->IMR, copy_EXTI_config->line_num); break;
		case DISABLE :  CLEAR_BIT(EXTI->IMR, copy_EXTI_config->line_num); break;
		default: Local_u8_Error_State = EXTI_INIT_STATE_ERR;
		}

		switch (copy_EXTI_config->edge_detect)
		{
		case RISING_TRIG:         SET_BIT(EXTI->RTSR, copy_EXTI_config->line_num); break;
		case FALLING_TRIG:        SET_BIT(EXTI->FTSR, copy_EXTI_config->line_num); break;
		case RISING_FALLING_TRIG: SET_BIT(EXTI->RTSR, copy_EXTI_config->line_num); SET_BIT(EXTI->FTSR, copy_EXTI_config->line_num); break;
		default: Local_u8_Error_State = EXTI_TRIG_STATE_ERR;
		}

		if (copy_EXTI_config->CallBackFun != NULL)
		{
			EXTI_Callback[copy_EXTI_config->line_num] = copy_EXTI_config->CallBackFun;
		}
		else
		{
			Local_u8_Error_State = NULL_PTR_ERR;
		}
		
	}

	else
	{
		Local_u8_Error_State = EXTI_LINE_NUM_ERR;
	}

	return Local_u8_Error_State; 
}
uint8_t EXTI_enable_Int(EN_EXTI_LINE_NUM_t copy_line_num)
{
	uint8_t Local_u8_Error_State = OK; 

	if ((copy_line_num >= 0) && (copy_line_num <= NUM_EXTI_LINES))
	{
		SET_BIT(EXTI->IMR, copy_line_num);
	}
	else
	{
		Local_u8_Error_State = EXTI_LINE_NUM_ERR;
	}

	return Local_u8_Error_State;
}
uint8_t EXTI_disable_Int(EN_EXTI_LINE_NUM_t copy_line_num)
{
	uint8_t Local_u8_Error_State = OK;

	if ((copy_line_num >= 0) && (copy_line_num <= NUM_EXTI_LINES))
	{
		CLEAR_BIT(EXTI->IMR, copy_line_num);
	}
	else
	{
		Local_u8_Error_State = EXTI_LINE_NUM_ERR;
	}

	return Local_u8_Error_State;
}
uint8_t EXTI_ClearPendingFlag(EN_EXTI_LINE_NUM_t copy_line_num)
{
	uint8_t Local_u8_Error_State = OK;

	if ((copy_line_num >= 0) && (copy_line_num <= NUM_EXTI_LINES))
	{
		SET_BIT(EXTI->PR, copy_line_num);    /* clear flag by writing 1 */
	}
	else
	{
		Local_u8_Error_State = EXTI_LINE_NUM_ERR;
	}

	return Local_u8_Error_State;
}

uint8_t EXTI_GetPendingFlag(EN_EXTI_LINE_NUM_t copy_line_num, uint8_t* copy_Flag_Status)
{
	uint8_t Local_u8_Error_State = OK;

	if ((copy_line_num >= 0) && (copy_line_num <= NUM_EXTI_LINES))
	{
		*copy_Flag_Status = ((EXTI->PR) >> copy_line_num) & 1; 
	}
	else
	{
		Local_u8_Error_State = EXTI_LINE_NUM_ERR;
	}

	return Local_u8_Error_State;
}





void EXTI0_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI_LINE0);
	EXTI_Callback[EXTI_LINE0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI_LINE1);
	EXTI_Callback[EXTI_LINE1]();
}


void EXTI2_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI_LINE2);
	EXTI_Callback[EXTI_LINE2]();
}
void EXTI3_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI_LINE3);
	EXTI_Callback[EXTI_LINE3]();
}
void EXTI4_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI_LINE4);
	EXTI_Callback[EXTI_LINE4]();
}

void EXTI9_5_IRQHandler(void)
{
	if ((((EXTI->PR) >> EXTI_LINE5) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE5);
		EXTI_Callback[EXTI_LINE5]();
	}
	if ((((EXTI->PR) >> EXTI_LINE6) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE6);
		EXTI_Callback[EXTI_LINE6]();
	}
	if ((((EXTI->PR) >> EXTI_LINE7) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE7);
		EXTI_Callback[EXTI_LINE7]();
	}
	if ((((EXTI->PR) >> EXTI_LINE8) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE8);
		EXTI_Callback[EXTI_LINE8]();
	}
	if ((((EXTI->PR) >> EXTI_LINE9) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE9);
		EXTI_Callback[EXTI_LINE9]();
	}

}

void EXTI15_10_IRQHandler(void)
{
	if ((((EXTI->PR) >> EXTI_LINE10) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE10);
		EXTI_Callback[EXTI_LINE10]();
	}
	if ((((EXTI->PR) >> EXTI_LINE11) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE11);
		EXTI_Callback[EXTI_LINE11]();
	}
	if ((((EXTI->PR) >> EXTI_LINE12) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE12);
		EXTI_Callback[EXTI_LINE12]();
	}
	if ((((EXTI->PR) >> EXTI_LINE13) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE13);
		EXTI_Callback[EXTI_LINE13]();
	}
	if ((((EXTI->PR) >> EXTI_LINE14) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE14);
		EXTI_Callback[EXTI_LINE14]();
	}
	if ((((EXTI->PR) >> EXTI_LINE15) & 1) == 1)
	{
		EXTI_ClearPendingFlag(EXTI_LINE15);
		EXTI_Callback[EXTI_LINE15]();
	}
}
