#include <stdint.h>

#ifndef SCHEDULER_H
#define SCHEDULER_H

extern uint32_t *get_ptr(void);
extern void set_ptr(uint32_t *ptr);

void _start_scheduler(void);
void _create_task(void*(*function)(void));

#endif