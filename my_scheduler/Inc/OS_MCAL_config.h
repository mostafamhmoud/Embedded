#ifndef OS_MCAL_CONFIG_H
#define OS_MCAL_CONFIG_H

#define HSI_CLK                    16000000UL
#define SYSTICK_CLK                HSI_CLK  

#define MAX_TASK_NUM               5u


#define T1_STACK_START          (SRAM_END)
#define T2_STACK_START          ((SRAM_END) - (1 * TASK_STACK_SIZE))
#define T3_STACK_START          ((SRAM_END) - (2 * TASK_STACK_SIZE))
#define T4_STACK_START          ((SRAM_END) - (3 * TASK_STACK_SIZE))
#define IDLE_TASK_STACK_START	((SRAM_END) - (4 * TASK_STACK_SIZE))
#define SCHED_STACK_START       ((SRAM_END) - (5 * TASK_STACK_SIZE))









#endif // !STK_CONFIG_H
