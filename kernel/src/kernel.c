#include <stddef.h>

#include "kernel.h"
#include "heap.h"
#include "scheduler.h"

void initKernel(Kernel_Settings* KS)
{
    if (KS != 0 && KS != NULL)
    {
        if (KS->HeapAllocationEnabled)
        {
            initHeap();
        }
        if (KS->TaskSchedulerSettings.SWITCH_SPEED != 0 && KS->TaskSchedulerSettings.MAX_TASKS != 0)
        {
            _start_scheduler(KS->TaskSchedulerSettings.SWITCH_SPEED, KS->TaskSchedulerSettings.MAX_TASKS);
        } else {
            _start_scheduler(2000000, 5);
        }
    }
}