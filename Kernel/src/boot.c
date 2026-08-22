#include <stdint.h>

extern int main(void);

extern uint32_t _estack; 
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _flashtopdata;

extern uint32_t _sbss;
extern uint32_t _ebss;

typedef void(*vector_item)(void);

void RESET_HANDLER(void);
void DEFAULT_HANDLER(void);

void NMI_HANDLER(void)              __attribute__((weak, alias("DEFAULT_HANDLER")));
void HardFault_Handler(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));

extern void SVCall_Handler(void);  // System service call via SWI instruction
extern void PendSV_Handler(void); //  Pendable request for system service
extern void SysTick_Handler(void);  // System tick timer

__attribute__((section(".isr_vector")))
const vector_item Vector_Table[] = 
{
    (vector_item)&_estack,
    RESET_HANDLER,

    NMI_HANDLER,
    HardFault_Handler,

    DEFAULT_HANDLER,
    DEFAULT_HANDLER,
    DEFAULT_HANDLER,

    0,
    0,
    0,
    0,

    SVCall_Handler,
    DEFAULT_HANDLER,

    0,

    PendSV_Handler,
    SysTick_Handler
};


void DEFAULT_HANDLER(void)
{
    while (1)
    {

    }
}

void RESET_HANDLER(void)
{
    uint32_t *src = &_flashtopdata; // at start flash
    uint32_t *dst = &_sdata; // at start stack

    while (dst < &_edata)
    {
        *dst = *src;

        dst++;
        src++;
    }

    uint32_t *src_bss = &_sbss;
    while (src_bss < &_edata)
    {
        *src_bss = 0;
        src_bss++;
    }
    
    main();

    while (1)
    {

    }
}