#ifndef OS_MCAL_INTERFACE_H
#define OS_MCAL_INTERFACE_H


/********************************
 *  SysTick Control and Status Register pins *
 ********************************/
enum
{
	ENABLE,
	TICKINT,
	CLKSOURCE,

	COUNTFLAG = 16
};


#define DUMMY_XPSR			0x01000000
#define DUMMY_LR			0xFFFFFFFD

#define ENTER_CRITICAL_SECTION()     do{__asm volatile("MOV R0 , 1"); __asm volatile("MSR PRIMASK, R0") ;} while(1)
#define EXIT_CRITICAL_SECTION()      do{__asm volatile("MOV R0 , 0"); __asm volatile("MSR PRIMASK, R0") ;} while(1)

void STK_init(uint32_t tick_hz);

__attribute__((naked)) void Stack_Schedular_Stack_init(uint32_t schedtos);

void init_tasks_stack(void);

void enable_system_faults(void);

__attribute__((naked)) void change_to_PSP(void);

void task_delay(uint32_t block_count);





#endif // !STK_INTERFACE_H
