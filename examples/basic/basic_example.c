#include "kernel.h"

int main(void)
{
    Kernel_Settings settings= 
    {
        .HeapAllocationEnabled = TRUE,
        .TaskSchedulerSettings = {
            .SWITCH_SPEED = 2000000,
            .MAX_TASKS = 4
        } 
    };

    initKernel(&settings);
    
    while (1)
    {
        
    }

    return 0;
}