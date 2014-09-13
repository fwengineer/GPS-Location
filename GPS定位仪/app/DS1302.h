
#ifndef __DS1302_H__
#define __DS1302_H__
#include "Sys.h"   

/*sbit SCK=D2;		
sbit SDA=D3;		
sbit RST=D4;*/
//��λ��
#define RST_CLR	PBO(0,0)//��ƽ�õ�
#define RST_SET	PBO(0,1)//��ƽ�ø�


//˫������
#define IO_CLR	PBO(1,0)//��ƽ�õ�
#define IO_SET	PBO(1,1)//��ƽ�ø�
#define IO_R	PB(1)  //��ƽ��ȡ


//ʱ���ź�
#define SCK_CLR	PBO(2,0)//ʱ���ź�
#define SCK_SET	PBO(2,1)//��ƽ�ø�


#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

typedef struct 
{
  u16 year;
  u8 mouth;
  u8 day;
  u8 hour;
  u8 min;
  u8 sec;
}time;

void DSWrite(time *buf); 
void DSRead(time *buf);  
void Ds1302_Init(void);

#endif
