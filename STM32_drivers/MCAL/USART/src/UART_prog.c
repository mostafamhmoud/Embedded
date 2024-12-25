#include <stdint.h>
#include "../../../Common/Error_type.h"
#include "../../../Common/Stm32F446xx.h"
#include "../inc/UART_private.h"
#include "../inc/UART_interface.h"




uint8_t USART_init(ST_USART_Config_t* usart_config)
{
	uint8_t Local_u8_Error_State = OK;

	ST_USART_RegDef_t* USART_X = (ST_USART_RegDef_t*)((uint32_t)(&USART->USART2.SR) + ((usart_config->usart_num) * 0x400));

	if ((usart_config->sync_async == ASYNCHRONOUS || usart_config->sync_async == SYNCHRONOUS) &&
		(usart_config->clk_phase == SECOND_CLK_TRANS || usart_config->clk_phase == FIRST_CLK_TRANS) &&
		(usart_config->clk_pol == STD_HIGH || usart_config->clk_pol == STD_LOW) &&
		(usart_config->data_length == DATA_BITS_9 || usart_config->data_length == DATA_BITS_8) &&
		(usart_config->mode >= RECEIVER && usart_config->mode <= TRANSMITTER_RECEIVER) &&
		(usart_config->ov_s_mode == OVERSAMPLING_BY_16 || usart_config->ov_s_mode == OVERSAMPLING_BY_8) &&
		(usart_config->parity_en_dis == PARITY_CONTROL_DISABLE || usart_config->parity_en_dis == PARITY_CONTROL_ENABLE) &&
		(usart_config->parity_ev_odd == ODD_PARITY || usart_config->parity_ev_odd == EVEN_PARITY) &&
		(usart_config->stop_bits >= ONE_STOP_BIT || usart_config->stop_bits <= ONE_HALF_STOP_BIT))
	{
		USART_X->CR1 = 0;
		USART_X->CR2 = 0;
		USART_X->CR3 = 0;

		USART_X->CR1 |= (usart_config->ov_s_mode << OVER8) | (usart_config->data_length << M) |
			(usart_config->parity_en_dis << PCE) | (usart_config->parity_ev_odd << PS);

		switch (usart_config->mode)
		{
		case TRANSMITTER: USART_X->CR1 |= (1 << TE); break;

		case RECEIVER: USART_X->CR1 |= (1 << RE); break;

		case TRANSMITTER_RECEIVER: USART_X->CR1 |= (1 << TE); USART_X->CR1 |= (1 << RE); break;
		}

		USART_X->CR2 |= (usart_config->clk_pol << CPOL) | (usart_config->clk_phase << CPHA) |
			((usart_config->stop_bits << STOP) & ~(USART_STOP_BITS_MASK));

		USART_X->CR3 |= (usart_config->half_duplex_select << HDSEL);

		if (usart_config->sync_async == SYNCHRONOUS)
		{
			/* The synchronous mode is selected by writing the CLKEN bit in the USART_CR2 register to 1 */
			USART_X->CR2 |= (1 << CLKEN);
			/* In synchronous mode, the following bits must be kept cleared */
			USART_X->CR2 &= ~(1 << LINEN);
			USART_X->CR3 &= ~(1 << SCEN) & ~(1 << HDSEL) & ~(1 << IREN);
		}

		/* Baud rate configs */

		uint32_t USARTDIV = (16000000.0 / (8.0 * (2 - usart_config->ov_s_mode) * usart_config->baud_rate)) * 1000.0;

		uint32_t mantissa = USARTDIV / 1000;
		uint8_t over_sample = (usart_config->ov_s_mode == OVERSAMPLING_BY_16) ? 16 : 8;
		uint32_t div_fraction = (((USARTDIV % 1000) * (over_sample)) + 500) / 1000;

		USART_X->BRR = mantissa << 4 | (div_fraction & 0x0000000F);

		/*enable usart */
		USART_X->CR1 |= (1 << UE);
	}
	else
	{
		Local_u8_Error_State = NOK;
	}

	/* try something */
	//USART_X->CR1 = 0x200C ;

	return Local_u8_Error_State;
}

uint8_t USART_Transmit_Polling(ST_USART_Config_t* usart_config, uint8_t* trans_data, uint8_t data_len)
{
	uint8_t Local_u8_Error_State = OK;

	ST_USART_RegDef_t* USART_X = (ST_USART_RegDef_t*)((uint32_t)(&USART->USART2.SR) + ((usart_config->usart_num) * 0x400));

	if ((usart_config->usart_num >= USART_NUM_2 && usart_config->usart_num <= UART_NUM_5) ||
		(usart_config->usart_num == USART_NUM_1 || usart_config->usart_num == USART_NUM_6))
	{
		for (int i = 0; i < data_len; i++)
		{
			USART_X->DR = trans_data[i];
			while (!(READ_BIT(USART_X->SR, TXE)));
		}
	}
	else
	{
		Local_u8_Error_State = NOK;
	}

	return Local_u8_Error_State;
}

uint8_t USART_Receive_Polling(ST_USART_Config_t* usart_config, uint8_t* received_data)
{
	uint8_t Local_u8_Error_State = OK;

	ST_USART_RegDef_t* USART_X = (ST_USART_RegDef_t*)((uint32_t)(&USART->USART2.SR) + ((usart_config->usart_num) * 0x400));

	if (usart_config->usart_num >= USART_NUM_1 && usart_config->usart_num <= USART_NUM_6)
	{
		while (USART_X->SR & (1 << RXNE))
		{
			*received_data = USART_X->DR;
		}
	}
	else
	{
		Local_u8_Error_State = NOK;
	}

	return Local_u8_Error_State;
}

uint8_t USART_Transmit_DMA(ST_USART_Config_t* usart_config , uint32_t Src_Addr, uint32_t data_len)
{
	uint8_t Local_u8_Error_State = OK;

	ST_USART_RegDef_t* USART_X = (ST_USART_RegDef_t*)((uint32_t)(&USART->USART2.SR) + (usart_config->usart_num) * 0x400);
	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (usart_config->dma_used) * 0x400);

	if ((usart_config->usart_num >= USART_NUM_2 && usart_config->usart_num <= UART_NUM_5) ||
		(usart_config->usart_num == USART_NUM_1 || usart_config->usart_num == USART_NUM_6))
	{

		/* Set the USART_DR register address in the DMA_SxPAR register */
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SPAR = (uint32_t)(&USART_X->DR);

		/* Set the memory address in the DMA_SxMA0R register The data are loaded into USART_DR from this memory after each TxE event.*/
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SM0AR = Src_Addr;

		/* Configure the total number of bytes to be transferred in the DMA_SxNDTR register.After each TxE event, this value is decremented.*/
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SNDTR = data_len;

		/* Clear the TC bit in the SR register by writing 0 to it.*/
		USART_X->SR &= ~(1 << TC);

		/* Activate the stream by setting the EN bit in the DMA_SxCR register.*/
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SCR |= (1 << 0);     // EN  bit is zero

		/* enable DMA line */
		USART_X->CR3 |= (1 << DMAT);
	}

	else
	{
		Local_u8_Error_State = NOK;
	}

	return Local_u8_Error_State;
}

uint8_t USART_Receive_DMA(ST_USART_Config_t* usart_config, uint32_t Dest_Addr, uint32_t data_len)
{
	uint8_t Local_u8_Error_State = OK;

	ST_USART_RegDef_t* USART_X = (ST_USART_RegDef_t*)((uint32_t)(&USART->USART2.SR) + (usart_config->usart_num) * 0x400);
	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (usart_config->dma_used) * 0x400);

	if ((usart_config->usart_num >= USART_NUM_2 && usart_config->usart_num <= UART_NUM_5) ||
		(usart_config->usart_num == USART_NUM_1 || usart_config->usart_num == USART_NUM_6))
	{

		/* Set the USART_DR register address in the DMA_SxPAR register */
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SPAR = (uint32_t)(&USART_X->DR);

		/* Set the memory address in the DMA_SxMA0R register The data will be loaded from USART_DR to this memory area after each RXNE event.*/
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SM0AR = Dest_Addr;

		/* Configure the total number of bytes to be transferred in the DMA_SxNDTR register.After each RXNE event, this value is decremented.*/
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SNDTR = data_len;

		/* Activate the stream by setting the EN bit in the DMA_SxCR register.*/
		DMA_X->DMA_Stream[usart_config->dma_stream_used].DMA_SCR |= (1 << 0);     // EN  bit is zero

		/* enable DMA line */
		USART_X->CR3 |= (1 << DMAR);
	}

	else
	{
		Local_u8_Error_State = NOK;
	}

	return Local_u8_Error_State;
}

uint8_t USART_Transmit_IT(EN_USART_Num_t usart_num, uint8_t trans_data);

uint8_t USART_Receive_IT(EN_USART_Num_t usart_num, uint8_t* received_data);
