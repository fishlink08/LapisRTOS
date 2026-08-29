#ifndef RTOS_HEAP_H
#define RTOS_HEAP_H

#include "stdint.h"

typedef uint32_t size_t;

void heap_init(void);

void* malloc(size_t size);
void free(void* ptr);

#endif