#ifndef RTC_DS1307_INTERFACE_H
#define RTC_DS1307_INTERFACE_H



typedef struct
{
	uint8_t RTC_Reg_Pointer;

	uint8_t seconds;
	uint8_t min;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;

}ST_RTC_DS1307_Date_t;



uint8_t RTC_DS1307_Write_Seconds(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* seconds);
uint8_t RTC_DS1307_Write_Min(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* min);
uint8_t RTC_DS1307_Write_Hours(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* hours);
uint8_t RTC_DS1307_Write_Day(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* day);
uint8_t RTC_DS1307_Write_Month(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* month);
uint8_t RTC_DS1307_Write_Year(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* year);

uint8_t RTC_DS1307_init(ST_I2C_Config_t* i2c_config);

uint8_t RTC_DS1307_Set_Date(ST_I2C_Config_t* i2c_config, ST_RTC_DS1307_Date_t* date);

void Convert_to_BCD(ST_RTC_DS1307_Date_t* date);
void Convert_to_Num(ST_RTC_DS1307_Date_t* date);

#endif
