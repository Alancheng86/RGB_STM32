#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

void Delay_Init(void);				//延时函数初始化
void Delay_ms(u32 nTime);	//毫秒延时函数
void Delay_us(u32 mTime);
void Delay_100ns(u32 mTime);

#endif //__DELAY_H

