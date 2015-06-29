#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"


int main(void)
{ 
 
    u8 Val;           //�����ֵ
	delay_init(168);      //��ʼ����ʱ����
	LED_Init();			  //��ʼ��LED�˿� 
	KEY_Init();           //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED0=1;			   	//�ȵ������
	LED1=0;			   	//�ȹر��̵�
	while(1)
	{
		Val=key();		//�õ���ֵ
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
