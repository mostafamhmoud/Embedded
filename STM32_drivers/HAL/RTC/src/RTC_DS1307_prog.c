#include <stdint.h>
#include "../../../Common/Error_type.h"
#include "../../../MCAL/I2C/inc/I2C_interface.h"
#include "../../../MCAL/I2C/inc/I2C_private.h"
#include "../inc/RTC_DS1307_interface.h"
#include "../inc/RTC_DS1307_private.h"



void Convert_to_BCD(ST_RTC_DS1307_Date_t* date)
{
	/*** Bit 7 of register 0 (seconds register ) is the clock halt (CH) bit. When this bit is set to a 1,
	the oscillator is disabled. When cleared to a 0, the oscillator is enabled */
	date->seconds = ((date->seconds % 10) | ((date->seconds / 10) << 4)) & (0x01111111); //
	date->min = (date->min % 10) | ((date->min / 10) << 4);
	date->hours = (date->hours % 10) | ((date->hours / 10) << 4);
	date->day = date->day;
	date->date = (date->date % 10) | ((date->date / 10) << 4);
	date->month = (date->month % 10) | ((date->month / 10) << 4);
	date->year = (date->year % 10) | ((date->year / 10) << 4);
}

void Convert_to_Num(ST_RTC_DS1307_Date_t* date)
{
	date->seconds = (date->seconds >> 4) * 10 + ((date->seconds << 4) >> 4);
	date->min = (date->min >> 4) * 10 + ((date->seconds << 4) >> 4);
	date->hours = (date->hours >> 4) * 10 + ((date->hours << 4) >> 4);
	date->day = date->day;
	date->date = (date->date >> 4) * 10 + ((date->date << 4) >> 4);
	date->month = (date->month >> 4) * 10 + ((date->month << 4) >> 4);
	date->year = (date->year >> 4) * 10 + ((date->year << 4) >> 4);
}

uint8_t RTC_DS1307_Set_Date(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* date)
{
	Convert_to_BCD(date);

	/* set pointer register in RTC_DS1307 to first reg */
	date->RTC_Reg_Pointer = SECONDS_REG_ADDRESS;

	i2C_Master_Transmit_DMA(i2c_config, RTC_DS1307_ADDRESS, date, 8); // 8 because of the rtc_reg_pointer
}

uint8_t RTC_DS1307_Read_Date(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* date)
{

	/* set pointer register in RTC_DS1307 to first reg */
	date->RTC_Reg_Pointer = SECONDS_REG_ADDRESS;

	i2C_Master_Receive_DMA(i2c_config, RTC_DS1307_ADDRESS, date, 8);

	Convert_to_Num(date);
}

uint8_t RTC_DS1307_init(ST_I2C_Config_t* i2c_config)
{
	i2C_Send_Start_Bit(i2c_config);

	i2C_Send_7_Bit_Slave_Address_With_Write(i2c_config, RTC_DS1307_ADDRESS);

	i2C_Send_Byte(i2c_config, CONTROL_ADDRESS); // Write 0x00 to Control register to disable SQW-Out

	i2C_Send_Byte(i2c_config, 0x00);

	i2C_Stop(i2c_config);
}


uint8_t RTC_DS1307_Write_Seconds(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* date)
{
	/* convert to BCD */
	date->seconds = (date->seconds >> 4) * 10 + ((date->seconds << 4) >> 4);

	/* set pointer register in RTC_DS1307 to Seconds register */
	date->RTC_Reg_Pointer = SECONDS_REG_ADDRESS;

	i2C_Master_Transmit_DMA(i2c_config, RTC_DS1307_ADDRESS, &(date->seconds), 2);
}
uint8_t RTC_DS1307_Write_Min(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* data);
uint8_t RTC_DS1307_Write_Hours(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* data);
uint8_t RTC_DS1307_Write_Day(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* data);
uint8_t RTC_DS1307_Write_Month(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* data);
uint8_t RTC_DS1307_Write_Year(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* data);





