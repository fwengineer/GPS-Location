#include "USART.h"

/**************************
函数功能：初始化UART
输入参数：SYS_Clk:系统时钟（2,4,8,16）
         baud：   波特率
输出参数：无
备    注：无
***************************/
void UART_Init(u32 baud)
{   
    u16 UART_Temp;
  
    UART_IOConfig();//UART IO引脚初始化 
  
    UART1->CR2 = 0;// 禁止UART发送和接收
    UART1->CR1 = 0;// b5 = 0,允许UART  b2 = 0,禁止校验                                                  
    UART1->CR3 = 0;// b5,b4 = 00,1个停止位
    
    UART3->CR2 = 0;// 禁止UART发送和接收
    UART3->CR1 = 0;// b5 = 0,允许UART  b2 = 0,禁止校验                                                  
    UART3->CR3 = 0;// b5,b4 = 00,1个停止位
                            
/************************************************** 
    设置波特率，必须注意以下几点：
    (1) 必须先写BRR2
    (2) BRR1存放的是分频系数的第11位到第4位，
    (3) BRR2存放的是分频系数的第15位到第12位，和第3位到第0位
    例如对于波特率位9600时，分频系数=2000000/9600=208
    对应的十六进制数为00D0，BBR1=0D,BBR2=00
*************************************************/ 
    
    UART_Temp = SYS_Clk/baud;
    
    UART1->BRR2 = (u8)((UART_Temp&0x000F)|((UART_Temp&0xF000)>>8));
    UART1->BRR1 = (u8)((UART_Temp&0x0FF0)>>4);
                                                 
                                    
    UART1->CR2 = 0x2C; // b3 = 1,允许发送
                       // b2 = 1,允许接收
                       // b5 = 1,允许产生接收中断 
    
    UART3->BRR2 = (u8)((UART_Temp&0x000F)|((UART_Temp&0xF000)>>8));
    UART3->BRR1 = (u8)((UART_Temp&0x0FF0)>>4);
                                                 
                                    
    UART3->CR2 = 0x2C; // b3 = 1,允许发送
                       // b2 = 1,允许接收
                       // b5 = 1,允许产生接收中断 
}

/**************************************
函数功能：从UART3发送一个字符
输入参数：ch -- 要发送的字符
输出参数：无
备    注：无
***************************************/
void UART_SendChar(u8 ch)
{
     while((UART1->SR & 0x80) == 0x00);  // 若发送寄存器不空，则等待
     UART1->DR = ch;                     // 将要发送的字符送到数据寄存器  
}
u8 UART_GetChar(void)
{
     while((UART1->SR & 0x20) == 0x00);  // 若发送寄存器不空，则等待
     return UART1->DR;                     // 将要发送的字符送到数据寄存器  
}
void UART3_SendChar(u8 ch)
{
     while((UART3->SR & 0x80) == 0x00);  // 若发送寄存器不空，则等待
     UART3->DR = ch;                     // 将要发送的字符送到数据寄存器  
}
u8 UART3_GetChar(void)
{
     while((UART3->SR & 0x20) == 0x00);  // 若发送寄存器不空，则等待
     return UART3->DR;                     // 将要发送的字符送到数据寄存器  
}
/***********************************
函数功能：UART IO口初始化
输入参数：无
输出参数：无
备   注：ＩＯ在输出模式下，可通过ＣＲ２寄存器
         控制输出速率
***********************************/
void UART_IOConfig(void)
{ 
    TXPort->DDR |= TXPin;//输出模式
    TXPort->CR1 |= TXPin;//推挽输出   
    
    RXPort->DDR &=~RXPin;//输入模式
    RXPort->CR1 &=~RXPin;//浮空输入
    
    TX3Port->DDR |= TX3Pin;//输出模式
    TX3Port->CR1 |= TX3Pin;//推挽输出   
    
    RX3Port->DDR &=~RX3Pin;//输入模式
    RX3Port->CR1 &=~RX3Pin;//浮空输入
}

int fputc(int ch,FILE *f)
{
   UART_SendChar((u8)ch);
   //while(UART2_GetFlagStatus(UART2_FLAG_TXE)==RESET);
   return ch;
}

void sendChars(u8 *disbuf)
{
    while(*disbuf!='\0')
    {
            UART_SendChar(*disbuf);
            *(disbuf++);
    }
}
 









