
/*******************************************************************************************/
 /* @file: File  GPIO_prog.c
  * @author : Mostafa Abdelmegeed
  * @brief The GPIO main source file
  *
  */

#include <stdint.h>

#include "../../../Common/Stm32F446xx.h"
#include "../inc/GPIO_interface.h"
#include "../inc/GPIO_private.h"
#include "../../../Common/Error_type.h"



/*******************************************************************************************/
 /* @brief : this function initializes GPIO pin
  * @param[in] : pin_config : pointer to struct have the init info
  * retval : Error_State
  *
  */


uint8_t GPIO_u8PIN_init(const ST_Pin_Config* pin_config)
{
	uint8_t Local_u8_Error_State = OK;

	ST_GPIO_RegDef_t* port_id = (ST_GPIO_RegDef_t*)((uint32_t)GPIOA + (pin_config->Port_X) * 0x400);

	if (pin_config != NULL)
	{
		if (pin_config->Port_X <= PORTH && (pin_config->Pin_Num <= 15))
		{
			/* switch to Mode*/
			port_id->MODER &= ~(0b11 << (2 * pin_config->Pin_Num));
			port_id->MODER |= (pin_config->mode << (2 * pin_config->Pin_Num));
			/* Pull Type */
			port_id->PUPDR &= ~(0b11 << 2 * pin_config->Pin_Num);
			port_id->PUPDR |= (pin_config->PullType << (2 * pin_config->Pin_Num));

			if (pin_config->mode == OUTPUT || pin_config->mode == ALTERNATE_FUNCTION)
			{
				port_id->PUPDR |= (pin_config->PullType << (2 * pin_config->Pin_Num));
				/* Output Type Push Pull & Open Drain */
				port_id->OTYPER &= ~(0b1 << (pin_config->Pin_Num));
				port_id->OTYPER |= (pin_config->Output_Type << (pin_config->Pin_Num));
				/* Speed */
				port_id->OSPEEDER &= ~(0b11 << (2 * pin_config->Pin_Num));
				port_id->OSPEEDER |= (pin_config->speed << (2 * pin_config->Pin_Num));
			}
			if (pin_config->mode == ALTERNATE_FUNCTION)
			{
				/* Function selection */
				port_id->AFR[pin_config->Pin_Num / 8] &= ~(0b1111 << (4 * (pin_config->Pin_Num % 8)));
				port_id->AFR[pin_config->Pin_Num / 8] |= (pin_config->Alt_Func << (4 * (pin_config->Pin_Num % 8)));
			}
		}
		else
		{
			Local_u8_Error_State = PORTS_PINS_ERR;
		}
	}
	else
	{
		Local_u8_Error_State = NULL_PTR_ERR;
	}

	return Local_u8_Error_State;

}
/*******************************************************************************************/
 /* @brief : this function output low or high to GPIO pin
  * @param[in] : EN_Port_t : options for port number ( A to H )
  * @param[in] : EN_Pin_t : options for pin number ( pin0 to pin15 )
  * @param[in] : EN_Pin_Value_t : options for pin value ( LOW & HIGH )
  * retval : Error_State
  *
  */

uint8_t GPIO_u8Set_Pin_Value(EN_Port_t Port_X, EN_Pin_t pin, EN_Pin_Value_t Pin_Value)
{
	uint8_t Local_u8_Error_State = OK;

	ST_GPIO_RegDef_t* port_id = (ST_GPIO_RegDef_t*)((uint32_t)GPIOA + Port_X * 0x400);

	if (Port_X <= PORTH && (pin <= 15)) // check if port and pin_number are Valid
	{
		(Pin_Value == PIN_HIGH) ? (port_id->BSRR = (1 << pin)) : (port_id->BSRR = (1 << (pin + 16)));
	}
	else
	{
		Local_u8_Error_State = PORTS_PINS_ERR;
	}
	return Local_u8_Error_State;
}

uint8_t GPIO_u8Toggle_Pin_Value(EN_Port_t Port_X, EN_Pin_t pin)
{
	uint8_t Local_u8_Error_State = OK;

	ST_GPIO_RegDef_t* port_id = (ST_GPIO_RegDef_t*)((uint32_t)GPIOA + Port_X * 0x400);

	if (Port_X <= PORTH && (pin <= 15)) // check if port and pin_number are Valid
	{
		TOGGLE_BIT(port_id->ODR, pin);
	}
	else
	{
		Local_u8_Error_State = PORTS_PINS_ERR;
	}
	return Local_u8_Error_State;
}

uint8_t GPIO_u8Read_Pin_Value(EN_Port_t Port_X, EN_Pin_t pin, EN_Pin_Value_t* Pin_Value)
{
	uint8_t Local_u8_Error_State = OK;

	ST_GPIO_RegDef_t* port_id = (ST_GPIO_RegDef_t*)((uint32_t)GPIOA + Port_X * 0x400);

	if (Port_X <= PORTH && (pin <= 15)) // check if port and pin_number are Valid
	{
		*Pin_Value = READ_BIT(port_id->ODR, pin);
	}
	else
	{
		Local_u8_Error_State = PORTS_PINS_ERR;
	}
	return Local_u8_Error_State;
}
