#ifndef __LCD_SPI_H
#define __LCD_SPI_H

#include "stm32f4xx.h"

/*---------------------- LCD_SPI配置宏 ------------------------*/

#define LCD_SPI1_PIN             GPIO_Pin_15        		 // LCD_SPI1 引脚      
#define LCD_SPI1_PORT            GPIOA                  // LCD_SPI1 GPIO端口     
#define LCD_SPI1_CLK             RCC_AHB1Periph_GPIOA	 // LCD_SPI1 GPIO端口时钟

#define LCD_SPI2_PIN             GPIO_Pin_11        		 // LCD_SPI2 引脚      
#define LCD_SPI2_PORT            GPIOI                  // LCD_SPI2 GPIO端口     
#define LCD_SPI2_CLK             RCC_AHB1Periph_GPIOI	 // LCD_SPI2 GPIO端口时钟

#define LCD_SPI3_PIN             GPIO_Pin_13        		 // LCD_SPI3 引脚      
#define LCD_SPI3_PORT            GPIOC                  // LCD_SPI3 GPIO端口     
#define LCD_SPI3_CLK             RCC_AHB1Periph_GPIOC	 // LCD_SPI3 GPIO端口时钟

#define LCD_SPI4_PIN             GPIO_Pin_2        		 // LCD_SPI4 引脚      
#define LCD_SPI4_PORT            GPIOB                  // LCD_SPI4 GPIO端口     
#define LCD_SPI4_CLK             RCC_AHB1Periph_GPIOB	 // LCD_SPI4 GPIO端口时钟




#define LCD_SPI_CS(x)   	GPIOA->ODR=(GPIOA->ODR&~LCD_SPI1_PIN)|(x ? LCD_SPI1_PIN:0)
#define LCD_SPI_SCK(x)   	GPIOI->ODR=(GPIOI->ODR&~LCD_SPI2_PIN)|(x ? LCD_SPI2_PIN:0)
#define LCD_SPI_MOSI(x)   GPIOC->ODR=(GPIOC->ODR&~LCD_SPI3_PIN)|(x ? LCD_SPI3_PIN:0)
#define LCD_SPI_MISO      GPIOB->IDR&GPIO_Pin_2



/*---------------------- 函数声明 ----------------------------*/

void LCD_SPI_Init(void);	//LCD_SPI初始化函数
int LCD_SPI_WRITE(u8 index,u16 Data);
int LCD_SPI_READ(u8 index);
void READ_EEPROM_DATA(void);
void WRITE_EEPROM_DATA(void);
char EEPROM_CHECK(void);



#endif //__LCD_SPI_H

