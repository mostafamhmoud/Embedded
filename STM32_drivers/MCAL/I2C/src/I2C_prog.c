

#include <stdint.h>
#include "../../../Common/Error_type.h"
#include "../../../Common/Stm32F446xx.h"
#include "../inc/I2C_interface.h"
#include "../inc/I2C_private.h"



void(*I2C_Callback[NUMBERS_OF_I2C][I2C_IT_SOURCES])(void) = { NULL };

uint8_t Flag_State = 0;


uint8_t I2C_init(ST_I2C_Config_t* i2c_config)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);

	if ((i2c_config->i2c_num >= I2C_NUM_1 && i2c_config->i2c_num <= I2C_NUM_3) &&
		(i2c_config->PCLK_freq_in_mhz >= 2 && i2c_config->PCLK_freq_in_mhz <= 50))


	{
		/* reset I2C */
		SET_BIT(I2C_X->CR1, SWRST);

		/* and again write a ‘0’ to this position to pull the I2C from the reset */
		CLEAR_BIT(I2C_X->CR1, SWRST);


		/* start configs */
		I2C_X->CR1 |= (i2c_config->smbus_mode << SMBUS) | (i2c_config->smbus_type << SMBTYPE) |
			(i2c_config->CLK_stretch << NOSTRETCH) | (i2c_config->gen_call << ENGC) |
			(i2c_config->PEC_en_dis << ENPEC);

		I2C_X->CR2 |= (i2c_config->last_transfer << LAST) | (i2c_config->PCLK_freq_in_mhz << FREQ);

		I2C_X->CCR |= (i2c_config->master_mode << F_S) | (i2c_config->duty << DUTY);

		/* Bit 14 Should always be kept at 1 by software */
		I2C_X->OAR1 |= (1 << 14);

		I2C_X->OAR1 |= (i2c_config->addr_mode << ADDMODE);



		/* PCLK1 must be at least 2 MHz to achieve Sm mode I²C frequencies */
		if (i2c_config->master_mode == SM_MODE && (i2c_config->PCLK_freq_in_mhz >= 2))
		{
			uint32_t CCR_value = (i2c_config->PCLK_freq_in_mhz * 1000000) / (2 * i2c_config->SCL_freq_in_khz * 1000);

			I2C_X->CCR |= (CCR_value << CCR);

			/* configure rise time */
			I2C_X->TRISE = (i2c_config->PCLK_freq_in_mhz + 1);                                 /*  For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
																								  If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
																								  therefore the TRISE[5:0] bits must be programmed with 09h.
																								  (1000 ns / 125 ns = 8 + 1)*/
		}

		/*  It must be at least 4 MHz to achieve Fm mode I²C frequencies*/
		else if (i2c_config->master_mode == FM_MODE && (i2c_config->PCLK_freq_in_mhz >= 4))
		{
			/* do configs */
		}

		/* enable the peripheral */

		I2C_X->CR1 |= (1 << PE);

	}
	else
	{
		Local_u8_Error_State = NOK;
	}

	return Local_u8_Error_State;
}


uint8_t i2C_Send_Start_Bit(ST_I2C_Config_t* i2c_config)
{
	uint8_t Local_u8_Error_State = OK;

	uint16_t temp_read = 0;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);

	/* Enable the ACK */
	I2C_X->CR1 |= (1 << ACK);
	/* send start condition to switch to master mode */
	I2C_X->CR1 |= (1 << START);

	/* wait till SB is set */
	while (!READ_BIT(I2C_X->SR1, SB));

	/* Cleared by software by reading the SR1 register followed by writing the DR register*/
	temp_read = I2C_X->SR1;
}

uint8_t i2C_Stop(ST_I2C_Config_t* i2c_config)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);

	/* send Stop Bit */
	I2C_X->CR1 |= (1 << STOP);
}

uint8_t i2C_Send_7_Bit_Slave_Address_With_Write(ST_I2C_Config_t* i2c_config, uint8_t slave_address)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);

	/* Send Address */
	I2C_X->DR |= (slave_address << 1) & (MASTER_WRITE_ADDRESS_MASK);    /* LSB is 0 for write */

	/* wait for ADDR bit to set */
	while (!(READ_BIT(I2C_X->SR1, ADDR)));

	/* ADDR Bit cleared by reading SR1 register followed by reading SR2.*/
	uint8_t temp = I2C_X->SR1 | I2C_X->SR2;  // read SR1 and SR2 to clear the ADDR bit
}

uint8_t i2C_Send_7_Bit_Slave_Address_With_Read(ST_I2C_Config_t* i2c_config, uint8_t slave_address)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);

	/* Send Address */
	I2C_X->DR |= (slave_address << 1) | (0x00000001);    /* LSB is 0 for Read */

	/* wait for ADDR bit to set */
	while (!(READ_BIT(I2C_X->SR1, ADDR)));

	/* ADDR Bit cleared by reading SR1 register followed by reading SR2.*/
	uint8_t temp = I2C_X->SR1 | I2C_X->SR2;  // read SR1 and SR2 to clear the ADDR bit
}

uint8_t i2C_Send_Byte(ST_I2C_Config_t* i2c_config, uint8_t data)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);

	/* wait for TXE bit to set */
	while (!READ_BIT(I2C_X->SR1, TxE));

	I2C_X->DR = data;

	/* wait for TXE bit to set */
	while (!READ_BIT(I2C_X->SR1, TxE));
}

uint8_t i2C_Send_Mem_Address(ST_I2C_Config_t* i2c_config, uint8_t mem_address);


uint8_t i2C_Master_Transmit_DMA(ST_I2C_Config_t* i2c_config, uint16_t slave_address, uint32_t Src_Addr, uint32_t data_len)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);
	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (i2c_config->dma_used) * 0x400);


	/* Monitor the BUSY bit of I2C_SR2 (Status 2) register until the bus is idl */
	while (READ_BIT(I2C_X->SR2, BUSY));

	i2C_Send_Start_Bit(i2c_config);

	/* DMAEN bit must be set in the I2C_CR2 register before the ADDR event. */
	SET_BIT(I2C_X->CR2, DMAEN);

	i2C_Send_7_Bit_Slave_Address_With_Write(i2c_config, slave_address);

	/* Set the I2C_DR register address in the DMA_SxPAR register */
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Tx].DMA_SPAR = (uint32_t)(&I2C_X->DR);

	/* Set the memory address in the DMA_SxMA0R register The data are loaded into I2C_DR from this memory after each TxE event.*/
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Tx].DMA_SM0AR = Src_Addr;

	/* Configure the total number of bytes to be transferred in the DMA_SxNDTR register.After each TxE event, this value is decremented.*/
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Tx].DMA_SNDTR = data_len;

	/* enable Event interrupt  */
	I2C_X->CR2 |= (1 << ITEVTEN);

	/* Activate the stream by setting the EN bit in the DMA_SxCR register.*/
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Tx].DMA_SCR |= (1 << 0);     // EN  bit is zero

	return Local_u8_Error_State;
}


uint8_t i2C_Master_Receive_DMA(ST_I2C_Config_t* i2c_config, uint16_t slave_address, uint32_t Dest_Addr, uint32_t data_len)
{
	uint8_t Local_u8_Error_State = OK;

	ST_I2C_RegDef_t* I2C_X = (ST_I2C_RegDef_t*)((uint32_t)&I2C->I2C1.CR1 + (i2c_config->i2c_num) * 0x400);
	ST_DMA_RegDef_t* DMA_X = (ST_DMA_RegDef_t*)((uint32_t)DMA->DMA1_Peripheral.DMA_ISR + (i2c_config->dma_used) * 0x400);


	/* Monitor the BUSY bit of I2C_SR2 (Status 2) register until the bus is idl */

	while (READ_BIT(I2C_X->SR2, BUSY));

	i2C_Send_Start_Bit(i2c_config);

	/* DMAEN bit must be set in the I2C_CR2 register before the ADDR event. */
	SET_BIT(I2C_X->CR2, DMAEN);

	i2C_Send_7_Bit_Slave_Address_With_Read(i2c_config, slave_address);

	/* now start read the data */

	/* Set the I2C_DR register address in the DMA_SxPAR register */
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Rx].DMA_SPAR = (uint32_t)(&I2C_X->DR);

	/* Set the memory address in the DMA_SxMA0R register The data are loaded into I2C_DR from this memory after each TxE event.*/
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Rx].DMA_SM0AR = Dest_Addr;

	/* Configure the total number of bytes to be transferred in the DMA_SxNDTR register.After each TxE event, this value is decremented.*/
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Rx].DMA_SNDTR = data_len;

	/* enable Event interrupt & in the I2C_CR2 register, the LAST bit is set, I2C
*****  automatically sends a NACK after the next byte following EOT_1. The user can
*****  generate a Stop condition in the DMA Transfer Complete interrupt routine if enabled
*****  */
	I2C_X->CR2 |= (1 << ITEVTEN) | (1 << LAST);

	/* Activate the stream by setting the EN bit in the DMA_SxCR register.*/
	DMA_X->DMA_Stream[i2c_config->dma_stream_used_Rx].DMA_SCR |= (1 << 0);     // EN  bit is zero


	return Local_u8_Error_State;
}






/* ISRs*/

void I2C1_EV_IRQHandler(void)
{
	if (READ_BIT(I2C->I2C1.SR1, SB))
	{
		Flag_State = START_SEND;
	}
	if (READ_BIT(I2C->I2C1.SR1, ADDR))
	{
		Flag_State = ADDRESS_SEND;
	}
	if (READ_BIT(I2C->I2C1.SR1, BTF))
	{
		Flag_State = BYTE_FINISHED;
	}
	if (READ_BIT(I2C->I2C1.SR1, ADD10))
	{
		Flag_State = ADDRESS_10_SEND;
	}
	if (READ_BIT(I2C->I2C1.SR1, STOPF))
	{
		Flag_State = STOP_SEND;
	}
	if (READ_BIT(I2C->I2C1.SR1, RxNE))
	{
		Flag_State = DATA_REGISTER_NOT_EMPTY;
	}
	if (READ_BIT(I2C->I2C1.SR1, TxE))
	{
		Flag_State = DATA_REGISTER_EMPTY;
		DMA->DMA1_Peripheral.DMA_Stream[STREAM6_USED_I2C].DMA_SCR &= ~(1 << 0);

		I2C->I2C1.CR1 |= (1 << STOP);
	}
}
void I2C2_EV_IRQHandler(void);
void I2C3_EV_IRQHandler(void);


void I2C1_ER_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void I2C3_ER_IRQHandler(void);


