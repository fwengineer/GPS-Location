#include "EXIT.h"

/***********************
�������ܣ��ⲿ�жϳ�ʼ��
�����������
�����������
��    ע��PA2
***********************/
void EXTI_Init(void)
{
    EXIT_GPIO->DDR &=~EXIT_PIN;//����ģʽ
    EXIT_GPIO->CR1 |= EXIT_PIN;//��������
    EXIT_GPIO->CR2 |= EXIT_PIN;//ʹ���ⲿ�ж�
     
    EXTI->CR1  |= BIT(1);//PA�½��ش���  
    
    asm("rim");    //�����ж�
}


#pragma   vector = EXTI0_PA_vector
__interrupt  void  EXTI0_PA_IRQHandler(void)
{
    asm("sim");    //�����ж�
      //PA2�ж�
    if(!(GPIOA->IDR&0X04))
    {    
          LED_ON();
    }
    
    asm("rim");    //�����ж�
}


#pragma vector = TIM4_Updata_vector
__interrupt void TIM4_Updata_IRQHandler(void)
{
    sim();//�����ж�

    
    TIM4->SR1 &=~BIT(0);//���־λ
    rim();//�����ж�
}

