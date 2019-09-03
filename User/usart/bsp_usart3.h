#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"
#include <stdio.h>

void USART3_Config(void);
void USART3_PutChar(uint8_t ch);
uint8_t USART3_GetChar(void);
#endif /* __USART1_H */
