#include <stdint.h>
#include "../../../Common/Error_type.h"
#include "../../../Common/Stm32F446xx.h"
#include "../inc/DMA_private.h"
#include "../inc/DMA_interface.h"




/* DMA[DMA_config->DMA_controller] */

void(*DMA1_Callback[NUMBERS_OF_STREAMS][DMA_IT_FLAGS])(void) = { NULL };
void(*DMA2_Callback[NUMBERS_OF_STREAMS][DMA_IT_FLAGS])(void) = { NULL };

uint8_t DMA_Init(ST_DMA_config_t* DMA_config)
{
	uint8_t Local_u8_Error_State = OK;
	uint16_t wait_time_out = 0;

	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (DMA_config->DMA_controller) * 0x400);

	/* clear all flags , reset some configs */
	if (DMA_config->DMA_controller == DMA1 || DMA_config->DMA_controller == DMA2)
	{
		/* clear flags */
		DMA_X->DMA_IFCR[0] = 0;
		DMA_X->DMA_IFCR[1] = 0;
		/* reset SFCR register */
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SFCR = 0;
	}
	else
	{
		Local_u8_Error_State = DMA_SELECT_ERR;
	}

	/* disable the stream by clear EN , not allowd for config the stream when this bit is 1 */
	if (DMA_config->DMA_str_num < NUMBERS_OF_STREAMS)
	{
		CLEAR_BIT(DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR, EN);
	}
	else
	{
		Local_u8_Error_State = DMA_NUM_STREAM_ERR;
	}

	/*  Writing this bit to 0 is not immediately effective , wait for the EN bit to be cleared
	**  before starting any stream configuration ********************************************/
	while (CLEAR_BIT(DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR, EN) == 1)
	{
		if (wait_time_out >= STREAM_EN_TIMEOUT)
		{
			Local_u8_Error_State = TIMEOUT_ERR;
			break;
		}

		wait_time_out++;
	}

	/* set DMA channel */
	if ((DMA_config->DMA_ch_num >= CHANNEL0) && (DMA_config->DMA_ch_num <= CHANNEL7))
	{
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_CHANNEL_MASK;
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_ch_num << CHSEL;
	}
	else
	{
		Local_u8_Error_State = DMA_CHANNEL_ERR;
	}

	/* set stream priority */
	if (DMA_config->DMA_str_priority >= LOW_PRIORITY && DMA_config->DMA_str_priority <= VERY_HIGH_PRIORITY)
	{
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_PL_MASK;
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_str_priority << PL;
	}
	else
	{
		Local_u8_Error_State = DMA_STREAM_PRIORITY_ERR;
	}

	/* set DMA mode  direct & fifo */

	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SFCR &= DMA_MODE_MASK;
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SFCR |= DMA_config->DMA_mode << DMDIS;

	if (DMA_config->DMA_mode == FIFO_MODE)
	{
		if (DMA_config->DMA_fifo_select >= QUARTER_FULL_FIFO && DMA_config->DMA_fifo_select <= FULL_FIFO)
		{
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SFCR &= DMA_FIFO_THRESHOLD_MASK;
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SFCR |= DMA_config->DMA_fifo_select << FTH;
		}
		else
		{
			Local_u8_Error_State = DMA_FIFO_THRESHOLD_ERR;
		}
	}

	/* set DMA Direction */
	if (DMA_config->DMA_dir == P2M || DMA_config->DMA_dir == M2P || DMA_config->DMA_dir == M2M)
	{
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_DIR_MASK;
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_dir << DIR;
	}
	else
	{
		Local_u8_Error_State = DMA_DIR_ERR;
	}

	/* set memmory increment */
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_MEM_INC_MASK;
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_mem_inc << MINC;

	/* set peripheral increment */
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_PERIPH_INC_MASK;
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_p_inc << PINC;


	/* set memmory allignment */
	if (DMA_config->DMA_mem_allign == BYTE || DMA_config->DMA_mem_allign == HALF_WORD || DMA_config->DMA_mem_allign == WORD)
	{
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_MEM_SIZE_MASK;
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_mem_allign << MSIZE;
	}
	else
	{
		Local_u8_Error_State = DMA_MEM_ALLIGN_ERR;
	}

	/* set peripheral allignment */
	if (DMA_config->DMA_mem_allign == BYTE || DMA_config->DMA_mem_allign == HALF_WORD || DMA_config->DMA_mem_allign == WORD)
	{
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_PERIPH_SIZE_MASK;
		DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_p_allign << PSIZE;
	}
	else
	{
		Local_u8_Error_State = DMA_PERIPH_ALLIGN_ERR;
	}


	/* set enable & disable circular mode */
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_CIRCULAR_MODE_MASK;
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= DMA_config->DMA_Circular_mode << CIRC;

	/* enable & disable interrupts */
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR &= DMA_IT_TYPES_MASK;
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR |= (DMA_config->DMA_IT_State.Direct_Mode_Error_IT << DMEIE) | (DMA_config->DMA_IT_State.Transfer_Error_IT << TEIE) | (DMA_config->DMA_IT_State.Half_Transfer_IT << HTIE) | (DMA_config->DMA_IT_State.Transfer_Complete_IT << TCIE);




	return Local_u8_Error_State;
}



uint8_t DMA_Start_IT(ST_DMA_config_t* DMA_config, uint32_t* Src_Addr, uint32_t* Dest_Addr, uint16_t data_items)
{
	uint8_t Local_u8_Error_State = OK;

	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (DMA_config->DMA_controller) * 0x400);

	/* set Addresses */

	if ((Src_Addr != NULL) && (Dest_Addr != NULL))
	{
		switch (DMA_config->DMA_dir)
		{
		case M2M:
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SPAR = (uint32_t)Src_Addr;
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SM0AR = (uint32_t)Dest_Addr;
			break;

		case P2M:
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SPAR = (uint32_t)Src_Addr;
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SM0AR = (uint32_t)Dest_Addr;
			break;

		case M2P:
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SM0AR = (uint32_t)Src_Addr;
			DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SPAR = (uint32_t)Dest_Addr;

		}
	}
	else
	{
		Local_u8_Error_State = NULL_PTR_ERR;
	}

	/* Configure the total number of data items to be transferred in the DMA_SxNDTR register */
	DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SNDTR = data_items;

	/* Activate the stream by setting the EN bit in the DMA_SCR register */
	SET_BIT(DMA_X->DMA_Stream[DMA_config->DMA_str_num].DMA_SCR, EN);


	return Local_u8_Error_State;
}

uint8_t DMA_Set_Callback(ST_DMA_config_t* DMA_config, EN_DMA_IT_Type_t DMA_IT_type)
{
	uint8_t Local_u8_Error_State = OK;

	if (DMA_config->DMA_CallBackFun != NULL)
	{
		if (DMA_config->DMA_controller == DMA1)
		{
			DMA1_Callback[DMA_config->DMA_str_num][DMA_IT_type] = DMA_config->DMA_CallBackFun[DMA_IT_type];
		}
		else if (DMA_config->DMA_controller == DMA2)
		{
			DMA2_Callback[DMA_config->DMA_str_num][DMA_IT_type] = DMA_config->DMA_CallBackFun[DMA_IT_type];
		}
		else
		{
			Local_u8_Error_State = DMA_SELECT_ERR;
		}

	}
	else
	{
		Local_u8_Error_State = NULL_PTR_ERR;
	}

	return Local_u8_Error_State;
}

static uint8_t DMA_Get_Flags_State(EN_DMA_Controller_t DMA_type, EN_DMA_Stream_t stram_num, ST_DMA_IT_FLAGS_State_t* Flags_state)
{
	uint8_t Local_u8_Error_State = OK;

	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (DMA_type) * 0x400);

	uint8_t loc_stream_num = stram_num % 4;
	if ((loc_stream_num == 0) || (loc_stream_num == 1))
	{
		Flags_state->FIFO_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (FEIF0 + loc_stream_num * 6)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SFCR, FEIE);
		Flags_state->Direct_Mode_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (DMEIF0 + loc_stream_num * 6)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, DMEIE);
		Flags_state->Transfer_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (TEIF0 + loc_stream_num * 6)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, TEIE);
		Flags_state->Half_Transfer_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (HTIF0 + loc_stream_num * 6)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, HTIE);
		Flags_state->Transfer_Complete_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (TCIF0 + loc_stream_num * 6)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, TCIE);
	}
	else if (loc_stream_num == 2)
	{
		Flags_state->FIFO_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (FEIF0 + 16)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SFCR, FEIE);
		Flags_state->Direct_Mode_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (DMEIF0 + 16)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, DMEIE);
		Flags_state->Transfer_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (TEIF0 + 16)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, TEIE);
		Flags_state->Half_Transfer_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (HTIF0 + 16)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, HTIE);
		Flags_state->Transfer_Complete_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (TCIF0 + 16)) && READ_BIT(DMA_X->DMA_Stream[stram_num].DMA_SCR, TCIE);
	}
	else if (loc_stream_num == 3)
	{
		Flags_state->FIFO_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (FEIF0 + 22));
		Flags_state->Direct_Mode_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (DMEIF0 + 22));
		Flags_state->Transfer_Error_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (TEIF0 + 22));
		Flags_state->Half_Transfer_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (HTIF0 + 22));
		Flags_state->Transfer_Complete_Flag = READ_BIT(DMA_X->DMA_ISR[stram_num / 4], (TCIF0 + 22));
	}
	else
	{
		Local_u8_Error_State = DMA_NUM_STREAM_ERR;
	}

	return Local_u8_Error_State;


}


uint8_t DMA_Clear_IT_Flag(EN_DMA_Controller_t DMA_type, EN_DMA_Stream_t stram_num, EN_DMA_IT_Type_t IT_type)
{
	uint8_t Local_u8_Error_State = OK;

	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (DMA_type) * 0x400);

	uint8_t loc_stream_num_div = stram_num / 4;
	uint8_t loc_stream_num_rem = stram_num % 4;

	if ((loc_stream_num_rem == 0) || (loc_stream_num_rem == 1))
	{
		switch (IT_type)
		{
		case Transfer_Complete_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CTCIF0 + loc_stream_num_rem * 6));
			break;
		case Half_Transfer_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CHTIF0 + loc_stream_num_rem * 6));
			break;
		case Transfer_Error_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CTEIF0 + loc_stream_num_rem * 6));
			break;
		case Direct_Mode_Error_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CDMEIF0 + loc_stream_num_rem * 6));
			break;
		default:
			Local_u8_Error_State = DMA_IT_TYPES_ERR;
		}
	}

	if (loc_stream_num_rem == 2)
	{
		switch (IT_type)
		{
		case Transfer_Complete_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CTCIF0 + loc_stream_num_rem * 16));
			break;
		case Half_Transfer_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CHTIF0 + loc_stream_num_rem * 16));
			break;
		case Transfer_Error_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CTEIF0 + loc_stream_num_rem * 16));
			break;
		case Direct_Mode_Error_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CDMEIF0 + loc_stream_num_rem * 16));
			break;
		default:
			Local_u8_Error_State = DMA_IT_TYPES_ERR;
		}
	}

	if (loc_stream_num_rem == 3)
	{
		switch (IT_type)
		{
		case Transfer_Complete_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CTCIF0 + loc_stream_num_rem * 22));
			break;
		case Half_Transfer_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CHTIF0 + loc_stream_num_rem * 22));
			break;
		case Transfer_Error_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CTEIF0 + loc_stream_num_rem * 22));
			break;
		case Direct_Mode_Error_ID:
			SET_BIT(DMA_X->DMA_IFCR[loc_stream_num_div], (CDMEIF0 + loc_stream_num_rem * 22));
			break;
		default:
			Local_u8_Error_State = DMA_IT_TYPES_ERR;
		}
	}

	return Local_u8_Error_State;
}


void DMA1_Stream0_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM0, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM0, Transfer_Complete_ID);
		DMA1_Callback[STREAM0][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM0, Half_Transfer_ID);
		DMA1_Callback[STREAM0][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM0, Direct_Mode_Error_ID);
		DMA1_Callback[STREAM0][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM0, FIFO_Error_ID);
		DMA1_Callback[STREAM0][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM0, Transfer_Error_ID);
		DMA1_Callback[STREAM0][Transfer_Error_ID]();
	}
}
void DMA1_Stream1_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM1, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM1, Transfer_Complete_ID);
		DMA1_Callback[STREAM1][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA1_Callback[STREAM1][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM1][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM1][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM1][Transfer_Error_ID]();
	}
}
void DMA1_Stream2_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM2, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM2, Transfer_Complete_ID);
		DMA1_Callback[STREAM2][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA1_Callback[STREAM2][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM2][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM2][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM2][Transfer_Error_ID]();
	}
}
void DMA1_Stream3_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM3, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM3, Transfer_Complete_ID);
		DMA1_Callback[STREAM3][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA1_Callback[STREAM3][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM3][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM3][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM3][Transfer_Error_ID]();
	}
}
void DMA1_Stream4_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM4, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM4, Transfer_Complete_ID);
		DMA1_Callback[STREAM4][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA1_Callback[STREAM4][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM4][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM4][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM4][Transfer_Error_ID]();
	}
}
void DMA1_Stream5_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM5, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		/*  disable DMA requests then wait for a BTF event before programming the Stop condition */
		DMA->DMA1_Peripheral.DMA_Stream[6].DMA_SCR &= ~(1 << EN);

		while (!READ_BIT(I2C->I2C1.SR1, 2));
		SET_BIT(I2C->I2C1.CR1, 9);

		DMA_Clear_IT_Flag(DMA1, STREAM6, Transfer_Complete_ID);
		DMA1_Callback[STREAM6][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA1_Callback[STREAM5][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM5][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM5][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM5][Transfer_Error_ID]();
	}
}
void DMA1_Stream6_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM6, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		/*  disable DMA requests then wait for a BTF event before programming the Stop condition */
		DMA->DMA1_Peripheral.DMA_Stream[6].DMA_SCR &= ~(1 << EN);

		while (!READ_BIT(I2C->I2C1.SR1, 2));
		SET_BIT(I2C->I2C1.CR1, 9);

		DMA_Clear_IT_Flag(DMA1, STREAM6, Transfer_Complete_ID);
		DMA1_Callback[STREAM6][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM6, Half_Transfer_ID);
		DMA1_Callback[STREAM6][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM6][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM6][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM6][Transfer_Error_ID]();
	}
}
void DMA1_Stream7_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA1, STREAM7, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA1, STREAM7, Transfer_Complete_ID);
		DMA1_Callback[STREAM7][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA1_Callback[STREAM7][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA1_Callback[STREAM7][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA1_Callback[STREAM7][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA1_Callback[STREAM7][Transfer_Error_ID]();
	}
}















void DMA2_Stream0_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM0, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM0, Transfer_Complete_ID);
		DMA2_Callback[STREAM0][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM0, Half_Transfer_ID);
		DMA2_Callback[STREAM0][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM0, Direct_Mode_Error_ID);
		DMA2_Callback[STREAM0][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM0, FIFO_Error_ID);
		DMA2_Callback[STREAM0][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM0, Transfer_Error_ID);
		DMA2_Callback[STREAM0][Transfer_Error_ID]();
	}
}
void DMA2_Stream1_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM1, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM0, Transfer_Complete_ID);
		DMA2_Callback[STREAM1][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM1, Half_Transfer_ID);
		DMA2_Callback[STREAM1][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM1, Direct_Mode_Error_ID);
		DMA2_Callback[STREAM1][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM1, FIFO_Error_ID);
		DMA2_Callback[STREAM1][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM1, Transfer_Error_ID);
		DMA2_Callback[STREAM1][Transfer_Error_ID]();
	}
}
void DMA2_Stream2_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM2, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM2, Transfer_Complete_ID);
		DMA2_Callback[STREAM2][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM2, Half_Transfer_ID);
		DMA2_Callback[STREAM2][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM2, Direct_Mode_Error_ID);
		DMA2_Callback[STREAM2][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM2, FIFO_Error_ID);
		DMA2_Callback[STREAM2][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA_Clear_IT_Flag(DMA2, STREAM2, Transfer_Error_ID);
		DMA2_Callback[STREAM2][Transfer_Error_ID]();
	}
}
void DMA2_Stream3_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM3, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA2_Callback[STREAM3][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA2_Callback[STREAM3][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA2_Callback[STREAM3][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA2_Callback[STREAM3][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA2_Callback[STREAM3][Transfer_Error_ID]();
	}
}
void DMA2_Stream4_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM4, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA2_Callback[STREAM4][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA2_Callback[STREAM4][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA2_Callback[STREAM4][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA2_Callback[STREAM4][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA2_Callback[STREAM4][Transfer_Error_ID]();
	}
}
void DMA2_Stream5_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM5, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA2_Callback[STREAM5][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA2_Callback[STREAM5][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA2_Callback[STREAM5][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA2_Callback[STREAM5][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA2_Callback[STREAM5][Transfer_Error_ID]();
	}
}
void DMA2_Stream6_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM6, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA2_Callback[STREAM6][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA2_Callback[STREAM6][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA2_Callback[STREAM6][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA2_Callback[STREAM6][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA2_Callback[STREAM6][Transfer_Error_ID]();
	}
}
void DMA2_Stream7_IRQHandler(void)
{
	ST_DMA_IT_FLAGS_State_t loc_Flags;
	DMA_Get_Flags_State(DMA2, STREAM7, &loc_Flags);

	/* check which IT Flag is set */
	if (loc_Flags.Transfer_Complete_Flag == 1)
	{
		DMA2_Callback[STREAM7][Transfer_Complete_ID]();
	}
	if (loc_Flags.Half_Transfer_Flag == 1)
	{
		DMA2_Callback[STREAM7][Half_Transfer_ID]();
	}
	if (loc_Flags.Direct_Mode_Error_Flag == 1)
	{
		DMA2_Callback[STREAM7][Direct_Mode_Error_ID]();
	}
	if (loc_Flags.FIFO_Error_Flag == 1)
	{
		DMA2_Callback[STREAM7][FIFO_Error_ID]();
	}
	if (loc_Flags.Transfer_Error_Flag == 1)
	{
		DMA2_Callback[STREAM7][Transfer_Error_ID]();
	}
}


