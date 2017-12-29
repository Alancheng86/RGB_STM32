/***
	***************************************************************************
	*	@file  	key.c
	*	@brief   KEY�ӿ���غ���
   ***************************************************************************
   *  @description
	*
	*  ��ʼ��KEY��IO�ڣ�����Ϊ����������������ٶȵȼ�2M��
	* 	
	***************************************************************************
***/

#include "key.h"  
#include "delay.h"

// ������KEY IO�ڳ�ʼ��
//
void key_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��
	RCC_AHB1PeriphClockCmd ( KEY1_CLK, ENABLE); 	//��ʼ��GPIOIʱ��	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�������
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //�ٶ�ѡ��
	
	//��ʼ�� KEY1 ����
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

