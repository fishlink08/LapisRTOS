#include "delay.h"

void init(void)
{
    DELAY_RCC_APB1ENR |= (1U << 0);

    TIM2_PSC = 7;
    TIM2_ARR = 0xFFFFFFFF;

    TIM2_EGR |= 1U;

    TIM2_CR1 |= 1U;

}

void delay_us(uint32_t us)
{
    uint32_t start = TIM2_CNT;

    while ((uint32_t)(TIM2_CNT - start) < us)
    {
    }
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}