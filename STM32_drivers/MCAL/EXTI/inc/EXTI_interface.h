#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H



typedef enum
{
	EXTI_LINE0  ,
	EXTI_LINE1  ,
	EXTI_LINE2  ,
	EXTI_LINE3  ,
	EXTI_LINE4  ,
	EXTI_LINE5  ,
	EXTI_LINE6  ,
	EXTI_LINE7  ,
	EXTI_LINE8  ,
	EXTI_LINE9  ,
	EXTI_LINE10  ,
	EXTI_LINE11 ,
	EXTI_LINE12 ,
	EXTI_LINE13  ,
	EXTI_LINE14  ,
	EXTI_LINE15  

}EN_EXTI_LINE_NUM_t ;




typedef enum
{
	RISING_TRIG , 
	FALLING_TRIG , 
	RISING_FALLING_TRIG ,

}EN_EXTI_TrigSrc_t;


typedef enum
{
	ENABLE ,
	DISABLE,

}EN_EXTI_InitState_t;

typedef struct
{
	EN_EXTI_LINE_NUM_t line_num;
	EN_EXTI_TrigSrc_t edge_detect;
	EN_EXTI_InitState_t init_state;
	void(*CallBackFun)(void);

}ST_EXTI_Config_t;


uint8_t EXTI_init(ST_EXTI_Config_t *copy_EXTI_config);
uint8_t EXTI_enable_Int(EN_EXTI_LINE_NUM_t copy_line_num);
uint8_t EXTI_disable_Int(EN_EXTI_LINE_NUM_t copy_line_num);
uint8_t EXTI_ClearPendingFlag(EN_EXTI_LINE_NUM_t copy_line_num);
uint8_t EXTI_GetPendingFlag(EN_EXTI_LINE_NUM_t copy_line_num , uint8_t* copy_Flag_Status);






#endif

