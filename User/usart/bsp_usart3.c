/**
******************************************************************************
* @file    			bsp_usart3.c *
* @author  			WisIOE Software Team *
* @version 			V1.2
**
* @date    			2017-11-01
**
* @brief
*usart串口配置以及实现C库printf函数到usart端口 *
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
#include "bsp_usart3.h"

/**
 * @brief  USART3 GPIO 配置,工作模式配置。115200 @ 8-N-1
 * @param  无
 * @retval 无
 */
void USART3_Config(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* config USART3 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* USART3 GPIO config */
  /* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* USART1 mode config */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);
  USART_Cmd(USART3, ENABLE);
}

// USART3 发送一个字符
void USART3_PutChar(uint8_t ch) {
  /* 发送一个字节数据到USART3 */
  USART_SendData(USART3, (uint8_t)ch);

  /* 等待发送完毕 */
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
    ;
}

// USART3 接收一个字符
uint8_t USART3_GetChar(void) {
  /* 等待串口1输入数据 */
  while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET)
    ;
  return (uint8_t)USART_ReceiveData(USART3);
}
/*********************************************END OF FILE**********************/
