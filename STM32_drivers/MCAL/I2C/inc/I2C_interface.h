#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H



typedef enum
{
	CLOCK_STRETCHING_DISABLED,
	CLOCK_STRETCHING_ENABLED,
}EN_CLOCK_STRETCHING_t;            /* this used in slave mode */

typedef enum
{
	GENERAL_CALL_DISABLED,
	GENERAL_CALL_ENABLE,
}EN_GENERAL_CALL_t;



typedef enum
{
	PEC_CALCULATION_DISABLED,
	PEC_CALCULATION_ENABLE,
}EN_Packet_Error_Checking_t;



typedef enum
{
	ARP_DISABLED,
	ARP_ENABLE,
}EN_ARP_t;



typedef enum
{
	SMBUS_DEVICE,
	SMBUS_HOST,
}EN_SMBus_Type_t;


typedef enum
{
	I2C_MODE,
	SMBUS_MODE,
}EN_SMBus_Mode_t;



typedef enum
{
	NEXT_DMA_EOT_IS_NOT_THE_LAST_TRANSFER,
	NEXT_DMA_EOT_IS_THE_LAST_TRANSFER,
}EN_DMA_Last_Transfer_t;


typedef enum
{
	SM_MODE,
	FM_MODE,
}EN_Master_Mode_Selection_t;


typedef enum
{
	FM_MODE_DUTY_2,
	FM_MODE_DUTY_16_OVER_9,
}EN_Fm_Mode_Duty_Cycle_t;



typedef enum
{
	SLAVE_ADDRESS_7_BIT,
	SLAVE_ADDRESS_10_BIT,
}EN_Addressing_Mode_t;


typedef enum
{
	DUAL_ADDRESSING_MODE_ENABLE,
	DUAL_ADDRESSING_MODE_DISABLE,
}EN_Dual_Addressing_Mode_t;



typedef enum
{
	I2C_NUM_1,
	I2C_NUM_2,
	I2C_NUM_3,

}EN_I2C_Num_t;


typedef enum
{
	DMA1_USED,
	DMA2_USED,
}EN_DMA_Used_In_I2C_t;

typedef enum
{
	STREAM0_USED_I2C,
	STREAM1_USED_I2C,
	STREAM2_USED_I2C,
	STREAM3_USED_I2C,
	STREAM4_USED_I2C,
	STREAM5_USED_I2C,
	STREAM6_USED_I2C,
	STREAM7_USED_I2C,

}EN_DMA_Stream_Used_In_I2C_t;

typedef struct
{
	EN_I2C_Num_t i2c_num;
	EN_DMA_Last_Transfer_t last_transfer;
	EN_CLOCK_STRETCHING_t CLK_stretch;
	EN_GENERAL_CALL_t gen_call;
	EN_Packet_Error_Checking_t PEC_en_dis;
	EN_SMBus_Mode_t smbus_mode;
	EN_SMBus_Type_t smbus_type;
	EN_Master_Mode_Selection_t master_mode;
	EN_Fm_Mode_Duty_Cycle_t duty;
	EN_Addressing_Mode_t addr_mode;
	EN_Dual_Addressing_Mode_t dual_add_mode;
	EN_DMA_Used_In_I2C_t dma_used;
	EN_DMA_Stream_Used_In_I2C_t dma_stream_used_Tx;
	EN_DMA_Stream_Used_In_I2C_t dma_stream_used_Rx;
	uint32_t Own_Address_1;
	uint32_t Own_Address_2;
	uint8_t PCLK_freq_in_mhz;                                /* freq must be in range 2MHZ to 45MHZ*/
	uint8_t SCL_freq_in_khz;

}ST_I2C_Config_t;




uint8_t I2C_init(ST_I2C_Config_t* i2c_config);

uint8_t i2C_Master_Transmit_DMA(ST_I2C_Config_t* i2c_config, uint16_t slave_address, uint32_t Src_Addr, uint32_t data_len);

uint8_t i2C_Master_Receive_DMA(ST_I2C_Config_t* i2c_config, uint16_t slave_address, uint32_t Dest_Addr, uint32_t data_len);

uint8_t i2C_Slave_Transmit_DMA(ST_I2C_Config_t* i2c_config, uint16_t slave_address, uint32_t Src_Addr, uint16_t data_len);

uint8_t i2C_Slave_Receive_DMA(ST_I2C_Config_t* i2c_config, uint16_t slave_address, uint32_t Src_Addr, uint16_t data_len);

static uint8_t i2C_Send_Start_Bit(ST_I2C_Config_t* i2c_config);

static uint8_t i2C_Send_7_Bit_Slave_Address_With_Write(ST_I2C_Config_t* i2c_config, uint8_t slave_address);

static uint8_t i2C_Send_7_Bit_Slave_Address_With_Read(ST_I2C_Config_t* i2c_config, uint8_t slave_address);

static uint8_t i2C_Send_Mem_Address(ST_I2C_Config_t* i2c_config, uint8_t mem_address);

static uint8_t i2C_Send_Byte(ST_I2C_Config_t* i2c_config, uint8_t data);

static uint8_t i2C_Stop(ST_I2C_Config_t* i2c_config);




#endif
