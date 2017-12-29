/***
	************************************************************************************************
	*	@file  	main.c
	*	@version V1.0.0
	*  @date    2017-5-10	
	*	@author  反客科技
	*	@brief   驱动AT070TN83进行显示
   ************************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32F429核心板
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*	
	*	重要说明：
	*
	*	1.使用核心板与83进行连接时，要使用同面的FPC排线
	*	2.由于83屏幕功耗过大，超出了一般的USB口供电能力，所以这里使用PWM来控制背光，占空比40%，频率200Hz
	*	3.在刚下载程序时或刚上电时，屏幕有轻微抖动属于正常现象，片刻即可恢复正常			
	*	4.83的驱动程序仅在反客7.0RGB液晶屏的程序上增加了几个控制引脚的初始化，其他没有变动
	*	5.驱懂RGB屏幕显示时，32和SDRAM芯片有轻微发热属正常现象
	*	6.若发现屏幕有明显的条纹底噪，请使用大功率的5V电源进行更电
	*
	*	驱动测试：
	*	
	*	以下数据的测试条件为：分辨率800*480，FPC排线长度为20cm。所谓最高驱动频率是指显示正常，并且在清屏
	*	的时候无花屏的现象，使用更高的驱动频率可能会在清屏时造成短暂的花屏。只开单层显示和使用更短的排线
	*	可以允许使用更高的驱动频率，相关参数在lcd_rgb.h里进行设置。
	*	1.只开单层显示下，16位色模式最高驱动频率70M
	*	2.只开单层显示下，24位色模式最高驱动频率52M
	*	3.只开单层显示下，32位色模式最高驱动频率38M
	*	4.开双层显示下，RGB565和ARGB1555模式下，最高驱动频率40M
	*	5.开双层显示下，RGB565和ARGB8888模式下，最高驱动频率25M
	*  5.开双层显示下，RGB888和ARGB1555模式下，最高驱动频率36M
	*	5.开双层显示下，RGB888和ARGB8888模式下，最高驱动频率22M
	*	
	*	其他说明：
	*
	*	1.STM32F29的透明度是用在两个显示层之间
	*	2.在分辨率为800*480时，驱动频率在33M左右就可以达到60帧的刷新率，一般使用这个频率就足够了
	*	3.开层显示下，前景层应设置为带透明色的颜色模式，不然就无法看到背景层，推荐使用RGB565+ARGB8888的搭配
	*	4.屏幕在刚下载或者刚上电的时候有轻微的闪烁属于正常现象，片刻就会消失，使用越低的驱动频率闪烁越明显  
	*	5.在lcd_rgb.h里定义了一些常用的颜色，高8位为透明色，只在ARGB8888和ARGB1555模式下有效，ARGB1555只有
	*	  在高8位为0时才会显示透明。
	*
	************************************************************************************************
***/

#include "stm32f4xx.h"
#include "led.h"  
#include "key.h"
#include "LCD_SPI.h" 
#include "delay.h"
#include "usart.h"
#include "lcd_rgb.h"
#include "lcd_pwm.h"
#include "picc1.h" 




//#define OTP_FORCE_ON		1







void LCD_ClearTest(void);		// 清屏测试
void LCD_TextTest(void);		// 文本显示测试
void LCD_FillTest(void);		// 矩形填充测试
void LCD_ColorTest(void);		// 颜色测试
void LCD_GrahicTest(void);		// 绘图测试
void LCD_AlphaTest(void);		// 透明度测试
void LCD_Vertical_Test(void);	// 垂直显示测试

void LCD_COLORBAR(void);







void LCD_Test(void)		// LCD测试
{
	
	
	LCD_DisplayMode(Mode_H); 	//横屏显示,,對於字符之類的超出屏範圍的，容易導致屏顯示無故中斷
	
//	LCD_TextTest();
	LCD_SetFont(&Font32);
//	LCD_SetColor(LIGHT_BLUE);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayString(440,20,"M1658A0_LCD_TEST");	//Delay_ms(time);
	LCD_DisplayString(440,20+32,"ColorMode: RGB888");	//Delay_ms(time);		

	DelayKEY_AutoRun(1000);	
	
	
	
	LCD_DisplayMode(Mode_H); 	//横屏显示,,對於字符之類的超出屏範圍的，容易導致屏顯示無故中斷
	LCD_SetBackColor(LCD_RED);   LCD_Clear();  DelayKEY_AutoRun(1000);
	LCD_SetBackColor(LCD_GREEN);   LCD_Clear();  DelayKEY_AutoRun(1000);
    LCD_SetBackColor(LCD_BLUE);LCD_Clear();  DelayKEY_AutoRun(1000);	
	
	LCD_SetBackColor(LCD_WHITE);  LCD_Clear();  DelayKEY_AutoRun(1000);
    LCD_SetBackColor(LCD_GREY);  LCD_Clear();  DelayKEY_AutoRun(1000);
    LCD_SetBackColor(LCD_BLACK);  LCD_Clear();  DelayKEY_AutoRun(1000);
	
//	LCD_SetBackColor(LCD_WHITE);  LCD_Clear();
//	LCD_SetBackColor(LCD_WHITE);LCD_SetColor(LCD_BLACK);	//设置画笔颜色
//    LCD_FillRect(1,  1,LCD_Width-2,LCD_Height-2);  DelayKEY_AutoRun(1*2000);
	
	LCD_FLICKER_B();	LCD_FLICKER_B();							DelayKEY_AutoRun(1000);
	LCD_FLICKER_A();	LCD_FLICKER_A();							DelayKEY_AutoRun(1000);
	
	LCD_WriteBMP(0,0,352,1259,picc1);DelayKEY_AutoRun(1000);
	
	DelayKEY(2*1000);



}
/*---------------------------- 主函数 ---------------------------------*/

int main(void)
{
	LED_Init();			//LED初始化
	Delay_Init();		//延时函数初始化
	Usart_Config();  //串口初始化
	LCD_SPI_Init();		/////SPI 初始化
	
	printf("\n  M1658A0_EEPROM_TEST   start********* \n");
#ifdef OTP_FORCE_ON
			WRITE_EEPROM_DATA();///////燒錄eeprom
#endif		
	
	READ_EEPROM_DATA();				/////回讀eeprom
	printf("\n  M1658A0_EEPROM_TEST   end*********** \n");
	
	LCD_Init();			//LCD初始化
	LCD_PWMinit(40);	//設置reset引腳---Alan
	key_Init();			////按鍵初始化
	LCD_SetLayer(1);	//切换到前景层
		Delay_ms(20);
		GPIO_ResetBits(LCD_PWM_PORT,LCD_PWM_PIN);  //输出置地
		Delay_ms(10);
		while(EEPROM_CHECK())	{		GPIO_ResetBits(LCD_PWM_PORT,LCD_PWM_PIN);while(1);  	}//////進行check eeprom ,NG則將reset置地，保持外接的LED常亮。。
		GPIO_SetBits(LCD_PWM_PORT,LCD_PWM_PIN);  //输出置高
		Delay_ms(150);
		
	while (1)
	{	
		
		LCD_DisplayMode(Mode_H); 	//横屏显示,,對於字符之類的超出屏範圍的，容易導致屏顯示無故中斷
		LCD_SetFont(&Font32);
		LCD_SetColor(LCD_YELLOW);
		LCD_DisplayString(440,20,"M1658A0_LCD_TEST");	//Delay_ms(time);
		LCD_DisplayString(440,20+32,"ColorMode: RGB888");	//Delay_ms(time);		
		LCD_DisplayString(440,20+32*2,"resolution: 1260x352    8'");
		DelayKEY_AutoRun(1000);	
		
		
		
		LCD_DisplayMode(Mode_H); 	//横屏显示,,對於字符之類的超出屏範圍的，容易導致屏顯示無故中斷
		LCD_SetBackColor(LCD_RED);   LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_GREEN);   LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_BLUE);LCD_Clear();  DelayKEY_AutoRun(1000);	
		
		LCD_SetBackColor(LCD_WHITE);  LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_GREY);  LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_BLACK);  LCD_Clear();  DelayKEY_AutoRun(1000);

		
		LCD_FLICKER_B();	LCD_FLICKER_B();							DelayKEY_AutoRun(1000);
		LCD_FLICKER_A();	LCD_FLICKER_A();							DelayKEY_AutoRun(1000);
		
		LCD_WriteBMP(0,0,352,1259,picc1);DelayKEY_AutoRun(1000);
		
		DelayKEY(2*1000);	///////暫停在此處，，，AutoRun的函數可以自動跑畫面，此函數默認是暫停。

	}
}
/*---------------------------- 测试函数 ---------------------------------*/

// 函数：透明度测试
//
void LCD_AlphaTest(void)
{
	LCD_DisplayMode(Mode_H);	//设置横屏
	LCD_SetFont(&Font32);		//设置字体

	LCD_SetLayer(0);		//切换到层0	
	LCD_SetColor(LCD_BLACK);	
	LCD_SetBackColor(LIGHT_BLUE);   
	LCD_Clear();
	LCD_DisplayString(100,60,"STM32F429 LCD Layer 0"); 

	LCD_SetLayer(1);	//切换到层1
	LCD_SetBackColor(LIGHT_YELLOW & 0x00FFFFFF);  //透明度100%，高8位的数字越小透明度越高
	LCD_Clear();											 //此时前景层完全透明

	LCD_SetColor(LCD_BLACK & 0x0DFFFFFF);		
	LCD_SetBackColor(LIGHT_YELLOW & 0x0DFFFFFF);  	
	LCD_DisplayString(100,100,"STM32F429 LCD Layer 1,Alpha:95%"); 

	LCD_SetColor(LCD_BLACK & 0x33FFFFFF);			
	LCD_SetBackColor(LIGHT_YELLOW & 0x33FFFFFF); 
	LCD_DisplayString(100,140,"STM32F429 LCD Layer 1,Alpha:80%"); 

	LCD_SetColor(LCD_BLACK & 0x66FFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0x66FFFFFF); 
	LCD_DisplayString(100,180,"STM32F429 LCD Layer 1,Alpha:60%"); 

	LCD_SetColor(LCD_BLACK & 0x99FFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0x99FFFFFF); 
	LCD_DisplayString(100,220,"STM32F429 LCD Layer 1,Alpha:40%"); 

	LCD_SetColor(LCD_BLACK & 0xccFFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0xCCFFFFFF); 
	LCD_DisplayString(100,260,"STM32F429 LCD Layer 1,Alpha:20%"); 

	LCD_SetColor(LCD_BLACK & 0xffFFFFFF);
	LCD_SetBackColor(LIGHT_YELLOW & 0xFFFFFFFF); 
	LCD_DisplayString(100,300,"STM32F429 LCD Layer 1,Alpha: 0%"); 

	Delay_ms(2000);
}

// 函数：清屏测试
//
void LCD_ClearTest(void)
{
	u16 time = 2000;	//延时时间
    u32 data=0x00000001;

//	LCD_DisplayMode(Mode_H); 	//横屏显示
	LCD_DisplayMode(Mode_V); 	//
	LCD_SetFont(&Font32);		//设置字体
	LCD_SetColor(LCD_BLACK);	//设置画笔颜色
//    while(1)
//    {
//        LCD_SetBackColor(data);   LCD_Clear();             Delay_ms(time);
//        data = data<<1;
//    }
//	LCD_SetBackColor(LIGHT_RED);   LCD_Clear(); LCD_DisplayString(100,200,"STM32F429 LCD TEST"); Delay_ms(time);
//	LCD_SetBackColor(LIGHT_GREEN); LCD_FillRect(1,  1,1022,598); LCD_DisplayString(100,200,"STM32F429 LCD TEST"); Delay_ms(time);
////	while(1);
//    
//    LCD_SetBackColor(LIGHT_YELLOW);LCD_Clear(); LCD_DisplayString(100,200,"STM32F429 LCD TEST"); Delay_ms(time);	
//	LCD_SetBackColor(LIGHT_BLUE);  LCD_Clear(); LCD_DisplayString(100,200,"STM32F429 LCD TEST"); Delay_ms(time);
//	LCD_SetBackColor(LIGHT_CYAN);  LCD_Clear(); LCD_DisplayString(100,200,"STM32F429 LCD TEST"); Delay_ms(time);
//	LCD_SetBackColor(LIGHT_GREY);  LCD_Clear(); LCD_DisplayString(100,200,"STM32F429 LCD TEST"); Delay_ms(time);
    
    LCD_SetBackColor(LCD_RED);   LCD_Clear();  Delay_ms(time);
		LCD_SetBackColor(LCD_GREEN);   LCD_Clear();  Delay_ms(time);
//		LCD_FillRect(1,  1,1278,350);  Delay_ms(time);
//	while(1);
    
    LCD_SetBackColor(LCD_BLUE);LCD_Clear();  Delay_ms(time);	
	
	
	LCD_SetBackColor(LCD_WHITE);  LCD_Clear();  Delay_ms(time);
	LCD_SetBackColor(LCD_WHITE);LCD_SetColor(LCD_BLACK);	//设置画笔颜色
//    LCD_FillRect(1,  1,LCD_Width-2,LCD_Height-2);  Delay_ms(1*time);
//		while(1);
		
    LCD_SetBackColor(LCD_GREY);  LCD_Clear();  Delay_ms(time);
    LCD_SetBackColor(LCD_BLACK);  LCD_Clear();  Delay_ms(time);
//		LCD_COLORBAR();															Delay_ms(time);
}
// 函数：文本测试
//
void LCD_TextTest(void)
{
	u16 time = 100;
	LCD_SetBackColor(LCD_BLACK); //设置背景色
//	LCD_SetBackColor(LCD_WHITE); //设置背景色
	LCD_Clear(); //清屏，刷背景色

//	LCD_SetColor(LCD_WHITE);
//	LCD_SetFont(&Font32); LCD_DisplayString(0, 0,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);		
//	LCD_SetFont(&Font24); LCD_DisplayString(0,32,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);
//	LCD_SetFont(&Font20); LCD_DisplayString(0,56,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);	
//	LCD_SetFont(&Font16); LCD_DisplayString(0,76,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);	
//	LCD_SetFont(&Font12); LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);	

//	LCD_SetColor(LCD_CYAN);                                                                            
//	LCD_SetFont(&Font12); LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);	
//	LCD_SetFont(&Font16); LCD_DisplayString(0,116,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);	
//	LCD_SetFont(&Font20); LCD_DisplayString(0,132,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);		
//	LCD_SetFont(&Font24); LCD_DisplayString(0,152,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);		
//	LCD_SetFont(&Font32); LCD_DisplayString(0,176,"!#$%&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRST"); Delay_ms(time);	

//	LCD_SetFont(&Font32);
//	LCD_SetColor(LCD_YELLOW);
//	LCD_DisplayNumber( 0,230,4294967295,10);  Delay_ms(time);		
//	LCD_DisplayNumber( 0,262,123456,6);	      Delay_ms(time);		
//	LCD_DisplayNumber( 0,294,1234,4);		   Delay_ms(time);		
//	LCD_DisplayNumber( 0,326,0,1);			   Delay_ms(time);		

	LCD_SetFont(&Font32);
//	LCD_SetColor(LIGHT_BLUE);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayString(440,20,"M1658A0_LCD_TEST");	//Delay_ms(time);
	LCD_DisplayString(440,20+32,"ColorMode: RGB888");	//Delay_ms(time);		

	DelayKEY_AutoRun(1000);	
}
// 函数：矩形填充测试
//
void LCD_FillTest(void)
{
	u16  i;
    
    LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

    Delay_ms(10);
    /////////单个函数无法实现每次都显示
//    for(i=0;i<1024;i+=4)
//	{
//		LCD_SetColor( 255*(1024-i)/1024 );
////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
//		LCD_FillRect(1*i/1,  400,4,  200);	
////		LCD_DrawLine(30+2*i+1,350,30+2*i+1,390);
//        
//        LCD_SetColor( (255*(1024-i)/1024)<<8 );
////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
//		LCD_FillRect(1*i/1,  200,4,  200);
//        
//        LCD_SetColor( (255*(1024-i)/1024)<<16 );
////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
//		LCD_FillRect(1*i/1,  0,4,  200);
//	}
    
    Delay_ms(10);
    /////////单个函数无法实现每次都显示
    for(i=0;i<LCD_Width;i+=4)
	{
		LCD_SetColor( 255*(LCD_Width-i)/LCD_Width );
//        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
		LCD_FillRect(1*i/1,  150,4,  100);	
//		LCD_DrawLine(30+2*i+1,350,30+2*i+1,390);
        
        LCD_SetColor( (255*(LCD_Width-i)/LCD_Width)<<8 );
//        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
		LCD_FillRect(1*i/1,  250,2,  100);
        
        LCD_SetColor( (255*(LCD_Width-i)/LCD_Width)<<16 );
//        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
		LCD_FillRect(1*i/1,  350,2,  100);LCD_DisplayString(0,  3,"LCD_BLUE");
////        i++;i++;i++;i++;i++;i++;i++;i++;
////        i--;i--;i--;i--;i--;i--;i--;i--;
	}
    Delay_ms(2000);

	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(200,  3,500,16);	LCD_DisplayString(0,  3,"LCD_BLUE");		
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(200, 25,500,16);  LCD_DisplayString(0, 25,"LCD_GREEN");		
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(200, 47,500,16);  LCD_DisplayString(0, 47,"LCD_RED");			
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(200, 69,500,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(200, 91,500,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(200,113,500,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(200,135,500,16);	LCD_DisplayString(0,135,"LCD_GREY");		

	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(200,157,500,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(200,179,500,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(200,201,500,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(200,223,500,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(200,245,500,16);  LCD_DisplayString(0,245,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(200,267,500,16);  LCD_DisplayString(0,267,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(200,289,500,16);	LCD_DisplayString(0,289,"LIGHT_GREY");  	

	LCD_SetColor(DARK_BLUE);	  LCD_FillRect(200,311,500,16);  LCD_DisplayString(0,311,"DARK_BLUE");		
	LCD_SetColor(DARK_GREEN);    LCD_FillRect(200,333,500,16);  LCD_DisplayString(0,333,"DARK_GREEN");		
	LCD_SetColor(DARK_RED);      LCD_FillRect(200,355,500,16);  LCD_DisplayString(0,355,"DARK_RED");		
	LCD_SetColor(DARK_CYAN);     LCD_FillRect(200,377,500,16);  LCD_DisplayString(0,377,"DARK_CYAN");		
	LCD_SetColor(DARK_MAGENTA);  LCD_FillRect(200,399,500,16);  LCD_DisplayString(0,399,"DARK_MAGENTA");	
	LCD_SetColor(DARK_YELLOW);   LCD_FillRect(200,421,500,16);  LCD_DisplayString(0,421,"DARK_YELLOW");	
	LCD_SetColor(DARK_GREY);     LCD_FillRect(200,443,500,16);	LCD_DisplayString(0,443,"DARK_GREY");		

	Delay_ms(2000);
}

void LCD_COLORBAR(void)
{
    u16  i,j,index;
	u32 color_set=0;
//    LCD_SetBackColor(LCD_BLACK); //设置背景色
//	LCD_Clear(); //清屏，刷背景色
//    
////    LCD_SetColor( 0xFFFFFFFF );
////    LCD_Clear();
//    Delay_ms(2);
    
//    LCD_SetColor(LCD_WHITE);
//    for(i=0;i<LCD_Width-1;i++)
//	{
//		color_set = 0XFF*(i)/LCD_Width;
//		LCD_SetColor( color_set );
//		LCD_FillRect(i,  LCD_Height*0/4,1,  LCD_Height/4);	//LCD_DisplayString(0,  3,"LCD_BLUE");
//	
//		color_set = (( 0XFF*(i)/LCD_Width )<<8);
//     LCD_SetColor(color_set);
//		LCD_FillRect(i,  90,1,  LCD_Height/4);
//	
//		color_set = (( 0XFF*(i)/LCD_Width )<<16);
//		LCD_SetColor(color_set);
//		LCD_FillRect(i,  180,1,  LCD_Height/4);
//		
//		color_set = (( 0XFF*(i)/LCD_Width )<<24);
//		LCD_SetColor(color_set);
//		LCD_FillRect(i,  270,1,  LCD_Height/4);
//		
////        LCD_SetColor( (255*(1024-i)/1024)<<8 );
//////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
////		LCD_FillRect(1*i/1,  200,4,  200);
////        
////        LCD_SetColor( (255*(1024-i)/1024)<<16 );
//////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
////		LCD_FillRect(1*i/1,  0,4,  200);
//	}

//    for(i=0;i<LCD_Width-1;i++)
//		{
//			for(j=0;j<LCD_Height-1;j++)
//			{
//				color_set = 0XFF*(i)/LCD_Width;
//				LCD_DrawPoint(i,j,color_set);	//使用画笔色绘点
//			}
//		}
		
		for(i=0;i<LCD_Height*1/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = 0XFF*(j)/LCD_Width;
				LCD_DrawPoint(j,i,color_set);	//使用画笔色绘点
			}
		}
		
		for(i=LCD_Height*1/4;i<LCD_Height*2/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = (0XFF*(j)/LCD_Width)<<8;color_set = (0XFF*(j)/LCD_Width)<<8;
				color_set = (0XFF*(j)/LCD_Width)<<8;color_set = (0XFF*(j)/LCD_Width)<<8;
				LCD_DrawPoint(j,i,color_set);	//使用画笔色绘点
			}
		}
		
		for(i=LCD_Height*2/4;i<LCD_Height*3/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = (0XFF*(j)/LCD_Width)<<16;color_set = (0XFF*(j)/LCD_Width)<<16;
				color_set = (0XFF*(j)/LCD_Width)<<16;color_set = (0XFF*(j)/LCD_Width)<<16;
				LCD_DrawPoint(j,i,color_set);	//使用画笔色绘点
			}
		}
		
		for(i=LCD_Height*3/4;i<LCD_Height*4/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = (0XFF*(j)/LCD_Width)<<24;color_set = (0XFF*(j)/LCD_Width)<<24;
				color_set = (0XFF*(j)/LCD_Width)<<24;color_set = (0XFF*(j)/LCD_Width)<<24;
				LCD_DrawPoint(j,i,color_set);	//使用画笔色绘点
			}
		}
    Delay_ms(2000);
}

// 函数：颜色测试
//
void LCD_ColorTest(void)
{
	u16 i;

	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_BLACK);

	LCD_SetBackColor(LIGHT_BLUE); LCD_DisplayString(30, 40,"STM32F429 LTDC ColorTest"); 
	LCD_SetBackColor(LCD_RED);    LCD_DisplayString(30, 80,"STM32F429 LTDC ColorTest");
	LCD_SetBackColor(LCD_CYAN);   LCD_DisplayString(30,120,"STM32F429 LTDC ColorTest");
	LCD_SetBackColor(LCD_YELLOW); LCD_DisplayString(30,160,"STM32F429 LTDC ColorTest");	
	
	//使用画线函数绘制三基色色条
	for(i=0;i<255;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
		LCD_DrawLine(30+2*i,  240,30+2*i,  280);	
		LCD_DrawLine(30+2*i+1,240,30+2*i+1,280);
	}
    Delay_ms(10);
	for(i=0;i<255;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
		LCD_DrawLine(30+2*i,  290,30+2*i,  330);	
		LCD_DrawLine(30+2*i+1,290,30+2*i+1,330);
	}
    Delay_ms(10);
	for(i=0;i<255;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
		LCD_DrawLine(30+2*i,  350,30+2*i,  390);	
		LCD_DrawLine(30+2*i+1,350,30+2*i+1,390);
	}
    Delay_ms(10);	
    
//    Delay_ms(10);
//    /////////单个函数无法实现每次都显示
//    for(i=0;i<1024;i+=4)
//	{
//		LCD_SetColor( 255*(1024-i)/1024 );
////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
//		LCD_FillRect(1*i/1,  450,4,  100);	
////		LCD_DrawLine(30+2*i+1,350,30+2*i+1,390);
//        
////        LCD_SetColor( (255*(1024-i)/1024)<<8 );
//////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
////		LCD_FillRect(1*i/1,  550,2,  100);
////        
////        LCD_SetColor( (255*(1024-i)/1024)<<16 );
//////        LCD_FillRect(1024*i/255,  450,1024*(0+1)/255,  1024*(0+1)/255);
////		LCD_FillRect(1*i/1,  350,2,  100);
//////        i++;i++;i++;i++;i++;i++;i++;i++;
//////        i--;i--;i--;i--;i--;i--;i--;i--;
//	}
    

    
	Delay_ms(2000);	
}
// 函数：绘图测试
//
void LCD_GrahicTest(void)
{
	u16 time = 80;

	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	

	LCD_SetColor(LCD_RED);    LCD_FillCircle(120,350,80);		//填充圆形
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(170,350,80); 	//
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(220,350,80);  	

	LCD_SetColor(LIGHT_GREY);
	LCD_DrawLine(5,5,400,5);	Delay_ms(time);	//画直线
	LCD_DrawLine(5,10,300,10);	Delay_ms(time);
	LCD_DrawLine(5,15,200,15);  Delay_ms(time);
	LCD_DrawLine(5,20,100,20);	Delay_ms(time);	

	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(600,120,100);	Delay_ms(time);	//绘制圆形
	LCD_DrawCircle(600,120,80);   Delay_ms(time);
	LCD_DrawCircle(600,120,60);   Delay_ms(time);
	LCD_DrawCircle(600,120,40);   Delay_ms(time);

	LCD_SetColor(LCD_RED);	
	LCD_DrawRect(5,35,400,150);  Delay_ms(time);	//绘制矩形
	LCD_DrawRect(30,50,350,120); Delay_ms(time);
	LCD_DrawRect(55,65,300,90);  Delay_ms(time);
	LCD_DrawRect(80,80,250,60);  Delay_ms(time);

	LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(590,350,200,100); Delay_ms(time);	//绘制椭圆
	LCD_DrawEllipse(590,350,170,80);  Delay_ms(time);
	LCD_DrawEllipse(590,350,140,60);  Delay_ms(time);
	LCD_DrawEllipse(590,350,110,40);  Delay_ms(time);

	Delay_ms(2000);	
}
// 函数：竖屏测试
//
void  LCD_Vertical_Test(void)
{
	u16 i;
	u16 time = 100;	

	LCD_DisplayMode(Mode_V); //横屏显示
	LCD_SetLayer(1);
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色		

	LCD_SetColor(LCD_WHITE);
	LCD_SetFont(&Font32);LCD_DisplayString(0, 0,"!#$%&'()*+,-.0123456789:;<=>"); Delay_ms(time);		
	LCD_SetFont(&Font24);LCD_DisplayString(0,32,"!#$%&'()*+,-.0123456789:;<=>"); Delay_ms(time);
	LCD_SetFont(&Font20);LCD_DisplayString(0,56,"!#$%&'()*+,-.0123456789:;<=>"); Delay_ms(time);	
	LCD_SetFont(&Font16);LCD_DisplayString(0,76,"!#$%&'()*+,-.0123456789:;<=>"); Delay_ms(time);	
	LCD_SetFont(&Font12);LCD_DisplayString(0,92,"!#$%&'()*+,-.0123456789:;<=>"); Delay_ms(time);	
                                                                                                      
	LCD_SetColor(LCD_CYAN);                                                                            
	LCD_SetFont(&Font12);LCD_DisplayString(0,104,"!#$%&'()*+,-.0123456789:;<=>");Delay_ms(time);	
	LCD_SetFont(&Font16);LCD_DisplayString(0,116,"!#$%&'()*+,-.0123456789:;<=>");Delay_ms(time);	
	LCD_SetFont(&Font20);LCD_DisplayString(0,132,"!#$%&'()*+,-.0123456789:;<=>");Delay_ms(time);		
	LCD_SetFont(&Font24);LCD_DisplayString(0,152,"!#$%&'()*+,-.0123456789:;<=>");Delay_ms(time);		
	LCD_SetFont(&Font32);LCD_DisplayString(0,176,"!#$%&'()*+,-.0123456789:;<=>");Delay_ms(time);	

	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayNumber( 0,230, 4294967295,10); Delay_ms(time);		
	LCD_DisplayNumber( 0,262,123456,6);	      Delay_ms(time);		
	LCD_DisplayNumber( 0,294,1234,4);		   Delay_ms(time);		
	LCD_DisplayNumber( 0,326,0,0);			   Delay_ms(time);		
	 
	LCD_SetFont(&Font32);
	LCD_SetColor(LIGHT_BLUE);
	LCD_DisplayString(40,550,"STM32F429 LCD TEST");Delay_ms(time);
	LCD_DisplayString(40,550+32,"ColorMode: RGB888");Delay_ms(time);		

	LCD_SetFont(&Font32);
	LCD_SetColor(LIGHT_BLUE);
	LCD_DisplayString(40,700,"LCD VERTICAL MODE");Delay_ms(time);

	Delay_ms(2000);

	time = 80;
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	
	
	LCD_SetColor(LCD_RED);    LCD_FillCircle(120,285,80);	
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(170,285,80); 
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(220,285,80);  	
	
   LCD_SetColor(LCD_RED);	
	LCD_DrawRect(5,35,350,150);  Delay_ms(time);
	LCD_DrawRect(30,50,300,120); Delay_ms(time);
	LCD_DrawRect(55,65,250,90);  Delay_ms(time);
	LCD_DrawRect(80,80,200,60);  Delay_ms(time);
	
	LCD_SetColor(LIGHT_GREY);
	LCD_DrawLine(5,5,400,5);	Delay_ms(time);
	LCD_DrawLine(5,10,300,10);	Delay_ms(time);
	LCD_DrawLine(5,15,200,15); Delay_ms(time);
	LCD_DrawLine(5,20,100,20);	Delay_ms(time);		
	
   
   LCD_SetColor(LCD_YELLOW);	LCD_DrawCircle(100,480,80);   Delay_ms(time);
	LCD_SetColor(LCD_CYAN);		LCD_DrawCircle(150,480,80);   Delay_ms(time);
   LCD_SetColor(LCD_MAGENTA); LCD_DrawCircle(200,480,80);   Delay_ms(time);
   LCD_SetColor(LCD_RED);		LCD_DrawCircle(250,480,80);   Delay_ms(time);

   LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(200,680,200,100); Delay_ms(time);
	LCD_DrawEllipse(200,680,170,80);  Delay_ms(time);
	LCD_DrawEllipse(200,680,140,60);  Delay_ms(time);
	LCD_DrawEllipse(200,680,110,40);  Delay_ms(time);
                                                        
	Delay_ms(2000);	
	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色

	LCD_SetFont(&Font16);
	LCD_SetColor(LCD_BLUE);	  	  LCD_FillRect(150,  3,250,16);	LCD_DisplayString(0,  3,"LCD_BLUE"); LCD_DisplayString(0,509,"0X0000FF");			
	LCD_SetColor(LCD_GREEN);  	  LCD_FillRect(150, 25,250,16);  LCD_DisplayString(0, 25,"LCD_GREEN");LCD_DisplayString(0,487,"0X00FF00");	
	LCD_SetColor(LCD_RED);    	  LCD_FillRect(150, 47,250,16);  LCD_DisplayString(0, 47,"LCD_RED");	 LCD_DisplayString(0,465,"0XFF0000");	
	LCD_SetColor(LCD_CYAN);   	  LCD_FillRect(150, 69,250,16);  LCD_DisplayString(0, 69,"LCD_CYAN");		
	LCD_SetColor(LCD_MAGENTA);	  LCD_FillRect(150, 91,250,16);  LCD_DisplayString(0, 91,"LCD_MAGENTA");	
	LCD_SetColor(LCD_YELLOW); 	  LCD_FillRect(150,113,250,16);  LCD_DisplayString(0,113,"LCD_YELLOW");		
	LCD_SetColor(LCD_GREY);   	  LCD_FillRect(150,135,250,16);	LCD_DisplayString(0,135,"LCD_GREY");		
                                                                                          
	LCD_SetColor(LIGHT_BLUE);	  LCD_FillRect(150,157,250,16);  LCD_DisplayString(0,157,"LIGHT_BLUE");		
	LCD_SetColor(LIGHT_GREEN);   LCD_FillRect(150,179,250,16);  LCD_DisplayString(0,179,"LIGHT_GREEN");	
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(150,201,250,16);  LCD_DisplayString(0,201,"LIGHT_RED");	   
	LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(150,223,250,16);  LCD_DisplayString(0,223,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(150,245,250,16);  LCD_DisplayString(0,245,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(150,267,250,16);  LCD_DisplayString(0,267,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(150,289,250,16);	LCD_DisplayString(0,289,"LIGHT_GREY");  	
	                                                                                       
	LCD_SetColor(DARK_BLUE);	  LCD_FillRect(150,311,250,16);  LCD_DisplayString(0,311,"DARK_BLUE");		
	LCD_SetColor(DARK_GREEN);    LCD_FillRect(150,333,250,16);  LCD_DisplayString(0,333,"DARK_GREEN");		
	LCD_SetColor(DARK_RED);      LCD_FillRect(150,355,250,16);  LCD_DisplayString(0,355,"DARK_RED");		
	LCD_SetColor(DARK_CYAN);     LCD_FillRect(150,377,250,16);  LCD_DisplayString(0,377,"DARK_CYAN");		
	LCD_SetColor(DARK_MAGENTA);  LCD_FillRect(150,399,250,16);  LCD_DisplayString(0,399,"DARK_MAGENTA");	
	LCD_SetColor(DARK_YELLOW);   LCD_FillRect(150,421,250,16);  LCD_DisplayString(0,421,"DARK_YELLOW");	
	LCD_SetColor(DARK_GREY);     LCD_FillRect(150,443,250,16);	LCD_DisplayString(0,443,"DARK_GREY");		
	                                           
	//刷颜色条
	for(i=0;i<255;i++){LCD_SetColor( LCD_RED-(i<<16) ); 	LCD_DrawLine(150+i,465,150+i,481);}
	for(i=0;i<255;i++){LCD_SetColor( LCD_GREEN-(i<<8) );	LCD_DrawLine(150+i,487,150+i,503);}
	for(i=0;i<255;i++){LCD_SetColor( LCD_BLUE-i );		 	LCD_DrawLine(150+i,509,150+i,525);}
	for(i=0;i<255;i++){LCD_SetColor( LIGHT_RED-(i<<16) );	LCD_DrawLine(150+i,531,150+i,547);}LCD_DisplayString(0,531,"0xFF8080");
	for(i=0;i<255;i++){LCD_SetColor( LIGHT_GREEN-(i<<8) );LCD_DrawLine(150+i,553,150+i,568);}LCD_DisplayString(0,553,"0x80FF80");
	for(i=0;i<255;i++){LCD_SetColor( LIGHT_BLUE-i );		LCD_DrawLine(150+i,575,150+i,591);}LCD_DisplayString(0,575,"0x8080FF");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_BLUE-(i<<16) );	LCD_DrawLine(150+i,597,150+i,613);}LCD_DisplayString(0,597,"0x000080");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_BLUE-(i<<8) );	LCD_DrawLine(150+i,619,150+i,635);}LCD_DisplayString(0,619,"0x000080");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_RED-i );			LCD_DrawLine(150+i,641,150+i,657);}LCD_DisplayString(0,641,"0x800000");		
	for(i=0;i<255;i++){LCD_SetColor( DARK_RED-(i<<8));		LCD_DrawLine(150+i,663,150+i,679);}LCD_DisplayString(0,663,"0x800000");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_GREEN-(i<<16)); LCD_DrawLine(150+i,685,150+i,701);}LCD_DisplayString(0,685,"0x008000");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_GREEN-i);			LCD_DrawLine(150+i,707,150+i,723);}LCD_DisplayString(0,707,"0x008000");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_CYAN-(i<<16));	LCD_DrawLine(150+i,729,150+i,745);}LCD_DisplayString(0,729,"0x008080");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_YELLOW-i);		LCD_DrawLine(150+i,751,150+i,767);}LCD_DisplayString(0,751,"0x808000");	
	for(i=0;i<255;i++){LCD_SetColor( DARK_MAGENTA-(i<<8));LCD_DrawLine(150+i,773,150+i,789);}LCD_DisplayString(0,773,"0x800080");	

	Delay_ms(2000);	
}




