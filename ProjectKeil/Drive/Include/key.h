#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

/*---------------------- KEY���ú� ------------------------*/

#define KEY1_PIN             GPIO_Pin_8        		 // KEY1 ����      
#define KEY1_PORT            GPIOI                  // KEY1 GPIO�˿�     
#define KEY1_CLK             RCC_AHB1Periph_GPIOI	 // KEY1 GPIO�˿�ʱ��


#define KEY_IO      GPIOI->IDR&GPIO_Pin_8

/*---------------------- �������� ----------------------------*/

void KEY_Init(void);	//KEY��ʼ������
void DelayKEY(u32 time);
void DelayKEY_AutoRun(u32 time);


#endif //__KEY_H

