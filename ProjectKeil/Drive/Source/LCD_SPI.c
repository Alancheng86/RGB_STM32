/***
	***************************************************************************
	*	@file  	LCD_SPI.c
	*	@brief   KEY接口相关函数
   ***************************************************************************
   *  @description
	*
	*  初始化KEY的IO口，配置为推挽输出、上拉、速度等级2M。
	* 	
	***************************************************************************
***/

#include "LCD_SPI.h"  
#include "delay.h"
#include "usart.h"
#include "delay.h"

#define EEPROM_DATA_SUM		104
u16 eepromData[640]=
	{
		82,0,113,52,48,207,5,16,9,6,134,48,32,0,16,16,16,128,128,128,161,104,165,0,0,0,2,2,0,128,144,58,20,20,82,20,20,85,85,85,85,85,85,85,85,3,145,239,58,26,0,0,128,0,4,8,24,35,18,17,23,32,35,38,43,37,37,53,48,36,49,56,30,0,4,8,24,35,18,17,23,32,35,38,43,37,37,53,48,36,49,56,30,0,4,12,28,44,60,92,124,188,252,124,252,0,128,0,64,128,160,192,208,224,240,248,252,0,0,5,175,255,255,0,4,12,28,44,60,92,124,188,252,124,252,0,128,0,64,128,160,192,208,224,240,248,252,0,0,5,175,255,255,0,4,12,28,44,60,92,124,188,252,124,252,0,128,0,64,128,160,192,208,224,240,248,252,0,0,5,175,255,255,25,1,0,0,0,0,0,0,128,128,42,42,26,26,0,26,26,0,48,87,73,98,64,233,0
		
	};

u32 bufferdata[640]={0};		
// 函数：KEY IO口初始化
//
void LCD_SPI_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd ( LCD_SPI1_CLK, ENABLE); 	//初始化LCD_SPI时钟	
	RCC_AHB1PeriphClockCmd ( LCD_SPI2_CLK, ENABLE); 	//初始化LCD_SPI时钟	
	RCC_AHB1PeriphClockCmd ( LCD_SPI3_CLK, ENABLE); 	//初始化LCD_SPI时钟	
	RCC_AHB1PeriphClockCmd ( LCD_SPI4_CLK, ENABLE); 	//初始化LCD_SPI时钟	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度选择
	
	//初始化 LCD_SPI1 引脚
	GPIO_InitStructure.GPIO_Pin = LCD_SPI1_PIN;	 
	GPIO_Init(LCD_SPI1_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度选择
	//初始化 LCD_SPI2 引脚								   
	GPIO_InitStructure.GPIO_Pin = LCD_SPI2_PIN;	
	GPIO_Init(LCD_SPI2_PORT, &GPIO_InitStructure);	
	
	//初始化 LCD_SPI3 引脚								   
	GPIO_InitStructure.GPIO_Pin = LCD_SPI3_PIN;	
	GPIO_Init(LCD_SPI3_PORT, &GPIO_InitStructure);
		
	
	
	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //輸入模式
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; //速度选择
	
	//初始化 KEY1 引脚
	GPIO_InitStructure.GPIO_Pin = LCD_SPI4_PIN;	 
	GPIO_Init(LCD_SPI4_PORT, &GPIO_InitStructure);
	
	
	
	GPIO_ResetBits(LCD_SPI1_PORT,LCD_SPI1_PIN);  //LCD_SPI输出
	GPIO_ResetBits(LCD_SPI2_PORT,LCD_SPI2_PIN);  //LCD_SPI输出

	
}

void EWEN(void)
{
		u16 ij;
		u32 temp_data=0;

	
		temp_data = (0x1<<10) + (0x0<<0) +0xc0 ;
		LCD_SPI_CS(1);		Delay_100ns(2);
		for(ij=0;ij<11;ij++)
		{
				LCD_SPI_MOSI(temp_data&0x400);
				LCD_SPI_SCK(1);Delay_us(1);
				LCD_SPI_SCK(0);Delay_us(1);
				temp_data = temp_data<<1;
  	}

		LCD_SPI_CS(0);
		LCD_SPI_SCK(1);Delay_us(1);LCD_SPI_CS(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_SCK(1);Delay_us(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_SCK(1);Delay_us(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_SCK(1);Delay_us(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_CS(0);
				Delay_100ns(2);
}

void EWDS(void)
{
		u16 ij;
		u32 temp_data=0;

	
		temp_data = (0x1<<10) + (0x0<<0) +0x00 ;
		LCD_SPI_CS(1);
		for(ij=0;ij<11;ij++)
		{
				LCD_SPI_MOSI(temp_data&0x400);
				LCD_SPI_SCK(1);Delay_us(1);
				LCD_SPI_SCK(0);Delay_us(1);
				temp_data = temp_data<<1;
  	}

		LCD_SPI_CS(0);
		LCD_SPI_SCK(1);Delay_us(1);LCD_SPI_CS(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_SCK(1);Delay_us(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_SCK(1);Delay_us(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_SCK(1);Delay_us(1);
		LCD_SPI_SCK(0);Delay_us(1);
		LCD_SPI_CS(0);
		Delay_us(1);
}

int LCD_SPI_WRITE(u8 index,u16 Data)
{
	u8 ij;
	u32 temp_data=0;
	u32 READ_BACK=0;
	
	temp_data = (0x1<<26) + (0x1<<24) +(index<<16) + Data;
	LCD_SPI_CS(1);
	for(ij=0;ij<27;ij++)
	{
			LCD_SPI_MOSI(temp_data&0x4000000);
			LCD_SPI_SCK(1);Delay_us(1);
			LCD_SPI_SCK(0);Delay_us(1);
			temp_data = temp_data<<1;
	}
	LCD_SPI_CS(0);		Delay_100ns(3);
	
	LCD_SPI_SCK(1);Delay_us(1);LCD_SPI_CS(1);
	LCD_SPI_SCK(0);Delay_us(1);
	LCD_SPI_SCK(1);Delay_us(1);
	LCD_SPI_SCK(0);Delay_us(1);
	LCD_SPI_SCK(1);Delay_us(1);
	LCD_SPI_SCK(0);Delay_us(1);
	LCD_SPI_SCK(1);Delay_us(1);
	LCD_SPI_SCK(0);Delay_us(1);
		while(!LCD_SPI_MISO)
		{
				LCD_SPI_SCK(1);Delay_us(1);
				READ_BACK = LCD_SPI_MISO ;
				LCD_SPI_SCK(0);Delay_us(1);
		}
		LCD_SPI_CS(0);Delay_ms(6);

	return READ_BACK;
}

int LCD_SPI_READ(u8 index)
{
		u16 ij;
		u32 temp_data=0;
		u32 READ_BACK=0;
	
		temp_data = (0x1<<26) + (0x2<<24) +(index<<16) + 0;
		LCD_SPI_CS(1);
		for(ij=0;ij<27;ij++)
		{
				LCD_SPI_MOSI(temp_data&0x4000000);
				LCD_SPI_SCK(1);Delay_us(1);
				READ_BACK += LCD_SPI_MISO ;
				LCD_SPI_SCK(0);Delay_us(1);
				
				temp_data = temp_data<<1;
				READ_BACK = READ_BACK<<1;
		}
		READ_BACK = READ_BACK<<1;
		LCD_SPI_CS(0);Delay_us(1);
	
		READ_BACK = READ_BACK>>4;
		
		return READ_BACK;
}

void READ_EEPROM_DATA(void)
{
		u16 i;
	
		for(i=0;i<EEPROM_DATA_SUM;i++)
		{
				bufferdata[i] = LCD_SPI_READ(i);
				printf("%08x,",bufferdata[i]);
		}
		printf(" \n *****************fen ge xian**************** \n");
}

char EEPROM_CHECK(void)
{
		u16 jj;
		u16 error_sum=0;
	
		for(jj=0;jj<EEPROM_DATA_SUM;jj++)
		{
				if(bufferdata[jj]!=((eepromData[2*jj]<<8)+eepromData[2*jj+1]))
				{		error_sum++;		}
		}
		
		if(error_sum>0)
		{
				printf(" \t\n error_sum = '%d',******* \n ",error_sum);
				return 1;
		}
		else
		{
				printf(" \t\n eeprom check ok \n ",error_sum);
			return 0;
		}
}

void WRITE_EEPROM_DATA(void)
{
		u16 i;
		u16 data=0;
		
		printf(" \n *****************fen ge xian**************** \n");
		EWEN();
		for(i=0;i<EEPROM_DATA_SUM;i++)
		{
				data = (eepromData[i*2]<<8)+eepromData[2*i+1];
				LCD_SPI_WRITE(i,data);
				printf("%08x;",data);
		}
		EWDS();
		printf(" \n *****************fen ge xian**************** \n");
}



