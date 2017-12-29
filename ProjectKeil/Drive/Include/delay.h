#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

void Delay_Init(void);				//��ʱ������ʼ��
void Delay_ms(u32 nTime);	//������ʱ����
void Delay_us(u32 mTime);
void Delay_100ns(u32 mTime);

#endif //__DELAY_H

