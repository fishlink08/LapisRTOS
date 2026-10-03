#include <stdint.h>

#ifndef UART_H
#define UART_H

#define BASE_USART1     0x40011000
#define USART_SR        (*(volatile uint32_t*)(BASE_USART1 + 0x00))
#define USART_DR        (*(volatile uint32_t*)(BASE_USART1 + 0x04))
#define USART_BRR       (*(volatile uint32_t*)(BASE_USART1 + 0x08))
#define USART_CR1       (*(volatile uint32_t*)(BASE_USART1 + 0x0C))
#define USART_CR2       (*(volatile uint32_t*)(BASE_USART1 + 0x10))
#define USART_CR3       (*(volatile uint32_t*)(BASE_USART1 + 0x14))
#define USART_GTPR      (*(volatile uint32_t*)(BASE_USART1 + 0x18))

#define BASE_USART2     0x40004400
#define USART2_SR       (*(volatile uint32_t*)(BASE_USART2 + 0x00))
#define USART2_DR       (*(volatile uint32_t*)(BASE_USART2 + 0x04))
#define USART2_BRR      (*(volatile uint32_t*)(BASE_USART2 + 0x08))
#define USART2_CR1      (*(volatile uint32_t*)(BASE_USART2 + 0x0C))
#define USART2_CR2      (*(volatile uint32_t*)(BASE_USART2 + 0x10))
#define USART2_CR3      (*(volatile uint32_t*)(BASE_USART2 + 0x14))
#define USART2_GTPR     (*(volatile uint32_t*)(BASE_USART2 + 0x18))

#define GPIOA_BASE      0x40020000
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER  (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR (*(volatile uint32_t *)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR   (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR     (*(volatile uint32_t *)(GPIOA_BASE + 0x10))
#define GPIOA_ODR     (*(volatile uint32_t *)(GPIOA_BASE + 0x14))
#define GPIOA_BSRR    (*(volatile uint32_t *)(GPIOA_BASE + 0x18))
#define GPIOA_LCKR    (*(volatile uint32_t *)(GPIOA_BASE + 0x1C))
#define GPIOA_AFRL    (*(volatile uint32_t *)(GPIOA_BASE + 0x20))
#define GPIOA_AFRH    (*(volatile uint32_t *)(GPIOA_BASE + 0x24))

#define RCC_BASE        0x40023800
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x44))
#define RCC_APB1ENR    (*(volatile uint32_t*)(RCC_BASE + 0x40))
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))

#endif