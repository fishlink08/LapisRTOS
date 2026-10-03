#include "../../include/scheduler.h"
#include "../../include/io.h"

#include <stdint.h>

#define MAX_TASKS 20
#define STACK_SIZE 128

typedef enum {FALSE, TRUE} boolean;
typedef struct
{
    void*(*function)(void);
    uint32_t STACK[STACK_SIZE]          __attribute__((aligned(8)));
    uint32_t * stack_pointer;           // program counter heads here 
} Task;

static Task tasks[MAX_TASKS];
static uint32_t task_count = 0;
volatile uint32_t current_task = 0;

static boolean scheduler_initialized = FALSE;
static uint8_t kernel_restricted_MAX_TASKS;

void SysTick_Handler(void)
{
    SCB_ICSR = PENDSVSET;
}

void init_systick(uint32_t SwitchSpeed)
{
    SYST_LOAD = SwitchSpeed - 1;
    SYST_VAL = 0;

    SYST_CTRL |= (1U << 0) | (1U << 1) | (1U << 2);
}

void scheduler_pendsv(void)
{
    tasks[current_task].stack_pointer = get_ptr();

    current_task++;
    
    if (current_task >= task_count)
    {
        current_task = 0;
    }

    set_ptr(tasks[current_task].stack_pointer);
}

uint32_t * get_stack_first(void)
{
    current_task = 0;
    return tasks[current_task].stack_pointer;
}

void _create_task(void*(*function)(void))
{
    if (!scheduler_initialized) {return;}
    if (task_count >= kernel_restricted_MAX_TASKS) {return;}

    Task * tsk = &tasks[task_count];
    tsk->function = function;

    uint32_t * stack_top = &tsk->STACK[STACK_SIZE];

    *(--stack_top) = 0x01000000;
    *(--stack_top) = (uint32_t)function;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;

    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;
    *(--stack_top) = 0;

    tsk->stack_pointer = stack_top;

    task_count++;

}

void _start_scheduler(uint32_t SWITCH_SPEED, uint8_t kr_MAX_TASKS)
{
    if (!scheduler_initialized)
    {
        if (kr_MAX_TASKS > MAX_TASKS) {return;}

        kernel_restricted_MAX_TASKS = kr_MAX_TASKS;
        if (task_count == 0);

        current_task = 0;
        init_systick(SWITCH_SPEED);

        __asm volatile("svc 0");

        scheduler_initialized = TRUE;
    }
}

