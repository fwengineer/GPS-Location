#include "abba_GPIO.h"

/*
**************************************************
GPIO��ʼ������
����1:�˿������A-E
����2:���ź�Pin0-Pin16
����3:���Ź���ģʽ
		_AIN			ģ������
		_IN_FLOATING	��������
		_IPD			��������
		_IPU			��������
		_Out_OD			��©���
		_Out_PP			�������
		_AF_OD			���ÿ�©���
		_AF_PP			�����������
����5:�˿ڳ�ʼ��ֵ
��ע:���Ź����ٶ�Ĭ��50Mhz
**************************************************
*/

void abba_GPIO_Init(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,uint8_t GPIO_Init_val)
{
	GPIO_InitTypeDef GPIO_temp;
	if(GPIOx == GPIOA)//������Ӧ�˿�ʱ��
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if(GPIOx == GPIOD)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if(GPIOx == GPIOE)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	}
	GPIO_temp.GPIO_Pin  = GPIO_Pin;//��������
	GPIO_temp.GPIO_Mode = GPIO_Mode;//���ù���ģʽ
	GPIO_temp.GPIO_Speed = GPIO_Speed_50MHz;//���ù����ٶ�
	
	GPIO_Init(GPIOx,&GPIO_temp);//���ùٷ����ʼ��
	abba_GPIO_WriteBit(GPIOx,GPIO_Pin,GPIO_Init_val);//��ʼ��д��
}

/*
**************************************************
GPIO�˿�����д��
����1:�˿������A-E
����2:���ź�Pin0-Pin16
����3:�˿�д��ֵ
e.g.  :BSRR��16λ��ַд1�øߵ�ƽ,��16λ��ַдһ�õ͵�ƽ
**************************************************
*/
void abba_GPIO_WriteBit(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t GPIO_Init_val)
{
	if(GPIO_Init_val==1)
	{
		GPIO_Init_val = 0;
	}
	else 
	{
		GPIO_Init_val = 1;
	}
	GPIOx->BSRR=GPIO_Pin<<(GPIO_Init_val*16);//���ó�ʼ��ֵ
}


/*
**************************************************
GPIO�˿ڵ�ƽ��ת
����1:�˿������A-E
����2:���ź�Pin0-Pin16
**************************************************
*/
void abba_GPIO_Toggle(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->ODR ^= GPIO_Pin;
}


/*
**************************************************
GPIO�˿ڵ�ƽ��ȡ
����1:�˿������A-E
����2:���ź�Pin0-Pin16
����ֵ:��ƽ�ߵ�
**************************************************
*/
uint8_t abba_GPIO_ReadBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint8_t bitstatus = 0x00;
	if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
	{
		bitstatus = (uint8_t)Bit_SET;
	}	
	else
	{
		bitstatus = (uint8_t)Bit_RESET;
	}
	return bitstatus;
}



/*********************************************END OF FILE**********************/
