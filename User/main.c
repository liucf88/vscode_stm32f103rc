/**
 ******************************************************************************
 * @file    			main.c *
 * @author  			WisIOE Software Team *
 * @version 			V1.2
 **
 * @date    			2017-11-01
 **
 * @brief 				用3.5.0版本库建的工程模板
 **
 * @attention  	内网测试，请保证W5500的IP与测试PC机在同一网段内，且不冲突    *
 *               如果是用网线跟PC机直连，请设置PC机本地连接地址IP为静态IP
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

#include <stdio.h>
#include <string.h>
#include "W5500_conf.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "bsp_led.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_usart3.h"
#include "socket.h"
#include "stm32f10x.h"
#include "tcp_demo.h"
#include "utility.h"
#include "w5500.h"

int main(void)
{
	systick_init(72); /*初始化Systick工作时钟*/
	LED_GPIO_Config();
	USART1_Config(); /*初始化串口通信:115200@8-n-1*/
	USART2_Config(); /*初始化串口通信:115200@8-n-1*/
	USART3_Config(); /*初始化串口通信:115200@8-n-1*/
	i2c_CfgGpio();   /*初始化eeprom*/

	printf(" W5500 TCP Server demo V1.2 \r\n");

	gpio_for_w5500_config(); /*初始化MCU相关引脚*/
	reset_w5500();			 /*硬复位W5500*/
	PHY_check();			 /*检查网线是否接入*/
	set_w5500_mac();		 /*配置MAC地址*/
	set_w5500_ip();			 /*配置IP地址*/

	socket_buf_init(txsize, rxsize); /*初始化8个Socket的发送接收缓存大小*/

	printf(" W5500为TCP 服务器，建立侦听，等待PC作为TCP Client建立连接 \r\n");
	printf(" W5500监听端口为： %d \r\n", local_port);
	printf(" 连接成功后，TCP Client发送数据给W5500，W5500将返回对应数据 \r\n");

	while (1) /*循环执行的函数*/
	{
		do_tcp_server(); /*TCP_Client 数据回环测试程序*/
		delay_ms(1);
		// USART2_PutChar(0x17);
		// USART3_PutChar(0x18);
	}
}
