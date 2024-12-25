#ifndef STM32F446xx_H
#define STM32F446xx_H


#define SET_BIT(register_x , bit_x) (register_x |= (1<<bit_x))
#define CLEAR_BIT(register_x , bit_x) (register_x &= ~(1<<bit_x))
#define TOGGLE_BIT(register_x , bit_x) (register_x ^= (1<<bit_x))
#define READ_BIT(register_x , bit_x) ((register_x & (1<<bit_x)) >> bit_x)




/***************************         CORE Peripherals Base Address        ***************/

#define SYSTICK_BASE_ADDRESS               0xE000E010


/***************************         Various memories Base Address        ***************/

#define FLASH_BASE_ADDRESS           0x08000000UL
#define SRAM_BASE_ADDRESS            0x20000000UL
#define ROM_BASE_ADDRESS             0x1FFF0000UL


/***************************         AHB1 Peripheral Base Address        ***************/

#define GPIOA_BASE_ADRESS             0x40020000U
#define GPIOB_BASE_ADRESS             0x40020400U
#define GPIOC_BASE_ADRESS             0x40020800U
#define GPIOD_BASE_ADRESS             0x40020C00U
#define GPIOE_BASE_ADRESS             0x40021000U
#define GPIOF_BASE_ADRESS             0x40021400U
#define GPIOG_BASE_ADRESS             0x40021800U
#define GPIOH_BASE_ADRESS             0x40021C00U

#define RCC_BASE_ADRESS               0x40023800U


#define DMA_BASE_ADDRESS            0x40026000

#define DMA1_BASE_ADDRESS            0x40026000

#define DMA2_BASE_ADDRESS            0x40026400



/***************************         AHB2 Peripheral Base Address    90MHZ MAX Speed          ********************/

#define USART1_BASE_ADRESS               0x40011000U
#define USART6_BASE_ADRESS               0x40011400U


/***************************         AHB3 Peripheral Base Address         ***************/




/***************************         APB1 Peripheral Base Address     45MHZ MAX Speed    ***************/

#define USART2_BASE_ADRESS               0x40004800U
#define USART3_BASE_ADRESS               0x40004400U

#define UART4_BASE_ADRESS               0x40004C00U
#define UART5_BASE_ADRESS               0x40005000U


/***************************         APB2 Peripheral Base Address         ***************/

#define SPI_BASE_ADRESS                           0x40013000

#define SPI1_BASE_ADRESS                           0x40013000
#define SPI4_BASE_ADRESS                           0x40013400
#define SPI2_BASE_ADRESS                           0x40013800
#define SPI3_BASE_ADRESS                           0x40013C00



#define I2C_BASE_ADRESS                            0x40005400

#define I2C1_BASE_ADRESS                           0x40005400
#define I2C2_BASE_ADRESS                           0x40005800
#define I2C3_BASE_ADRESS                           0x40005C00


/***************************         NVIC Peripheral Registers Base Address         ***************/

#define  NVIC_ISER_BASE_ADDRESS      0xE000E100 
#define  NVIC_ICER_BASE_ADDRESS      0xE000E180 
#define  NVIC_ISPR_BASE_ADDRESS      0xE000E200 
#define  NVIC_ICPR_BASE_ADDRESS      0xE000E280 
#define  NVIC_IABR_BASE_ADDRESS      0xE000E300 
#define  NVIC_IPR_BASE_ADDRESS       0xE000E400 



/***************************         EXTI Peripheral Registers Base Address         ***************/

#define  EXTI_BASE_ADDRESS      0x40013C00 



/***************************         SYSCFG Peripheral Registers Base Address         ***************/

#define  SYSCFG_BASE_ADDRESS      0x40013800 



/***************************         SCB Peripheral Registers Base Address         ***************/

//#define SCB_BASE_ADDRESS            0xE000E008  // start from ACTLR Resgister

#define SCB_BASE_ADDRESS            0xE000ED00   // // start from CPUID Resgister



/***************************         GPIO Register Definition Structure   ***************/

typedef struct
{
	volatile uint32_t MODER;                  /*GPIO PORT Mode Register*/
	volatile uint32_t OTYPER;                 /*GPIO PORT Output Type Register*/
	volatile uint32_t OSPEEDER;               /*GPIO PORT Output Speed Register*/
	volatile uint32_t PUPDR;                  /*GPIO PORT Pull Up/Down Register*/
	volatile uint32_t IDR;                    /*GPIO PORT Input Data Register*/
	volatile uint32_t ODR;                    /*GPIO PORT Output Data Register*/
	volatile uint32_t BSRR;                   /*GPIO PORT Bit Set/Reset Register*/
	volatile uint32_t LCKR;                   /*GPIO PORT Lock Register*/
	volatile uint32_t AFR[2];                 /*GPIO PORT Alternate Function Register*/

}ST_GPIO_RegDef_t;

/***************************         RCC Register Definition Structure   ***************/

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED1;

	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED2;
	uint32_t RESERVED3;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED4;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED5;
	uint32_t RESERVED6;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t RESERVED7;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED8;
	uint32_t RESERVED9;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED10;
	uint32_t RESERVED11;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
	volatile uint32_t CKGATENR;
	volatile uint32_t DCKCFGR2;

}ST_RCC_RegDef_t;




/***************************         SYSTICK Register Definition Structure   ***************/

/* * * * * * * * * * * * * * *
 *  SYSTICK Registers Structure  *
 * * * * * * * * * * * * * * */

typedef struct
{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
}ST_SysTick_RegDef_t;



/***************************         SCB Register Definition Structure   ***************/

  /* * * * * * * * * * * * * * *
   *  SCB Registers Structure  *
   * * * * * * * * * * * * * * */

typedef struct
{
	//volatile uint32_t ACTLR;
	//volatile uint32_t space[830];
	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	volatile uint32_t VTOR;
	volatile uint32_t AIRCR;
	volatile uint32_t SCR;
	volatile uint32_t CCR;
	volatile uint32_t SHPR1;
	volatile uint32_t SHPR2;
	volatile uint32_t SHPR3;
	volatile uint32_t SHCSR;
	volatile uint32_t CFSR;
}ST_SCB_RegDef_t;


/***************************         EXTI Register Definition Structure   ***************/

  /* * * * * * * * * * * * * * *
   *  EXTI Registers Structure  *
   * * * * * * * * * * * * * * */

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}ST_EXTI_RegDef_t;


/***************************         SYSCFG Register Definition Structure   ***************/

  /* * * * * * * * * * * * * * *
   *  SYSCFG Registers Structure  *
   * * * * * * * * * * * * * * */

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	volatile uint32_t CMPCR;
	uint32_t RESERVED2[2];
	volatile uint32_t CFGR;

}ST_SYSCFG_RegDef_t;





/***************************         DMA Register Definition Structure   ***************/

  /* * * * * * * * * * * * * * *
   *  DMA Registers Structure  *
   * * * * * * * * * * * * * * */

typedef struct
{
	volatile uint32_t DMA_SCR;
	volatile uint32_t DMA_SNDTR;
	volatile uint32_t DMA_SPAR;
	volatile uint32_t DMA_SM0AR;
	volatile uint32_t DMA_SM1AR;
	volatile uint32_t DMA_SFCR;

}ST_DMA_Stream_RegDef_t;


typedef struct
{
	volatile uint32_t DMA_ISR[2];
	volatile uint32_t DMA_IFCR[2];

	ST_DMA_Stream_RegDef_t DMA_Stream[8];

}ST_DMA_RegDef_t;


typedef struct
{
	ST_DMA_RegDef_t DMA1_Peripheral;
	uint8_t space[0x330];    // 400 - (size of last struct which is (4 + (8*6))*4 = 52 elements in 4 bytes = 0x330)
	ST_DMA_RegDef_t DMA2_Peripheral;
}ST_DMA_Peripheral_t;



/***************************         USART Register Definition Structure   ***************/

/* * * * * * * * * * * * * * *
 *  USART Registers Structure  *
 * * * * * * * * * * * * * * */

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

}ST_USART_RegDef_t;


typedef struct
{
	ST_USART_RegDef_t USART1;
	uint8_t space1[0x3E4];        // 400 - (size of last struct which is 7 elements in 4 bytes = 0x3E4)
	ST_USART_RegDef_t USART6;
	uint8_t space2[0x2FE4];
	ST_USART_RegDef_t USART2;
	uint8_t space3[0x3E4];
	ST_USART_RegDef_t USART3;
	uint8_t space4[0x3E4];
	ST_USART_RegDef_t UART4;
	uint8_t space5[0x3E4];
	ST_USART_RegDef_t UART5;

}ST_USART_Peripheral_t;



/***************************         SPI Peripheral Definitions   ***************/


typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;

}ST_SPI_RegDef_t;

typedef struct
{
	ST_SPI_RegDef_t SPI1;
	uint8_t RESERVED1[0x3DC];        // 400 - (size of last struct which is 9 elements in 4 bytes = 0x3DC)
	ST_SPI_RegDef_t SPI4;
	uint8_t RESERVED2[0x3DC];
	ST_SPI_RegDef_t SPI2_I2S2;
	uint8_t RESERVED3[0x3DC];
	ST_SPI_RegDef_t SPI3_I2S3;
}ST_SPI_Peripheral_t;



/***************************         I2C Peripheral Definitions   ***************/


typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;

}ST_I2C_RegDef_t;

typedef struct
{
	ST_I2C_RegDef_t I2C1;
	uint8_t RESERVED1[0x3DE];        // 400 - (size of last struct which is 10 elements in 4 bytes = 0x3DC)
	ST_I2C_RegDef_t I2C2;
	uint8_t RESERVED2[0x3DE];
	ST_I2C_RegDef_t I2C3;

}ST_I2C_Peripheral_t;

/***************************         GPIO Peripheral Definitions   ***************/

#define GPIOA             ((ST_GPIO_RegDef_t*)GPIOA_BASE_ADRESS)
#define GPIOB             ((ST_GPIO_RegDef_t*)GPIOB_BASE_ADRESS)
#define GPIOC             ((ST_GPIO_RegDef_t*)GPIOC_BASE_ADRESS)
#define GPIOD             ((ST_GPIO_RegDef_t*)GPIOD_BASE_ADRESS)
#define GPIOE             ((ST_GPIO_RegDef_t*)GPIOE_BASE_ADRESS)
#define GPIOF             ((ST_GPIO_RegDef_t*)GPIOF_BASE_ADRESS)
#define GPIOG             ((ST_GPIO_RegDef_t*)GPIOG_BASE_ADRESS)
#define GPIOH             ((ST_GPIO_RegDef_t*)GPIOH_BASE_ADRESS)


/***************************         RCC Peripheral Definitions   ***************/

#define RCC            ((ST_RCC_RegDef_t*)RCC_BASE_ADRESS)



/***************************         NVIC Peripheral Definitions   ***************/

  /* every  register has 8 copies { ISER[0] TO ISER[7] and so on for the remaining registers except for IPR 60
  ** from IPR[0] to IPR[59]   each IRQ have 8 bits in the register so each register has configs for 4 IRQ */

#define  NVIC_ISER      ((uint32_t*)NVIC_ISER_BASE_ADDRESS)  
#define  NVIC_ICER      ((uint32_t*)NVIC_ICER_BASE_ADDRESS)
#define  NVIC_ISPR      ((uint32_t*)NVIC_ISPR_BASE_ADDRESS)
#define  NVIC_ICPR      ((uint32_t*)NVIC_ICPR_BASE_ADDRESS)
#define  NVIC_IABR      ((uint32_t*)NVIC_IABR_BASE_ADDRESS)
#define  NVIC_IPR       ((uint8_t*)NVIC_IPR_BASE_ADDRESS)    // because each IRQ priority have 1 byte  

#define  NVIC_STIR           ((uint32_t*)0xE000EF00)



  /***************************         SYSTICK Peripheral Definitions   ***************/


#define SCB       ((ST_SCB_RegDef_t*)SCB_BASE_ADDRESS)


/***************************         EXTI Peripheral Definitions   ***************/


#define EXTI       ((ST_EXTI_RegDef_t*)EXTI_BASE_ADDRESS)


/***************************         EXTI Peripheral Definitions   ***************/


#define SYSCFG       ((ST_SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)


/***************************         SYSTICK Peripheral Definitions   ***************/

#define SYSTICK              ((ST_SysTick_RegDef_t*)SYSTICK_BASE_ADDRESS)


/***************************         DMA Peripheral Definitions   ***************/

#define DMA    ((ST_DMA_Peripheral_t*)DMA_BASE_ADDRESS)


//ST_DMA_RegDef_t* DMA[2] = { (ST_DMA_RegDef_t*)DMA1_BASE_ADDRESS , (ST_DMA_RegDef_t*)DMA2_BASE_ADDRESS };


/***************************         USART Peripheral Definitions   ***************/


#define USART            ((ST_USART_Peripheral_t*)USART1_BASE_ADRESS)

/*
#define USART1            ((ST_USART_RegDef_t*)USART1_BASE_ADRESS)
#define USART2            ((ST_USART_RegDef_t*)USART2_BASE_ADRESS)
#define USART3            ((ST_USART_RegDef_t*)USART3_BASE_ADRESS)
#define UART4            ((ST_USART_RegDef_t*)UART4_BASE_ADRESS)
#define UART5            ((ST_USART_RegDef_t*)UART5_BASE_ADRESS)
#define USART6            ((ST_USART_RegDef_t*)USART6_BASE_ADRESS)

ST_USART_RegDef_t* USART[6] = { USART1 , USART2 , USART3 , UART4 , UART5 , USART6 };
*/


/***************************         SPI Peripheral Definitions   ***************/

#define SPI            ((ST_SPI_Peripheral_t*)SPI_BASE_ADRESS)



/***************************         I2C Peripheral Definitions   ***************/

#define I2C            ((ST_I2C_Peripheral_t*)I2C_BASE_ADRESS)


#endif

