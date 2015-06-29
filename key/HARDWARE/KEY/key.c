#include "key.h"
#include "delay.h" 

void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOE,GPIOF时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; //4行对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉输出
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOF0,2,4,6
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; //4列对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //普通入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE0,2,4,6
 
} 

int key(void)  //实现矩阵键盘。返回值为KeyVal，各按键的键值，此键值由用户自己定义。
{
	int KeyVal=0;	 //keyVal为最后返回的键值。
	GPIO_SetBits(GPIOF,GPIO_Pin_0 | GPIO_Pin_2| GPIO_Pin_4| GPIO_Pin_6);//GPIOF0,2,4,6为高,各行输出高电平	
	if((GPIOE->IDR & 0x0055)==0x0000)  //如果，PE0,2,4,6全为0，则没有键按下。此时，返回值为-1.
		return -1;
	else
		{
		delay_ms(10);//延时10ms去抖动。
		if((GPIOE->IDR & 0x0055)==0x0000)  //如果，延时10ms后，PE0,2,4,6又全为0，则刚才引脚的电位变化是抖动产生的.
		return -1;
		}

		
	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0040));	//让PF6,第一行输出1.   
	switch(GPIOE->IDR & 0x0055)		                //对PE0,2,4,6的值进行判断，以输出不同的键值。
	{
		case 0x0001: KeyVal=1;	break;
		case 0x0004: KeyVal=2;	break;
		case 0x0010: KeyVal=3;	break;
		case 0x0040: KeyVal=4;	break;
	}
		while((GPIOE->IDR & 0x0055)!=0x0000)		//松手检测
		delay_us(1);
	
	
	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0010));	//让PF4，第二行输出1.
	switch(GPIOE->IDR & 0x0055)		                //对PE0,2,4,6的值进行判断，以输出不同的键值。
	{
		case 0x0001: KeyVal=5;	break;
		case 0x0004: KeyVal=6;	break;
		case 0x0010: KeyVal=7;	break;
		case 0x0040: KeyVal=8;	break;
	}
		while((GPIOE->IDR & 0x0055)!=0x0000)		//松手检测
		delay_us(1);

	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0004));	//让PF2，第三行输出1.
	switch(GPIOE->IDR & 0x0055)		                //对PE0,2,4,6的值进行判断，以输出不同的键值。
	{
		case 0x0001: KeyVal=9;	break;
		case 0x0004: KeyVal=10;	break;
		case 0x0010: KeyVal=11;	break;
		case 0x0040: KeyVal=12;	break;
	}
		while((GPIOE->IDR & 0x0055)!=0x0000)		//松手检测
		delay_us(1);
		
	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0001));	//让PF0，第四行输出1.
	switch(GPIOE->IDR & 0x0055)		               //对PE0,2,4,6的值进行判断，以输出不同的键值。
	{
		case 0x0001: KeyVal=13;	break;
		case 0x0004: KeyVal=14;	break;
		case 0x0010: KeyVal=15;	break;
		case 0x0040: KeyVal=16;	break;
	}
	while((GPIOE->IDR & 0x0055)!=0x0000)			//松手检测
		delay_us(1);
	return KeyVal;		
}


















