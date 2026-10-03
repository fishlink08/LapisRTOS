#include <stdint.h>

#ifndef DELAY_H
#define DELAY_H

#define DELAY_RCC               0x40023800
#define DELAY_RCC_APB2ENR       (*(volatile uint32_t*)(DELAY_RCC + 0x44))
#define DELAY_RCC_APB1ENR       (*(volatile uint32_t*)(DELAY_RCC + 0x40))

#define TIM2                    0x40000000
#define TIM2_CR1                (*(volatile uint32_t*)(TIM2 + 0x00))
#define TIM2_PSC                (*(volatile uint32_t*)(TIM2 + 0x28))
#define TIM2_ARR                (*(volatile uint32_t*)(TIM2 + 0x2C))
#define TIM2_CNT                (*(volatile uint32_t*)(TIM2 + 0x24))
#define TIM2_EGR                (*(volatile uint32_t*)(TIM2 + 0x14))

#endif