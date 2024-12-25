
#include <stdint.h>

#include "../../../Common/Stm32F446xx.h"
#include "../inc/NVIC_interface.h"
#include "../inc/NVIC_private.h"
#include "../../../Common/Error_type.h"



uint8_t NVIC_EnableIRQ(EN_IRQn_t IRQn)
{
	uint8_t Local_u8_Error_State = OK;

	if (IRQn <= FMPI2C1_error_IRQn)
	{
		NVIC_ISER[IRQn / 32] = 1 << (IRQn % 32);
	}
	else
	{
		Local_u8_Error_State = IRQn_SRC_ERR;
	}

	return Local_u8_Error_State;
}
uint8_t NVIC_DisableIRQ(EN_IRQn_t IRQn)
{
	uint8_t Local_u8_Error_State = OK;

	if (IRQn <= FMPI2C1_error_IRQn)
	{
		NVIC_ICER[IRQn / 32] = 1 << (IRQn % 32);
	}
	else
	{
		Local_u8_Error_State = IRQn_SRC_ERR;
	}

	return Local_u8_Error_State;

}
uint8_t NVIC_SetPendingIRQ(EN_IRQn_t IRQn)
{
	uint8_t Local_u8_Error_State = OK;

	if (IRQn <= FMPI2C1_error_IRQn)
	{
		NVIC_ISPR[IRQn / 32] = 1 << (IRQn % 32);
	}
	else
	{
		Local_u8_Error_State = IRQn_SRC_ERR;
	}

	return Local_u8_Error_State;

}
uint8_t NVIC_ClearPendingIRQ(EN_IRQn_t IRQn)
{
	uint8_t Local_u8_Error_State = OK;

	if (IRQn <= FMPI2C1_error_IRQn)
	{
		NVIC_ICPR[IRQn / 32] = 1 << (IRQn % 32);
	}
	else
	{
		Local_u8_Error_State = IRQn_SRC_ERR;
	}

	return Local_u8_Error_State;

}
uint8_t NVIC_GetActiveFlag(EN_IRQn_t IRQn)
{
	return ( (NVIC_IABR[IRQn / 32] && (1 << (IRQn % 32))) >> (IRQn % 32) );
}
