#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H



/********************************
 * Control Register Pins *
 ********************************/

enum
{
	HSION,
	HSIRDY,
	HSITRIM0 = 3,
	HSITRIM1,
	HSITRIM2,
	HSITRIM3,
	HSITRIM4,
	HSICAL0,
	HSICAL1,
	HSICAL2,
	HSICAL3,
	HSICAL4,
	HSICAL5,
	HSICAL6,
	HSICAL7,
	HSEON,
	HSERDY,
	HSEBYP,
	CSSON,
	PLLON = 24,
	PLLRDY,
	PLLI2SON,
	PLLI2SRDY,
	PLLSAION,
	PLLSAIRDY
};

/********************************
 * PLL Configuration register Pins *
 ********************************/

enum
{
	PLLM0,
	PLLN0 = 6,
	PLLP0 = 16,
	PLLSRC = 22,
	PLLQ0 = 24,
	PLLR0 = 28
};

/********************************
 * RCC Configuration registers Pins *
 ********************************/

enum
{
	SW0,
	SWS0 = 2,
	HPRE0 = 4,
	PPRE10 = 10,
	PPRE20 = 13,
	RTCPRE = 16,
	MCO1 = 21,
	MCO1PRE = 24,
	MCO2PRE = 27,
	MCO2 = 30
};

/********************************
 * RCC clock interrupt register Pins *
 ********************************/

enum
{
	LSIRDYF,
	LSERDYF,
	HSIRDYF,
	HSERDYF,
	PLLRDYF,
	PLLI2SRDYF,
	PLLSAIRDYF,
	CSSF,
	LSIRDYIE,
	LSERDYIE,
	HSIRDYIE,
	HSERDYIE,
	PLLRDYIE,
	PLLI2SRDYIE,
	PLLSAIRDYIE,
	LSIRDYC = 16,
	LSERDYC,
	HSIRDYC,
	HSERDYC,
	PLLRDYC,
	PLLI2SRDYC,
	PLLSAIRDYC,
	CSSC
};

/********************************
 * RCC AHB1 peripheral reset register (RCC_AHB1RSTR) pins *
 ********************************/

enum
{
	GPIOARST,
	GPIOBRST,
	GPIOCRST,
	GPIODRST,
	GPIOERST,
	GPIOFRST,
	GPIOGRST,
	GPIOHRST,

	CRCRST = 12,
	DMA1RST = 21,
	DMA2RST,
	OTGHSRST = 29
};

/********************************
 * RCC AHB2 peripheral reset register (RCC_AHB2RSTR) pins *
 ********************************/

enum
{
	DCMIRST = 32,
	OTGFSRST = 39
};

/********************************
 * RCC AHB3 peripheral reset register (RCC_AHB3RSTR) pins *
 ********************************/

enum
{
	FMCRST = 64,
	QSPIRST
};

/********************************
 *RCC APB1 peripheral reset register (RCC_APB1RSTR) pins *
 ********************************/

enum
{
	TIM2RST = 96,
	TIM3RST,
	TIM4RST,
	TIM5RST,
	TIM6RST,
	TIM7RST,
	TIM12RST,
	TIM13RST,
	TIM14RST,
	WWDGRST = 107,
	SPI2RST = 110,
	SPI3RST,
	SPDIFRXRST,
	USART2RST,
	USART3RST,
	UART4RST,
	UART5RST,
	I2C1RST,
	I2C2RST,
	I2C3RST,
	IFMPI2C1RST,
	CAN1RST,
	CAN2RST,
	CECRST,
	PWRRST,
	DACRST,
};

/********************************
 *RCC APB2 peripheral reset register (RCC_APB2RSTR) pins *
 ********************************/

enum
{
	TIM1RST = 128,
	TIM8RST,
	USART1RST = 132,
	USART6RST,
	ADCRST = 136,
	SDIORST = 139,
	SPI1RST,
	SPI4RST,
	SYSCFGRST,
	TIM9RST = 144,
	TIM10RST,
	TIM11RST,
	SAI1RST = 150,
	SAI2RST
};


/********************************
 * RCC AHB1 peripheral clock enable register (RCC_AHB1ENR) pins *
 ********************************/

enum
{
	GPIOAEN,
	GPIOBEN,
	GPIOCEN,
	GPIODEN,
	GPIOEEN,
	GPIOFEN,
	GPIOGEN,
	GPIOHEN,

	CRCEN = 12,
	BKPSRAMEN = 18,
	DMA1EN = 21,
	DMA2EN,
	OTGHSEN = 29,
};


/********************************
 * RCC AHB2 peripheral clock enable register (RCC_AHB2ENR) pins *
 ********************************/

enum
{
	DCMIEN = 32,
	OTGFSEN = 39
};


/********************************
 * RCC AHB3 peripheral clock enable register (RCC_AHB3ENR) pins *
 ********************************/

enum
{
	FMCEN = 64,
	QSPIEN
};

/********************************
 * RCC APB1 peripheral clock enable register (RCC_APB1ENR) pins *
 ********************************/

enum
{
	TIM2EN = 96,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	TIM6EN,
	TIM7EN,
	TIM12EN,
	TIM13EN,
	TIM14EN,
	WWDGEN = 107,
	SPI2EN = 110,
	SPI3EN,
	SPDIFRXEN,
	USART2EN,
	USART3EN,
	UART4EN,
	UART5EN,
	I2C1EN,
	I2C2EN,
	I2C3EN,
	IFMPI2C1EN,
	CAN1EN,
	CAN2EN,
	CECEN,
	PWREN,
	DACEN,
};


/********************************
 * RCC APB2 peripheral clock enable register (RCC_APB2ENR) pins *
 ********************************/

enum
{
	TIM1EN = 128,
	TIM8EN,
	USART1EN = 132,
	USART6EN,
	ADC1EN = 136,
	ADC2EN,
	ADC3EN,
	SDIOEN,
	SPI1EN,
	SPI4EN,
	SYSCFGEN,
	TIM9EN = 144,
	TIM10EN,
	TIM11EN,
	SAI1EN = 150,
	SAI2EN
};


/* * * * * * * * * * * * * * *
 *   system clock source *
 * * * * * * * * * * * * * * */
typedef enum
{
	HSI_system_clock_select,
	HSE_system_clock_select,
	PLL_P_system_clock_select,
	PLL_R_system_clock_select
}EN_SysClk_Type_t;

/* * * * * * * * * * * * * * *
 *   APB2 low-speed prescaler    *
 * * * * * * * * * * * * * * */
typedef enum
{
	APB2_HCLK_not_divided,
	APB2_HCLK_divided_by_2 = 4,
	APB2_HCLK_divided_by_4,
	APB2_HCLK_divided_by_8,
	APB2_HCLK_divided_by_16,
}EN_APB2_HClk_Prescaler_t;

/* * * * * * * * * * * * * * *
 *   APB1 low-speed prescaler    *
 * * * * * * * * * * * * * * */
typedef enum
{
	APB1_HCLK_not_divided,
	APB1_HCLK_divided_by_2 = 4,
	APB1_HCLK_divided_by_4,
	APB1_HCLK_divided_by_8,
	APB1_HCLK_divided_by_16,
}EN_APB1_HClk_Prescaler_t;

/* * * * * * * * * * * * * * *
 *   AHP prescaler  *
 * * * * * * * * * * * * * * */
typedef enum
{
	AHB_SYSCLK_not_devided,
	AHB_SYSCLK_devided_by_2 = 8,
	AHB_SYSCLK_devided_by_4,
	AHB_SYSCLK_devided_by_8,
	AHB_SYSCLK_devided_by_16,
	AHB_SYSCLK_devided_by_64,
	AHB_SYSCLK_devided_by_128,
	AHB_SYSCLK_devided_by_256,
	AHB_SYSCLK_devided_by_512
}EN_AHP_SysClk_Prescaler_t;

/* * * * * * * * * * * *
 *   PLL CLK Source    *
 * * * * * * * * * * * */
typedef enum
{
	HSI,
	HSE,
}EN_PLL_Clk_Source_t;

typedef enum
{
	PLLP_devided_by_2,
	PLLP_devided_by_4,
	PLLP_devided_by_6,
	PLLP_devided_by_8,
}EN_PLLP_Precaler_t;

typedef struct
{
	EN_SysClk_Type_t Sys_Clk_Select;
	EN_AHP_SysClk_Prescaler_t AHP_Pres;
	EN_APB1_HClk_Prescaler_t APB1_Pres;
	EN_APB2_HClk_Prescaler_t APB2_Pres;
	uint8_t PLLM_Pres;    /* this  prescaler value ranges from 2 to 63 */
	uint16_t PLLN_Factor; /* this  multiplication factor ranges from 50 to 432 */
	EN_PLLP_Precaler_t PLLP_Pres;
	EN_PLL_Clk_Source_t PLL_clk_src;

}ST_RCC_Config_t;









uint8_t RCC_Enable_HSI(void);
uint8_t RCC_Enable_HSE(void);
uint8_t RCC_Enable_PLL(ST_RCC_Config_t* st_rcc_config);

uint8_t RCC_Enable_LSI(void);
uint8_t RCC_Enable_LSE(void);

uint8_t RCC_MCO_CLK(uint8_t MCO_CLK_source);

uint8_t AHP_Prescaler(EN_AHP_SysClk_Prescaler_t AHP_prescaler_value);
uint8_t APB1_Prescaler(EN_APB1_HClk_Prescaler_t APB1_prescaler_value);
uint8_t APB2_Prescaler(EN_APB2_HClk_Prescaler_t APB2_prescaler_value);

uint8_t ADC_Prescaler(uint8_t ADC_prescaler_value);
uint8_t USB_Prescaler(uint8_t USB_prescaler_value);

uint8_t RCC_Enable_Peripheral(uint8_t peripheral_idx);
uint8_t RCC_Disable_Peripheral(uint8_t peripheral_idx);

uint8_t RCC_Config(ST_RCC_Config_t* st_rcc_config);


#endif
