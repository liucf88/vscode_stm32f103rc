#ifndef __USART2_H
#define __USART2_H

#include "stm32f10x.h"
#include <stdio.h>

void USART2_Config(void);
void USART2_PutChar(uint8_t ch);
uint8_t USART2_GetChar(void);
#endif /* __USART1_H */
