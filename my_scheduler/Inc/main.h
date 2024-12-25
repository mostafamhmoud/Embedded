#ifndef MAIN_H_
#define MAIN_H_


#include "OS_MCAL_config.h"


void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void idle_task_handler(void);


#define TASK_STACK_SIZE       1024U
#define SCHED_STACK_SIZE      1024U

#define SRAM_START             0x2000000U
#define SRAM_SIZE             (128*1024)
#define SRAM_END              ((SRAM_START) + (SRAM_SIZE))

#endif
