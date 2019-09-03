/**
******************************************************************************
* @file    			bsp_TiMbase.c *
* @author  			WisIOE Software Team *
* @version 			V1.2
**
* @date    			2017-11-01
**
* @brief 			  计时器应用函数 *
******************************************************************************
* @company  		深圳炜世科技有限公司 *
* @website  		www.wisioe.com
**
* @forum        www.w5500.cn
**
* @qqGroup      383035001
**
******************************************************************************
*/

#include "bsp_TiMbase.h"

/* TIM2中断优先级配置 */
void TIM2_NVIC_Configuration(void) {
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
 * TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71
 * 中断周期为 = 1/(72MHZ /72) * 1000 = 1ms
 *
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> 中断
 * 且TIMxCNT重置为0重新计数
 */
void TIM2_Configuration(void) {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* 设置TIM2CLK 为 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  // TIM_DeInit(TIM2);

  /* 自动重装载寄存器周期的值(计数值) */
  TIM_TimeBaseStructure.TIM_Period = 1000;

  /* 累计 TIM_Period个频率后产生一个更新或者中断 */
  /* 时钟预分频数为72 */
  TIM_TimeBaseStructure.TIM_Prescaler = 71;

  /* 对外部时钟进行采样的时钟分频,这里没有用到 */
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ClearFlag(TIM2, TIM_FLAG_Update);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  TIM_Cmd(TIM2, ENABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE); /*先关闭等待使用*/
}
/*********************************************END OF FILE**********************/
