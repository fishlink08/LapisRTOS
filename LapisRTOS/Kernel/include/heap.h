#ifndef RTOS_HEAP_H
#define RTOS_HEAP_H

#include "stdint.h"
#include "stddef.h"

void heap_init(void);

void* malloc(size_t size);
void free(void* ptr);

#endif