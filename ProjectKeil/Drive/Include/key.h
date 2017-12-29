#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

/*---------------------- KEY配置宏 ------------------------*/

#define KEY1_PIN             GPIO_Pin_8        		 // KEY1 引脚      
#define KEY1_PORT            GPIOI                  // KEY1 GPIO端口     
#define KEY1_CLK             RCC_AHB1Periph_GPIOI	 // KEY1 GPIO端口时钟


#define KEY_IO      GPIOI->IDR&GPIO_Pin_8

/*---------------------- 函数声明 ----------------------------*/

void KEY_Init(void);	//KEY初始化函数
void DelayKEY(u32 time);
void DelayKEY_AutoRun(u32 time);


#endif //__KEY_H

