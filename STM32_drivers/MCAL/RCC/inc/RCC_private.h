#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#define IS_PLLM_DEVISION_FACTOR_CORRECT(x)        ((x >= 2)  && (x <= 63))
#define IS_PLLN_MULTIPLICATION_FACTOR_CORRECT(x)  ((x >=50) && (x <= 432))
#define IS_PLLP_DEVISION_FACTOR_CORRECT(x)        (x%2 == 0  && x <= 8 && x > 0 ) /* Main PLL (PLL) division factor for main system clock */

#define IS_AHB_PRESCALER_CORRECT(x)  (((x >= 8) && (x <= 15)) || (x == 0))
#define IS_APB1_PRESCALER_CORRECT(x) (((x >= 4) && (x <= 7)) || (x == 0))
#define IS_APB2_PRESCALER_CORRECT(x) (((x >= 4) && (x <= 7)) || (x == 0))


#define CLOCK_SWITCH_MASK                 0b11
#define PLLN_MULTIPLICATION_FACTOR_MASK   0xFFFF803F
#define PLLM_DEVISION_FACTOR_MASK         0xFFFFFFE0
#define PLLP_DEVISION_FACTOR_MASK         0xFFFCFFFF
#define AHP_PRESCALER_MASK                0xFFFFFF0F
#define APB1_PRESCALER_MASK               0xFFFFE3FF
#define APB2_PRESCALER_MASK               0xFFFF1FFF

#define PERIPHERAL_IN_RCC_AHB1ENR(peripheral_idx) (peripheral_idx < 32)
#define PERIPHERAL_IN_RCC_AHB2ENR(peripheral_idx) (peripheral_idx >= 32 && peripheral_idx < 64)
#define PERIPHERAL_IN_RCC_AHB3ENR(peripheral_idx) (peripheral_idx >= 64 && peripheral_idx < 96)
#define PERIPHERAL_IN_RCC_APB1ENR(peripheral_idx) (peripheral_idx >= 96 && peripheral_idx < 128)
#define PERIPHERAL_IN_RCC_APB2ENR(peripheral_idx) (peripheral_idx >= 128 && peripheral_idx < 160)



#endif // !RCC_PRIVATE_H

