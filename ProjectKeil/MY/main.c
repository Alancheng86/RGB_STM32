/***
	************************************************************************************************
	*	@file  	main.c
	*	@version V1.0.0
	*  @date    2017-5-10	
	*	@author  ���ͿƼ�
	*	@brief   ����AT070TN83������ʾ
   ************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨������STM32F429���İ�
	*	�Ա���ַ��https://shop212360197.taobao.com
	*	QQ����Ⱥ��536665479
	*	
	*	��Ҫ˵����
	*
	*	1.ʹ�ú��İ���83��������ʱ��Ҫʹ��ͬ���FPC����
	*	2.����83��Ļ���Ĺ��󣬳�����һ���USB�ڹ�����������������ʹ��PWM�����Ʊ��⣬ռ�ձ�40%��Ƶ��200Hz
	*	3.�ڸ����س���ʱ����ϵ�ʱ����Ļ����΢����������������Ƭ�̼��ɻָ�����			
	*	4.83������������ڷ���7.0RGBҺ�����ĳ����������˼����������ŵĳ�ʼ��������û�б䶯
	*	5.����RGB��Ļ��ʾʱ��32��SDRAMоƬ����΢��������������
	*	6.��������Ļ�����Ե����Ƶ��룬��ʹ�ô��ʵ�5V��Դ���и���
	*
	*	�������ԣ�
	*	
	*	�������ݵĲ�������Ϊ���ֱ���800*480��FPC���߳���Ϊ20cm����ν�������Ƶ����ָ��ʾ����������������
	*	��ʱ���޻���������ʹ�ø��ߵ�����Ƶ�ʿ��ܻ�������ʱ��ɶ��ݵĻ�����ֻ��������ʾ��ʹ�ø��̵�����
	*	��������ʹ�ø��ߵ�����Ƶ�ʣ���ز�����lcd_rgb.h��������á�
	*	1.ֻ��������ʾ�£�16λɫģʽ�������Ƶ��70M
	*	2.ֻ��������ʾ�£�24λɫģʽ�������Ƶ��52M
	*	3.ֻ��������ʾ�£�32λɫģʽ�������Ƶ��38M
	*	4.��˫����ʾ�£�RGB565��ARGB1555ģʽ�£��������Ƶ��40M
	*	5.��˫����ʾ�£�RGB565��ARGB8888ģʽ�£��������Ƶ��25M
	*  5.��˫����ʾ�£�RGB888��ARGB1555ģʽ�£��������Ƶ��36M
	*	5.��˫����ʾ�£�RGB888��ARGB8888ģʽ�£��������Ƶ��22M
	*	
	*	����˵����
	*
	*	1.STM32F29��͸����������������ʾ��֮��
	*	2.�ڷֱ���Ϊ800*480ʱ������Ƶ����33M���ҾͿ��Դﵽ60֡��ˢ���ʣ�һ��ʹ�����Ƶ�ʾ��㹻��
	*	3.������ʾ�£�ǰ����Ӧ����Ϊ��͸��ɫ����ɫģʽ����Ȼ���޷����������㣬�Ƽ�ʹ��RGB565+ARGB8888�Ĵ���
	*	4.��Ļ�ڸ����ػ��߸��ϵ��ʱ������΢����˸������������Ƭ�̾ͻ���ʧ��ʹ��Խ�͵�����Ƶ����˸Խ����  
	*	5.��lcd_rgb.h�ﶨ����һЩ���õ���ɫ����8λΪ͸��ɫ��ֻ��ARGB8888��ARGB1555ģʽ����Ч��ARGB1555ֻ��
	*	  �ڸ�8λΪ0ʱ�Ż���ʾ͸����
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







void LCD_ClearTest(void);		// ��������
void LCD_TextTest(void);		// �ı���ʾ����
void LCD_FillTest(void);		// ����������
void LCD_ColorTest(void);		// ��ɫ����
void LCD_GrahicTest(void);		// ��ͼ����
void LCD_AlphaTest(void);		// ͸���Ȳ���
void LCD_Vertical_Test(void);	// ��ֱ��ʾ����

void LCD_COLORBAR(void);







void LCD_Test(void)		// LCD����
{
	
	
	LCD_DisplayMode(Mode_H); 	//������ʾ,,����ַ�֮ĳ����������ģ����׌������@ʾ�o���Д�
	
//	LCD_TextTest();
	LCD_SetFont(&Font32);
//	LCD_SetColor(LIGHT_BLUE);
	LCD_SetColor(LCD_YELLOW);
	LCD_DisplayString(440,20,"M1658A0_LCD_TEST");	//Delay_ms(time);
	LCD_DisplayString(440,20+32,"ColorMode: RGB888");	//Delay_ms(time);		

	DelayKEY_AutoRun(1000);	
	
	
	
	LCD_DisplayMode(Mode_H); 	//������ʾ,,����ַ�֮ĳ����������ģ����׌������@ʾ�o���Д�
	LCD_SetBackColor(LCD_RED);   LCD_Clear();  DelayKEY_AutoRun(1000);
	LCD_SetBackColor(LCD_GREEN);   LCD_Clear();  DelayKEY_AutoRun(1000);
    LCD_SetBackColor(LCD_BLUE);LCD_Clear();  DelayKEY_AutoRun(1000);	
	
	LCD_SetBackColor(LCD_WHITE);  LCD_Clear();  DelayKEY_AutoRun(1000);
    LCD_SetBackColor(LCD_GREY);  LCD_Clear();  DelayKEY_AutoRun(1000);
    LCD_SetBackColor(LCD_BLACK);  LCD_Clear();  DelayKEY_AutoRun(1000);
	
//	LCD_SetBackColor(LCD_WHITE);  LCD_Clear();
//	LCD_SetBackColor(LCD_WHITE);LCD_SetColor(LCD_BLACK);	//���û�����ɫ
//    LCD_FillRect(1,  1,LCD_Width-2,LCD_Height-2);  DelayKEY_AutoRun(1*2000);
	
	LCD_FLICKER_B();	LCD_FLICKER_B();							DelayKEY_AutoRun(1000);
	LCD_FLICKER_A();	LCD_FLICKER_A();							DelayKEY_AutoRun(1000);
	
	LCD_WriteBMP(0,0,352,1259,picc1);DelayKEY_AutoRun(1000);
	
	DelayKEY(2*1000);



}
/*---------------------------- ������ ---------------------------------*/

int main(void)
{
	LED_Init();			//LED��ʼ��
	Delay_Init();		//��ʱ������ʼ��
	Usart_Config();  //���ڳ�ʼ��
	LCD_SPI_Init();		/////SPI ��ʼ��
	
	printf("\n  M1658A0_EEPROM_TEST   start********* \n");
#ifdef OTP_FORCE_ON
			WRITE_EEPROM_DATA();///////���eeprom
#endif		
	
	READ_EEPROM_DATA();				/////���xeeprom
	printf("\n  M1658A0_EEPROM_TEST   end*********** \n");
	
	LCD_Init();			//LCD��ʼ��
	LCD_PWMinit(40);	//�O��reset���_---Alan
	key_Init();			////���I��ʼ��
	LCD_SetLayer(1);	//�л���ǰ����
		Delay_ms(20);
		GPIO_ResetBits(LCD_PWM_PORT,LCD_PWM_PIN);  //����õ�
		Delay_ms(10);
		while(EEPROM_CHECK())	{		GPIO_ResetBits(LCD_PWM_PORT,LCD_PWM_PIN);while(1);  	}//////�M��check eeprom ,NG�t��reset�õأ�������ӵ�LED��������
		GPIO_SetBits(LCD_PWM_PORT,LCD_PWM_PIN);  //����ø�
		Delay_ms(150);
		
	while (1)
	{	
		
		LCD_DisplayMode(Mode_H); 	//������ʾ,,����ַ�֮ĳ����������ģ����׌������@ʾ�o���Д�
		LCD_SetFont(&Font32);
		LCD_SetColor(LCD_YELLOW);
		LCD_DisplayString(440,20,"M1658A0_LCD_TEST");	//Delay_ms(time);
		LCD_DisplayString(440,20+32,"ColorMode: RGB888");	//Delay_ms(time);		
		LCD_DisplayString(440,20+32*2,"resolution: 1260x352    8'");
		DelayKEY_AutoRun(1000);	
		
		
		
		LCD_DisplayMode(Mode_H); 	//������ʾ,,����ַ�֮ĳ����������ģ����׌������@ʾ�o���Д�
		LCD_SetBackColor(LCD_RED);   LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_GREEN);   LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_BLUE);LCD_Clear();  DelayKEY_AutoRun(1000);	
		
		LCD_SetBackColor(LCD_WHITE);  LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_GREY);  LCD_Clear();  DelayKEY_AutoRun(1000);
		LCD_SetBackColor(LCD_BLACK);  LCD_Clear();  DelayKEY_AutoRun(1000);

		
		LCD_FLICKER_B();	LCD_FLICKER_B();							DelayKEY_AutoRun(1000);
		LCD_FLICKER_A();	LCD_FLICKER_A();							DelayKEY_AutoRun(1000);
		
		LCD_WriteBMP(0,0,352,1259,picc1);DelayKEY_AutoRun(1000);
		
		DelayKEY(2*1000);	///////��ͣ�ڴ�̎������AutoRun�ĺ��������Ԅ��ܮ��棬�˺���Ĭ�J�Ǖ�ͣ��

	}
}
/*---------------------------- ���Ժ��� ---------------------------------*/

// ������͸���Ȳ���
//
void LCD_AlphaTest(void)
{
	LCD_DisplayMode(Mode_H);	//���ú���
	LCD_SetFont(&Font32);		//��������

	LCD_SetLayer(0);		//�л�����0	
	LCD_SetColor(LCD_BLACK);	
	LCD_SetBackColor(LIGHT_BLUE);   
	LCD_Clear();
	LCD_DisplayString(100,60,"STM32F429 LCD Layer 0"); 

	LCD_SetLayer(1);	//�л�����1
	LCD_SetBackColor(LIGHT_YELLOW & 0x00FFFFFF);  //͸����100%����8λ������ԽС͸����Խ��
	LCD_Clear();											 //��ʱǰ������ȫ͸��

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

// ��������������
//
void LCD_ClearTest(void)
{
	u16 time = 2000;	//��ʱʱ��
    u32 data=0x00000001;

//	LCD_DisplayMode(Mode_H); 	//������ʾ
	LCD_DisplayMode(Mode_V); 	//
	LCD_SetFont(&Font32);		//��������
	LCD_SetColor(LCD_BLACK);	//���û�����ɫ
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
	LCD_SetBackColor(LCD_WHITE);LCD_SetColor(LCD_BLACK);	//���û�����ɫ
//    LCD_FillRect(1,  1,LCD_Width-2,LCD_Height-2);  Delay_ms(1*time);
//		while(1);
		
    LCD_SetBackColor(LCD_GREY);  LCD_Clear();  Delay_ms(time);
    LCD_SetBackColor(LCD_BLACK);  LCD_Clear();  Delay_ms(time);
//		LCD_COLORBAR();															Delay_ms(time);
}
// �������ı�����
//
void LCD_TextTest(void)
{
	u16 time = 100;
	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
//	LCD_SetBackColor(LCD_WHITE); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ

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
// ����������������
//
void LCD_FillTest(void)
{
	u16  i;
    
    LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ

    Delay_ms(10);
    /////////���������޷�ʵ��ÿ�ζ���ʾ
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
    /////////���������޷�ʵ��ÿ�ζ���ʾ
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
//    LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
//	LCD_Clear(); //������ˢ����ɫ
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
//				LCD_DrawPoint(i,j,color_set);	//ʹ�û���ɫ���
//			}
//		}
		
		for(i=0;i<LCD_Height*1/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = 0XFF*(j)/LCD_Width;
				LCD_DrawPoint(j,i,color_set);	//ʹ�û���ɫ���
			}
		}
		
		for(i=LCD_Height*1/4;i<LCD_Height*2/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = (0XFF*(j)/LCD_Width)<<8;color_set = (0XFF*(j)/LCD_Width)<<8;
				color_set = (0XFF*(j)/LCD_Width)<<8;color_set = (0XFF*(j)/LCD_Width)<<8;
				LCD_DrawPoint(j,i,color_set);	//ʹ�û���ɫ���
			}
		}
		
		for(i=LCD_Height*2/4;i<LCD_Height*3/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = (0XFF*(j)/LCD_Width)<<16;color_set = (0XFF*(j)/LCD_Width)<<16;
				color_set = (0XFF*(j)/LCD_Width)<<16;color_set = (0XFF*(j)/LCD_Width)<<16;
				LCD_DrawPoint(j,i,color_set);	//ʹ�û���ɫ���
			}
		}
		
		for(i=LCD_Height*3/4;i<LCD_Height*4/4-1;i++)
		{
			for(j=0;j<LCD_Width-1;j++)
			{
				color_set = (0XFF*(j)/LCD_Width)<<24;color_set = (0XFF*(j)/LCD_Width)<<24;
				color_set = (0XFF*(j)/LCD_Width)<<24;color_set = (0XFF*(j)/LCD_Width)<<24;
				LCD_DrawPoint(j,i,color_set);	//ʹ�û���ɫ���
			}
		}
    Delay_ms(2000);
}

// ��������ɫ����
//
void LCD_ColorTest(void)
{
	u16 i;

	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ
	LCD_SetFont(&Font32);
	LCD_SetColor(LCD_BLACK);

	LCD_SetBackColor(LIGHT_BLUE); LCD_DisplayString(30, 40,"STM32F429 LTDC ColorTest"); 
	LCD_SetBackColor(LCD_RED);    LCD_DisplayString(30, 80,"STM32F429 LTDC ColorTest");
	LCD_SetBackColor(LCD_CYAN);   LCD_DisplayString(30,120,"STM32F429 LTDC ColorTest");
	LCD_SetBackColor(LCD_YELLOW); LCD_DisplayString(30,160,"STM32F429 LTDC ColorTest");	
	
	//ʹ�û��ߺ�����������ɫɫ��
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
//    /////////���������޷�ʵ��ÿ�ζ���ʾ
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
// ��������ͼ����
//
void LCD_GrahicTest(void)
{
	u16 time = 80;

	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ	

	LCD_SetColor(LCD_RED);    LCD_FillCircle(120,350,80);		//���Բ��
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(170,350,80); 	//
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(220,350,80);  	

	LCD_SetColor(LIGHT_GREY);
	LCD_DrawLine(5,5,400,5);	Delay_ms(time);	//��ֱ��
	LCD_DrawLine(5,10,300,10);	Delay_ms(time);
	LCD_DrawLine(5,15,200,15);  Delay_ms(time);
	LCD_DrawLine(5,20,100,20);	Delay_ms(time);	

	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(600,120,100);	Delay_ms(time);	//����Բ��
	LCD_DrawCircle(600,120,80);   Delay_ms(time);
	LCD_DrawCircle(600,120,60);   Delay_ms(time);
	LCD_DrawCircle(600,120,40);   Delay_ms(time);

	LCD_SetColor(LCD_RED);	
	LCD_DrawRect(5,35,400,150);  Delay_ms(time);	//���ƾ���
	LCD_DrawRect(30,50,350,120); Delay_ms(time);
	LCD_DrawRect(55,65,300,90);  Delay_ms(time);
	LCD_DrawRect(80,80,250,60);  Delay_ms(time);

	LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(590,350,200,100); Delay_ms(time);	//������Բ
	LCD_DrawEllipse(590,350,170,80);  Delay_ms(time);
	LCD_DrawEllipse(590,350,140,60);  Delay_ms(time);
	LCD_DrawEllipse(590,350,110,40);  Delay_ms(time);

	Delay_ms(2000);	
}
// ��������������
//
void  LCD_Vertical_Test(void)
{
	u16 i;
	u16 time = 100;	

	LCD_DisplayMode(Mode_V); //������ʾ
	LCD_SetLayer(1);
	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ		

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
	
	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ	
	
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
	
	LCD_SetBackColor(LCD_BLACK); //���ñ���ɫ
	LCD_Clear(); //������ˢ����ɫ

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
	                                           
	//ˢ��ɫ��
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




