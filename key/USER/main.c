#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"


int main(void)
{ 
 
    u8 Val;           //保存键值
	delay_init(168);      //初始化延时函数
	LED_Init();			  //初始化LED端口 
	KEY_Init();           //初始化与按键连接的硬件接口
	LED0=1;			   	//先点亮红灯
	LED1=0;			   	//先关闭绿灯
	while(1)
	{
		Val=key();		//得到键值
	   	if(Val)
		{						   
			switch(Val)
			{				 
				case 1:
				case 2:		
				case 3:			
				case 4:				
				case 5:				
				case 6:					
				case 7:				
				case 8:	
					LED0=!LED0;
					break;
				
				case 9:								
				case 10:			
				case 11:			
				case 12:			
				case 13:			
				case 14:
				case 15:
				case 16:	
					LED1 =!LED1;
					break;

			}
		}
		else 
		{
			delay_ms(10);
		}
	}

}
