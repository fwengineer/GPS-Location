#include "abba_USART.h"
#include <string.h>
#include <stdio.h>
/*
**************************************************
USART��ʼ������
����1:���ں�USART1-USART2
����2:���ڲ�����
����3:����ģʽ
		TX_mode		ֻ����ģʽ
		RX_mode		ֻ����ģʽ
		TX_RX_mode	���ͺͽ���ģʽ
		(ע:���շ�ʽ��Ϊ�жϽ��� ��ʼ��ʱע���ж����ȼ� �ж������ļ�����ȫ�ֱ���RecChar����һ���ֽڵ���Ϣ)
��ע:Ŀǰֻ������USART1��USART2��ֻ���������������:8λ�շ�,��У��,������,1λֹͣλ
**************************************************
*/
void abba_USART_Init(USART_TypeDef* USARTx,uint32_t USART_BaudRate,uint8_t USART_Mode)
{
	USART_InitTypeDef USART_temp;
		
	if((USART_Mode&RX_Mode)==RX_Mode)
	{
		if(USARTx == USART1)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);//����IO���ü�USART1������ʱ��
			abba_GPIO_Init(GPIOA,GPIO_Pin_10,GPIO_Mode_IPU,0);
		}
		else if(USARTx == USART2)
		{
			abba_GPIO_Init(GPIOA,GPIO_Pin_3,GPIO_Mode_IPU,0);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE); //(ע:USART2����RCC_APB2ʱ����)
		}
		USART_temp.USART_Mode |= USART_Mode_Rx;
		USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);//ʹ��USART�����ж�
	}
	if((USART_Mode&TX_Mode) == TX_Mode)
	{
		if(USARTx == USART1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
			abba_GPIO_Init(GPIOA,GPIO_Pin_9,GPIO_Mode_AF_PP,0);
		}
		else if(USARTx == USART2)
		{
			abba_GPIO_Init(GPIOA,GPIO_Pin_2,GPIO_Mode_AF_PP,0);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
		}
		USART_temp.USART_Mode |= USART_Mode_Tx;
	}

	USART_temp.USART_BaudRate = USART_BaudRate;
	USART_temp.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_temp.USART_WordLength = USART_WordLength_8b;
	USART_temp.USART_StopBits = USART_StopBits_1;
	USART_temp.USART_Parity = USART_Parity_No;
	USART_Init(USARTx,&USART_temp);
	USART_Cmd(USARTx, ENABLE);
}
/*
**************************************************
USART_DMA����ģʽ��ʼ������
����1:���ں�USART1-USART2
����2:���͵����ݵ�ַ
����3:�������ݵĳ���
����4:����ģʽ
		_Normal ���η���ģʽ
		_Circular ��������ģʽ
����5:DMA���ȼ�
		_VeryHigh
		_High
		_Medium
		_Low
		(ע����������ȼ�ָ����ͬһDMA�µ����ȼ�,USART1-USART3����DMA1)
��ע:���ڶ�DMA�Ĳ���Ϥ��ʱûдDMA�ɼ�ģʽ,����ģʽ�������ݵ�λΪһ���ֽ�
ʹ�÷���:�����ó�ʼ������� USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);��������DMA����
**************************************************
*/
void abba_USART_DMA_Init(USART_TypeDef* USARTx,uint8_t Send[],uint32_t SENDBUFF_SIZE,uint32_t DMA_Mode,uint32_t DMA_Priority)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		   
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Send;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	DMA_InitStructure.DMA_Mode = DMA_Mode;//DMA_Mode_Circular;	 
	DMA_InitStructure.DMA_Priority = DMA_Priority;  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	if(USARTx == USART1)
	{
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(USART1) + 0x04;
		DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
		DMA_Cmd (DMA1_Channel4,ENABLE);		
	}
	else if(USARTx == USART2)
	{
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(USART2) + 0x04;
		DMA_Init(DMA1_Channel7, &DMA_InitStructure); 	   
		DMA_Cmd (DMA1_Channel7,ENABLE);
	}
}
/*
**************************************************
USART�����ַ�������
����1:���ں�USART1-USART2
����2:�跢�͵��ַ���
**************************************************
*/
void abba_USART_SendString(USART_TypeDef* USARTx,char *s)
{
	while(*s != '\0')
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		USARTx->DR = (*s & (uint16_t)0x01FF);
		s++;
	}
	
}

/*
**************************************************
USART���͵��ַ��ַ�����
����1:���ں�USART1-USART2
����2:�跢�͵��ַ�
**************************************************
*/

void abba_USART_SendChar(USART_TypeDef* USARTx,char s)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	USARTx->DR = (s & (uint16_t)0x01FF);
}


int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}


/*********************************************END OF FILE**********************/
