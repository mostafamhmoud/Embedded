#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H



#define NULL (void*)0

#define OK                                   1u
#define NOK                                  2u
#define NULL_PTR_ERR                         3u
#define TIMEOUT_ERR                          4u
#define PLL_CLK_SRC_ERR                      5u
#define PLLM_DEVISION_FACTOR_ERR             6u
#define PLLN_MULTIPLICATION_FACTOR_ERR       7u
#define PLLP_DEVISION_FACTOR_ERR             8u
#define AHB_PRESCALER_ERR                    9u
#define APB1_PRESCALER_ERR                   10u
#define APB2_PRESCALER_ERR                   11u
#define PERIPHERAL_NOT_FOUND_ERR             12u
#define CLK_SRC_ERR                          13u
#define PORTS_PINS_ERR                       15u
#define IRQn_SRC_ERR                         16u

#define PRI_GROUO_ERR                        17u


#define EXTI_INIT_STATE_ERR                  18u
#define EXTI_TRIG_STATE_ERR                  19u
#define EXTI_LINE_NUM_ERR                    20u
#define SYSCFG_LINE_NUM_ERR                  21u

#define DMA_SELECT_ERR                       22u
#define DMA_NUM_STREAM_ERR                   23u
#define DMA_STREAM_MODE_ERR                  24u
#define DMA_STREAM_PRIORITY_ERR              25u
#define DMA_FIFO_THRESHOLD_ERR               26u
#define DMA_CHANNEL_ERR                      27u
#define DMA_DIR_ERR                          28u
#define DMA_MEM_ALLIGN_ERR                   29u
#define DMA_PERIPH_ALLIGN_ERR                30u
#define DMA_IT_TYPES_ERR                     31u





#endif
