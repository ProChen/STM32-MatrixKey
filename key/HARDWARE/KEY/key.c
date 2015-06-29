#include "key.h"
#include "delay.h" 

void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOE,GPIOFʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; //4�ж�Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//�������
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOF0,2,4,6
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; //4�ж�Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //��ͨ��ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE0,2,4,6
 
} 

int key(void)  //ʵ�־�����̡�����ֵΪKeyVal���������ļ�ֵ���˼�ֵ���û��Լ����塣
{
	int KeyVal=0;	 //keyValΪ��󷵻صļ�ֵ��
	GPIO_SetBits(GPIOF,GPIO_Pin_0 | GPIO_Pin_2| GPIO_Pin_4| GPIO_Pin_6);//GPIOF0,2,4,6Ϊ��,��������ߵ�ƽ	
	if((GPIOE->IDR & 0x0055)==0x0000)  //�����PE0,2,4,6ȫΪ0����û�м����¡���ʱ������ֵΪ-1.
		return -1;
	else
		{
		delay_ms(10);//��ʱ10msȥ������
		if((GPIOE->IDR & 0x0055)==0x0000)  //�������ʱ10ms��PE0,2,4,6��ȫΪ0����ղ����ŵĵ�λ�仯�Ƕ���������.
		return -1;
		}

		
	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0040));	//��PF6,��һ�����1.   
	switch(GPIOE->IDR & 0x0055)		                //��PE0,2,4,6��ֵ�����жϣ��������ͬ�ļ�ֵ��
	{
		case 0x0001: KeyVal=1;	break;
		case 0x0004: KeyVal=2;	break;
		case 0x0010: KeyVal=3;	break;
		case 0x0040: KeyVal=4;	break;
	}
		while((GPIOE->IDR & 0x0055)!=0x0000)		//���ּ��
		delay_us(1);
	
	
	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0010));	//��PF4���ڶ������1.
	switch(GPIOE->IDR & 0x0055)		                //��PE0,2,4,6��ֵ�����жϣ��������ͬ�ļ�ֵ��
	{
		case 0x0001: KeyVal=5;	break;
		case 0x0004: KeyVal=6;	break;
		case 0x0010: KeyVal=7;	break;
		case 0x0040: KeyVal=8;	break;
	}
		while((GPIOE->IDR & 0x0055)!=0x0000)		//���ּ��
		delay_us(1);

	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0004));	//��PF2�����������1.
	switch(GPIOE->IDR & 0x0055)		                //��PE0,2,4,6��ֵ�����жϣ��������ͬ�ļ�ֵ��
	{
		case 0x0001: KeyVal=9;	break;
		case 0x0004: KeyVal=10;	break;
		case 0x0010: KeyVal=11;	break;
		case 0x0040: KeyVal=12;	break;
	}
		while((GPIOE->IDR & 0x0055)!=0x0000)		//���ּ��
		delay_us(1);
		
	GPIO_Write(GPIOF,(GPIOF->ODR & 0xff00|0x0001));	//��PF0�����������1.
	switch(GPIOE->IDR & 0x0055)		               //��PE0,2,4,6��ֵ�����жϣ��������ͬ�ļ�ֵ��
	{
		case 0x0001: KeyVal=13;	break;
		case 0x0004: KeyVal=14;	break;
		case 0x0010: KeyVal=15;	break;
		case 0x0040: KeyVal=16;	break;
	}
	while((GPIOE->IDR & 0x0055)!=0x0000)			//���ּ��
		delay_us(1);
	return KeyVal;		
}


















