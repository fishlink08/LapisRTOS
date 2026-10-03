#include "serial.h"

#ifndef UART_H
#include "uart.h"
#endif

// debug helper methods

void init_uart()
{
    RCC_APB1ENR |= (1 << 17);
    RCC_AHB1ENR |= (1 << 0);

    GPIOA_MODER &= ~(0x3 << 4);
    GPIOA_MODER |= (0x2 << 4);

    GPIOA_AFRL &= ~(0xF << 8);
    GPIOA_AFRL |= (0x7 << 8);

    USART2_CR1 |= (1 << 3);
    USART2_CR1 |= (1 << 13);

    USART2_BRR = 0x683;
}

// debug tools

void print_serial(char string[])
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        while (!(USART2_SR & (1 << 7))) {} 
        USART2_DR = string[i]; 
    }
}