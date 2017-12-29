/***
	***************************************************************************
	*	@file  	key.c
	*	@brief   KEY接口相关函数
   ***************************************************************************
   *  @description
	*
	*  初始化KEY的IO口，配置为推挽输出、上拉、速度等级2M。
	* 	
	***************************************************************************
***/

#include "key.h"  
#include "delay.h"

// 函数：KEY IO口初始化
//
void key_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd ( KEY1_CLK, ENABLE); 	//初始化GPIOI时钟	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度选择
	
	//初始化 KEY1 引脚
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;	 
	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);	
}

void DelayKEY(u32 time)
{	
		volatile u16 m=1;
		volatile u32 j;

		for (j=0; j<time; j++)
		{  
				m=KEY_IO;	
				Delay_ms(2);
				while(m!=0)
				{
					m=KEY_IO; 
					Delay_ms(2);
					j=time;
				}            
		}
}

void DelayKEY_AutoRun(u32 time)
{	
		volatile u16 m=1;
		volatile u32 j;

		for (j=0; j<time; j++)
		{  
				m=KEY_IO;	
				Delay_ms(2);
				while(m==0)
				{
					m=KEY_IO; 
					Delay_ms(2);
//					j=time;
				}            
		}
}

