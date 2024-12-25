#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H



typedef enum
{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
}EN_Port_t;
	
typedef enum
{
	PIN0  ,
	PIN1  ,
	PIN2  ,
	PIN3  ,
	PIN4  ,
	PIN5  ,
	PIN6  ,
	PIN7  ,
	PIN8  ,
	PIN9  ,
	PIN10 ,
	PIN11 ,
	PIN12 ,
	PIN13 ,
	PIN14 ,
	PIN15 
	
}EN_Pin_t;	

typedef enum
{
	INPUT , 
	OUTPUT , 
	ALTERNATE_FUNCTION ,
	ANALOG 

}EN_Mode_t;

typedef enum
{
	LOW , 
	MEDIUM,
	FAST , 
	HIGH
	
}EN_OutputSpeed_t;	


typedef enum
{
	PUSH_PULL , 
	OPEN_DRAIN
	
}EN_OutputType_t;

typedef enum
{
	PIN_LOW ,
	PIN_HIGH
	
}EN_Pin_Value_t;

typedef enum
{
	NO_PULL ,
	PULL_UP , 
	PULL_DOWN
	
}EN_Pull_Up_Down_t;

typedef enum
{
	AF0  ,
	AF1  ,
	AF2  ,
	AF3  ,
	AF4  ,
	AF5  ,
	AF6  ,
	AF7  ,
	AF8  ,
	AF9  ,
	AF10 ,
	AF11 ,
	AF12 ,
	AF13 ,
	AF14 ,
	AF15 
	
}EN_Alt_Func_t;

typedef struct
{
   EN_Port_t Port_X;
   EN_Mode_t mode ;
   EN_OutputSpeed_t speed;
   EN_Pin_t Pin_Num ;
   EN_OutputType_t Output_Type ;
   EN_Alt_Func_t Alt_Func ;
   EN_Pull_Up_Down_t PullType ;
	
}ST_Pin_Config;


uint8_t GPIO_u8PIN_init(const ST_Pin_Config* pin_config);

uint8_t GPIO_u8Set_Pin_Value(EN_Port_t port , EN_Pin_t pin , EN_Pin_Value_t Pin_Value);

uint8_t GPIO_u8Toggle_Pin_Value(EN_Port_t port , EN_Pin_t pin);

uint8_t GPIO_u8Read_Pin_Value(EN_Port_t port , EN_Pin_t pin , EN_Pin_Value_t* Pin_Value);  // save value in pointer passed to function

#endif
