#ifndef __LED_H
#define __LED_H

#include "W5500_conf.h"
#include "stm32f10x.h"
/** the macro definition to trigger the led on or off
 * 1 - off
 * 0 - on
 */
//#define ON  0
//#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)                                                                \
  if (a)                                                                       \
    GPIO_SetBits(GPIOA, GPIO_Pin_0);                                           \
  else                                                                         \
    GPIO_ResetBits(GPIOA, GPIO_Pin_0)

/* 直接操作寄存器的方法控制IO */
#define digitalHi(p, i)                                                        \
  { p->BSRR = i; } //设置为高电平
#define digitalLo(p, i)                                                        \
  { p->BRR = i; } //输出低电平
#define digitalToggle(p, i)                                                    \
  { p->ODR ^= i; } //输出反转状态

/* 定义控制IO的宏 */
#define LED1_TOGGLE digitalToggle(GPIOA, GPIO_Pin_0)
#define LED1_OFF digitalHi(GPIOA, GPIO_Pin_0)
#define LED1_ON digitalLo(GPIOA, GPIO_Pin_0)

void LED_GPIO_Config(void);

#endif /* __LED_H */
