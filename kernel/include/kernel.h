#include <stdint.h>

#ifndef RTOS_KERNEL_H
#define RTOS_KERNEL_H

typedef enum {FALSE,TRUE} boolean;

typedef struct 
{
    boolean HeapAllocationEnabled;
    struct {
        uint8_t MAX_TASKS : 4;
        uint32_t SWITCH_SPEED : 32;
    } TaskSchedulerSettings;
    
} Kernel_Settings;


/*
    Inits the LapisRTOS Kernel and associated systems.

    Params:
    KS or Kernel_Settings. Pass null to get default settings. 
*/
void initKernel(Kernel_Settings* KS);

#endif
