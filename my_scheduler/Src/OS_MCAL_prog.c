#include <stdint.h>
#include "Error_type.h"
#include "Stm32F446xx.h"
#include "OS_MCAL_interface.h"
#include "OS_MCAL_config.h"
#include "main.h"


typedef enum
{
	READY_STATE,
	BLOCKED_STATE,
	RUNNING_STATE
}EN_Task_State_t;

typedef struct
{
	uint32_t PSP_value;
	uint32_t block_count;
	EN_Task_State_t task_state;
	void(*task_handler)(void);
}TCB_t;

TCB_t user_tasks[MAX_TASK_NUM];

uint32_t current_task = 1u;	/*Starting at 1 to ignore Idle task*/

uint32_t global_tick_count = 0u;


__attribute__((naked)) void Stack_Schedular_Stack_init(uint32_t sched_top_stack)
{
	/* the value of sched_top_stack has already been loaded into register R0 in the previous line according to (AApcs = Arm Archetecture procedure call standard*/
	__asm volatile("MSR MSP , R0");

	/** can use this instead __asm volatile("MSR MSP, %0"::"r"(sched_top_stack)); */

	__asm volatile("BX LR");
}

void STK_init(uint32_t tick_hz)
{
	/*Calculate the required number of ticks*/
	uint32_t local_reload_value = (SYSTICK_CLK / tick_hz) - 1;

	/* Decrement by one to consider the Multi-shot timer*/
    /* the timer needs to generate the interrupt on the next tick. To adjust for this behavior */
	local_reload_value--;

	SYSTICK->LOAD = local_reload_value;

	/*Enable systick exception*/
	SET_BIT(SYSTICK->CTRL, TICKINT);

	/*Set clock source*/
	SET_BIT(SYSTICK->CTRL, CLKSOURCE);

	/*Enable the systick timer*/
	SET_BIT(SYSTICK->CTRL, ENABLE);
}

__attribute__((naked)) void PendSV_Handler(void)
{
	/* save the context of current task */

	// 1. get current PSP of the running task
	__asm volatile("MRS R0 , PSP");

	// 2. Save the registers R4-R11 SF2 (Software Frame 2) onto the stack of the current task
	__asm volatile("STMDB R0! , {R4-R11}");

	// 3. Save the updated PSP value back to the task's control block
	__asm volatile("PUSH {LR}");                                         // Preserve the Link Register (LR)
	__asm volatile("BL save_PSP_value");                                 // Call function to save the PSP for the current task


	/* Retrieve the context of the next task */

	// 1. Decide the next task to run
	__asm volatile("BL update_next_task");                              // Call function to select the next task

	// 2. get its past PSP value from its task control block
	__asm volatile("BL get_cur_PSP_value");

	__asm volatile("POP {LR}");

	// 3. Using that PSP value retrieve SF2(R4 to R11)
	__asm volatile("LDMIA R0! , {R4-R11}");                            // Load registers from the stack


	// 4. update PSP and exit
	__asm volatile("MSR PSP , R0");

	__asm volatile("POP {LR}");                                         // Restore the saved LR value

	__asm volatile("BX LR");                                            // Branch to the address in LR to resume execution

}

void unblock_tasks(void)
{
	uint8_t task_counter;

	for (task_counter = 1; task_counter <= MAX_TASK_NUM; task_counter++)
	{
		if (user_tasks[task_counter].task_state == BLOCKED_STATE)
		{
			if (user_tasks[task_counter].block_count == global_tick_count)
			{
				user_tasks[task_counter].task_state = READY_STATE;
			}
		}
	}
}

void SysTick_Handler(void)
{
	/*1- Update Global Tick Count*/
	global_tick_count++;

	/*2- Unblock Tasks*/
	unblock_tasks();

	/*3- Trigger the pendsv exception*/
	SET_BIT(SCB->ICSR, 28);
}

void init_tasks_stack(void)
{
	/* task PSP initialization */
	user_tasks[0].PSP_value = IDLE_TASK_STACK_START;
	user_tasks[1].PSP_value = T1_STACK_START;
	user_tasks[2].PSP_value = T2_STACK_START;
	user_tasks[3].PSP_value = T3_STACK_START;
	user_tasks[4].PSP_value = T4_STACK_START;

	/* task handler initialization */
	user_tasks[0].task_handler = &idle_task_handler;
	user_tasks[1].task_handler = &task1_handler;
	user_tasks[2].task_handler = &task2_handler;
	user_tasks[3].task_handler = &task3_handler;
	user_tasks[4].task_handler = &task4_handler;

	/* initialize tasks as ready */
	user_tasks[0].task_state = READY_STATE;
	user_tasks[1].task_state = READY_STATE;
	user_tasks[2].task_state = READY_STATE;
	user_tasks[3].task_state = READY_STATE;
	user_tasks[4].task_state = READY_STATE;


	uint8_t local_task_iterator;
	for (local_task_iterator = 0; local_task_iterator < MAX_TASK_NUM; local_task_iterator++)
	{
		uint32_t* local_task_PSP = (uint32_t*)user_tasks[local_task_iterator].PSP_value;

		local_task_PSP--;
		*local_task_PSP = DUMMY_XPSR;

		local_task_PSP--;
		*local_task_PSP = (uint32_t)user_tasks[local_task_iterator].task_handler;

		local_task_PSP--;
		*local_task_PSP = DUMMY_LR;

		for (uint8_t reg_iterator = 0; reg_iterator < 13; reg_iterator++)
		{
			local_task_PSP--;
			*local_task_PSP = 0;
		}

		user_tasks[local_task_iterator].PSP_value = (uint32_t)local_task_PSP;
	}


}



__attribute__((naked)) void change_to_PSP(void)
{

	// The return value of the function (which is of type uint32_t) is automatically placed into R0 by the ARM architecture calling convention AApcs.

	/*1- Initialize PSP with Task1 Stack address start*/
	/*
	This instruction saves the Link Register (LR) to the current stack.
	The LR is used to store the return address for function calls,
	so saving it here ensures that when this function finishes, the execution can return to the caller without issues.
	The PUSH operation is a part of saving the current state before making the changes.
	*/
	__asm volatile("PUSH {LR}");

	/* Call the GetCurrentPSPValue function */
	__asm volatile("BL get_cur_PSP_value");    // This call places the returned value (PSP) into R0 according to AApcs.

	/* Now, R0 contains the PSP value */
	__asm volatile("MSR PSP , R0");            // Set PSP to the value in R0.

	__asm volatile("POP {LR}");

	/*2- Change SP to PSP using CONTROL register*/
	__asm volatile("MOV R0 , #0x02");

	__asm volatile("MSR CONTROL , R0");



	__asm volatile("BX LR");


}

uint32_t get_cur_PSP_value(void)
{
	return user_tasks[current_task].PSP_value;
}

void save_PSP_value(uint32_t cur_PSP_value)
{
	user_tasks[current_task].PSP_value = cur_PSP_value;
}

void update_next_task(void)
{
	uint8_t local_task_iterator;

	for (local_task_iterator = 0; local_task_iterator < MAX_TASK_NUM; local_task_iterator++)
	{
		current_task++;

		current_task %= MAX_TASK_NUM;

		if ((user_tasks[current_task].block_count == READY_STATE) && (current_task != 0u))
		{
			/*Check if any other task is ready, excluding the Idle task*/
			break;
		}
	}

	if (user_tasks[current_task].task_state != READY_STATE)   //  All tasks are blocked
	{
		current_task = 0;
	}
}



void task_delay(uint32_t block_count_delay)
{
	if (current_task != 0u)   /*Idle Task can't be blocked state*/
	{
		ENTER_CRITICAL_SECTION();

		/*Update Task blocking period*/
		user_tasks[current_task].block_count = block_count_delay + global_tick_count;

		/*Update Task state*/
		user_tasks[current_task].task_state = BLOCKED_STATE;

		EXIT_CRITICAL_SECTION();

		/*Call the scheduler by pending the Pendsv*/
		SET_BIT(SCB->ICSR, 28);
	}
}




void enable_system_faults(void)
{
	SCB->SHCSR |= (1 << 16) | (1 << 17) | (1 << 18);
}


void HardFault_Handler(void)
{
	while (1);
}
void MemManage_Handler(void)
{
	while (1);
}
void BusFault_Handler(void)
{
	while (1);
}
void UsageFault_Handler(void)
{
	while (1);
}


void idle_task_handler(void)
{
	while (1);
}
