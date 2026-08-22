#include <stdint.h>

#ifndef IO_H
#define IO_H

#define RCC             0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC + 0x18))

#define SCB_ICSR        (*(volatile uint32_t*)((0xE000ED00) + 0x04))
#define PENDSVSET       (1U << 28)

#define SYST_CTRL       (*(volatile uint32_t*)(0xE000E010)) // Control and Status Register
#define SYST_LOAD       (*(volatile uint32_t*)(0xE000E014)) // Reload Value Register
#define SYST_VAL        (*(volatile uint32_t*)(0xE000E018)) // Current Value Registe

#endif