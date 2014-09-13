#include "abba_ISR.h"
char RecChar1,RecChar2;
extern Datapack Data;
extern uint8_t Rec_flag;
/*
**************************************************
Ƕ���ж����ó�ʼ��
����1:���ȼ����
		NVIC_PriorityGroup_0 	��ռ���ȼ�0 �����ȼ�4(λ)
		NVIC_PriorityGroup_1	��ռ���ȼ�1 �����ȼ�3(λ)
		NVIC_PriorityGroup_2	��ռ���ȼ�2 �����ȼ�2(λ)
		NVIC_PriorityGroup_3	��ռ���ȼ�3 �����ȼ�1(λ)
		NVIC_PriorityGroup_4	��ռ���ȼ�4 �����ȼ�0(λ)
����2:�жϱ�� ͷ�ļ�"stm32f10x.h"�б�ŵĶ���
����3:��ռ���ȼ�,���ݲ���һ�����õ�λ���޶����ֵ0-15
����4:�����ȼ�,���ݲ���һ�����õ�λ���޶����ֵ0-15
**************************************************
*/
void NVIC_Configuration(uint32_t NVIC_PriorityGroup,uint8_t IRQn_Channel,uint8_t IRQChannelPreemptionPriority,uint8_t IRQChannelSubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  
  NVIC_InitStructure.NVIC_IRQChannel = IRQn_Channel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IRQChannelPreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = IRQChannelSubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
**************************************************
�ⲿ�жϳ�ʼ��
����1:GPIO�ж�Դ���  	GPIO_PortSourceGPIOA-G       
����2:�ж���·    		GPIO_PinSource0-15 
����3:�ⲿ�ж�ģʽ
			EXTI_Mode_Event 		�¼�����
			EXTI_Mode_Interrupte	�ж�����
����4:������ʽ
			EXTI_Trigger_Falling			�½��ش���
			EXTI_Trigger_Rising				�����ش���
			EXTI_Trigger_Rising_Falling		�����ػ��½��ش���
**************************************************
*/
void abba_EXIT_Init(uint8_t GPIO_PortSource,uint8_t GPIO_PinSource,EXTIMode_TypeDef EXTI_Mode,EXTITrigger_TypeDef EXTI_Trigger)
{
	uint32_t EXTI_Line;
	uint8_t i,GPIO_Pin_temp = GPIO_PinSource0;
	EXTI_InitTypeDef EXTI_temp;

	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
	EXTI_Line = EXTI_Line0;
	for(i=0;i<16;i++)
	{
		if(GPIO_PinSource == GPIO_Pin_temp)
		{
			break;
		}
		GPIO_Pin_temp++;
		EXTI_Line += EXTI_Line;
	}
	
	EXTI_temp.EXTI_Line = EXTI_Line;
	EXTI_temp.EXTI_Mode = EXTI_Mode;
	EXTI_temp.EXTI_Trigger = EXTI_Trigger;
	EXTI_temp.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_temp);
	
											
	
}


/*
**************************************************
�ж������������ļ� "startup_stm32f10x_hd.s" �����ҵ�
**************************************************
*/

/*
**************************************************
�ⲿ�жϺ�������
EXTI0_IRQHandler - EXTI15_10_IRQHandler
�жϺ�����ɺ�,��������������־λ
void EXTI_ClearFlag(u32 EXTI_Line));
EXTI->PR = EXTI_Line;
**************************************************
*/

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void)
{
}
void EXTI2_IRQHandler(void)
{
}
void EXTI3_IRQHandler(void)
{
}
void EXTI4_IRQHandler(void)
{
}
void EXTI9_5IRQHandler(void)
{
}

void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line13);
}


void USART1_IRQHandler()
{
	RecChar1 = USART_ReceiveData(USART1);
	Rec_flag = GPRMC_Analyze(RecChar1,&Data);
}

void USART2_IRQHandler()
{
	RecChar2 = USART_ReceiveData(USART2);
	USART_SendData(USART1,RecChar2);
}
extern uint8_t flag_1s;



void TIM2_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM3_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM4_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM5_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM5 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM5 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM6_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM6 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM7_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM7 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM7 , TIM_FLAG_Update);  		 
	}		 	
}



/*********************************************END OF FILE**********************/
