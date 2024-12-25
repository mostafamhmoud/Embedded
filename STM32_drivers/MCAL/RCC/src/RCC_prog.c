#include <stdint.h>

#include "../../../Common/Error_type.h"
#include "../../../Common/Stm32F446xx.h"
#include "../inc/RCC_private.h"
#include "../inc/RCC_interface.h"



uint8_t RCC_Enable_HSI(void)
{
	uint8_t Local_u8_Error_State = OK;
	uint16_t wait = 0;
	SET_BIT(RCC->CR, HSION);
	while ((RCC->CR & (1 << HSIRDY)) == 0)
	{
		if (wait >= 500)
		{
			Local_u8_Error_State = TIMEOUT_ERR;
			break;
		}
		wait++;
	}
	SET_BIT(RCC->CIR, HSIRDYC); /* clear flag */

	RCC->CFGR &= ~(CLOCK_SWITCH_MASK << SW0);
	RCC->CFGR |= (HSI_system_clock_select << SW0);

	return Local_u8_Error_State;

}
uint8_t RCC_Enable_HSE(void)
{
	uint8_t Local_u8_Error_State = OK;
	uint16_t wait = 0;
	SET_BIT(RCC->CR, HSEON);
	while ((RCC->CR & (1 << HSERDY)) == 0)
	{
		if (wait >= 500)
		{
			Local_u8_Error_State = TIMEOUT_ERR;
			break;
		}
		wait++;
	}
	SET_BIT(RCC->CIR, HSERDYC); /* clear flag */

	RCC->CFGR &= ~(CLOCK_SWITCH_MASK << SW0);
	RCC->CFGR |= (HSE_system_clock_select << SW0);

	return Local_u8_Error_State;
}

uint8_t RCC_Enable_PLL(ST_RCC_Config_t* st_rcc_config)
{
	uint8_t Local_u8_Error_State = OK;
	uint16_t wait = 0;
	SET_BIT(RCC->CR, PLLON);
	while ((RCC->CR & (1 << PLLRDY)) == 0)
	{
		if (wait >= 500)
		{
			Local_u8_Error_State = TIMEOUT_ERR;
			break;
		}
		wait++;
	}

	/* Switch to PLL*/
	RCC->CFGR &= ~(CLOCK_SWITCH_MASK << SW0);
	RCC->CFGR |= (PLL_P_system_clock_select << SW0);

	/* PLL Clock Source */
	if (st_rcc_config->PLL_clk_src == HSI)
	{
		CLEAR_BIT(RCC->PLLCFGR, PLLSRC);
	}
	else if (st_rcc_config->PLL_clk_src == HSE)
	{
		SET_BIT(RCC->PLLCFGR, PLLSRC);
	}
	else
	{
		Local_u8_Error_State = PLL_CLK_SRC_ERR;
	}
	SET_BIT(RCC->CIR, PLLRDYC); /* clear flag */

	/* configuration for PLL*/

	if (IS_PLLM_DEVISION_FACTOR_CORRECT(st_rcc_config->PLLM_Pres))
	{
		RCC->PLLCFGR = (RCC->PLLCFGR & (PLLM_DEVISION_FACTOR_MASK)) | (st_rcc_config->PLLM_Pres << PLLM0);
	}
	else
	{
		Local_u8_Error_State = PLLM_DEVISION_FACTOR_ERR;
	}

	if(IS_PLLN_MULTIPLICATION_FACTOR_CORRECT(st_rcc_config->PLLN_Factor))
	{
		RCC->PLLCFGR = (RCC->PLLCFGR & (PLLN_MULTIPLICATION_FACTOR_MASK)) | (st_rcc_config->PLLN_Factor << PLLN0);
	}
	else
	{
		Local_u8_Error_State = PLLN_MULTIPLICATION_FACTOR_ERR;
	}

	if (IS_PLLP_DEVISION_FACTOR_CORRECT(st_rcc_config->PLLP_Pres))
	{
		RCC->PLLCFGR = (RCC->PLLCFGR & (PLLP_DEVISION_FACTOR_MASK)) | (st_rcc_config->PLLP_Pres << PLLP0);
	}
	else
	{
		Local_u8_Error_State = PLLP_DEVISION_FACTOR_ERR;
	}

	return Local_u8_Error_State;
}
uint8_t RCC_Enable_LSI(void);
uint8_t RCC_Enable_LSE(void);
uint8_t RCC_MCO_CLK(uint8_t MCO_CLK_source);

uint8_t AHP_Prescaler(EN_AHP_SysClk_Prescaler_t AHP_prescaler_value)
{
	uint8_t Local_u8_Error_State = OK;
	if (IS_AHB_PRESCALER_CORRECT(AHP_prescaler_value))
	{
		RCC->CFGR = (RCC->CFGR & (AHP_PRESCALER_MASK)) | (AHP_prescaler_value << HPRE0);
	}
	else
	{
		Local_u8_Error_State = AHB_PRESCALER_ERR;
	}
	return Local_u8_Error_State;
}
uint8_t APB1_Prescaler(EN_APB1_HClk_Prescaler_t APB1_prescaler_value)
{
	uint8_t Local_u8_Error_State = OK;
	if (IS_APB1_PRESCALER_CORRECT(APB1_prescaler_value))
	{
		RCC->CFGR = (RCC->CFGR & (APB1_PRESCALER_MASK)) | (APB1_prescaler_value << PPRE10);
	}
	else
	{
		Local_u8_Error_State = APB1_PRESCALER_ERR;
	}
	return Local_u8_Error_State;
}
uint8_t APB2_Prescaler(EN_APB2_HClk_Prescaler_t APB2_prescaler_value)
{
	uint8_t Local_u8_Error_State = OK;
	if (IS_APB2_PRESCALER_CORRECT(APB2_prescaler_value))
	{
		RCC->CFGR = (RCC->CFGR & (APB2_PRESCALER_MASK)) | (APB2_prescaler_value << PPRE20);
	}
	else
	{
		Local_u8_Error_State = APB2_PRESCALER_ERR;
	}
	return Local_u8_Error_State;

}
uint8_t ADC_Prescaler(uint8_t ADC_prescaler_value);
uint8_t USB_Prescaler(uint8_t USB_prescaler_value);

uint8_t RCC_Enable_Peripheral(uint8_t peripheral_idx)
{
	uint8_t Local_u8_Error_State = OK;
	if (PERIPHERAL_IN_RCC_AHB1ENR(peripheral_idx))
	{
		SET_BIT(RCC->AHB1ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_AHB2ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 32;
		SET_BIT(RCC->AHB2ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_AHB3ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 64;
		SET_BIT(RCC->AHB3ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_APB1ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 96;
		SET_BIT(RCC->APB1ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_APB2ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 128;
		SET_BIT(RCC->APB2ENR, peripheral_idx);
	}
	else
	{
		Local_u8_Error_State = PERIPHERAL_NOT_FOUND_ERR;
	}
	return Local_u8_Error_State;
}

uint8_t RCC_Disable_Peripheral(uint8_t peripheral_idx)
{
	uint8_t Local_u8_Error_State = OK;
	if (PERIPHERAL_IN_RCC_AHB1ENR(peripheral_idx))
	{
		CLEAR_BIT(RCC->AHB1ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_AHB2ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 32;
		CLEAR_BIT(RCC->AHB2ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_AHB3ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 64;
		CLEAR_BIT(RCC->AHB2ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_APB1ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 96;
		CLEAR_BIT(RCC->AHB2ENR, peripheral_idx);
	}
	else if (PERIPHERAL_IN_RCC_APB2ENR(peripheral_idx))
	{
		peripheral_idx = peripheral_idx - 128;
		CLEAR_BIT(RCC->AHB2ENR, peripheral_idx);
	}
	else
	{
		Local_u8_Error_State = PERIPHERAL_NOT_FOUND_ERR;
	}
	return Local_u8_Error_State;
}


uint8_t RCC_Config(ST_RCC_Config_t* st_rcc_config)
{
	uint8_t Local_u8_Error_State = OK;

	if (st_rcc_config->Sys_Clk_Select == HSI_system_clock_select)
	{
		Local_u8_Error_State = RCC_Enable_HSI();
	}
	else if (st_rcc_config->Sys_Clk_Select == HSE_system_clock_select)
	{
		Local_u8_Error_State = RCC_Enable_HSE();
	}
	else if(st_rcc_config->Sys_Clk_Select == PLL_P_system_clock_select)
	{
		Local_u8_Error_State = RCC_Enable_PLL(st_rcc_config);
	}
	else
	{
		Local_u8_Error_State = CLK_SRC_ERR;
	}

	Local_u8_Error_State = AHP_Prescaler(st_rcc_config->AHP_Pres);
	Local_u8_Error_State = APB1_Prescaler(st_rcc_config->APB1_Pres);
	Local_u8_Error_State = APB2_Prescaler(st_rcc_config->APB2_Pres);

	return Local_u8_Error_State;
}
