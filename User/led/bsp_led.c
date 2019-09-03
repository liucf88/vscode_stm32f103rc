/**
******************************************************************************
* @file    			bsp_led.c *
* @author  			WisIOE Software Team *
* @version 			V1.2
**
* @date    			2017-11-01
**
* @brief 				LED灯配置函数
**
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
#include "bsp_led.h"
/**
 * @brief  初始化控制LED的IO
 * @param  无
 * @retval 无
 */
void LED_GPIO_Config(void) {
  /*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure;

  /*开启LED的外设时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /*选择要控制的GPIOB引脚*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*选择要控制的引脚*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC, GPIO_Pin_7);

  /* 打开所有led灯	*/
  GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}
/*********************************************END OF FILE**********************/
