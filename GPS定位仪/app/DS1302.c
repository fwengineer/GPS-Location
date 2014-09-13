#include "ds1302.h"

void ds_rdinit(void);
void ds_wrinit(void);


void DSWriteDat(u8 addr, u8 d)
{
  u8 i;
  RST_SET;	
  delay_us(5);
  //д��Ŀ���ַ��addr
  addr = addr & 0xFE;     //���λ����
  for (i = 0; i < 8; i ++) 
  { 
          if (addr & 0x01) 
          {
              IO_SET;
          }
          else 
          {
              IO_CLR;
          }
          delay_us(5);
          SCK_SET;
          delay_us(5);
          SCK_CLR;
          addr = addr >> 1;
  }
  delay_us(5);
  //д�����ݣ�d
  for (i = 0; i < 8; i ++) 
  {
          if (d & 0x01) 
          {
                  IO_SET;
          }
          else 
          {
                  IO_CLR;
          }
          delay_us(5);
          SCK_SET;
          delay_us(5);
          SCK_CLR;
          d = d >> 1;
  }
  delay_us(5);
  RST_CLR;	//ֹͣDS1302����
  delay_us(5);
}
/*------------------------------------------------
��DS1302����һ�ֽ�����
------------------------------------------------*/

u8 DSReadDat(u8 addr) 
{
    u8 i;
    u8 temp;
    RST_SET;	
    delay_us(5);
    //д��Ŀ���ַ��addr
    addr = addr | 0x01;//���λ�ø�
    for (i = 0; i < 8; i ++) 
    {
            if (addr & 0x01) 
            {
                    IO_SET;
            }
            else 
            {
                    IO_CLR;
            }
            delay_us(5);
            SCK_SET;
            delay_us(5);
            SCK_CLR;
            addr = addr >> 1;
    }
    delay_us(5);
    //������ݣ�temp
    ds_rdinit();
    for (i = 0; i < 8; i ++) 
    {
            temp = temp >> 1;
            if (IO_R) 
            {
                    temp |= 0x80;
            }
            else 
            {
                    temp &= 0x7F;
            }
            delay_us(5);
            SCK_SET;
            delay_us(5);
            SCK_CLR;
    }
    delay_us(5);
    ds_wrinit();
    RST_CLR;	//ֹͣDS1302����
    delay_us(5);
    return temp;
}

/*------------------------------------------------
��DS1302д��ʱ������
------------------------------------------------*/
void DSWrite(time *buf) 
{
    buf->year=buf->year%10+(u16)(buf->year/10)*16;
    buf->mouth=buf->mouth%10+(u8)(buf->mouth/10)*16;
    buf->day=buf->day%10+(u8)(buf->day/10)*16;
    buf->hour=buf->hour%10+(u8)(buf->hour/10)*16;
    buf->min=buf->min%10+(u8)(buf->min/10)*16;
    buf->sec=buf->sec%10+(u8)(buf->sec/10)*16;

    DSWriteDat(ds1302_control_add,0x00);			//�ر�д���� 
    DSWriteDat(ds1302_sec_add,0x80);				//��ͣ 
    //DSWriteDat(ds1302_charger_add,0xa9);			//������ 
    DSWriteDat(ds1302_year_add,buf->year);		//�� 
    DSWriteDat(ds1302_month_add,buf->mouth);	//�� 
    DSWriteDat(ds1302_date_add,buf->day);		//�� 
    //DSWriteDat(ds1302_day_add,timebuf[7]);		//�� 
    DSWriteDat(ds1302_hr_add,buf->hour);		//ʱ 
    DSWriteDat(ds1302_min_add,buf->min);		//��
    DSWriteDat(ds1302_sec_add,buf->sec);		//��
    //DSWriteDat(ds1302_day_add,timebuf[7]);		//�� 
    DSWriteDat(ds1302_control_add,0x80);			//��д���� 
}

/*------------------------------------------------
��DS1302����ʱ������
------------------------------------------------*/
void DSRead(time *buf)  
{ 
  delay_ms(10);buf->year=DSReadDat(ds1302_year_add);		//�� 
  delay_ms(10);buf->mouth=DSReadDat(ds1302_month_add);		//�� 
  delay_ms(10);buf->day=DSReadDat(ds1302_date_add);		//�� 
  delay_ms(10);buf->hour=DSReadDat(ds1302_hr_add);		//ʱ 
  delay_ms(10);buf->min=DSReadDat(ds1302_min_add);		//�� 
  delay_ms(10);buf->sec=(DSReadDat(ds1302_sec_add))&0x7F;//�� 
  //time_buf[6]=DSReadDat(ds1302_day_add);		//�� 
  
  buf->year=buf -> year%16 +(u16)(buf->year/16)*10;
  buf->mouth=buf-> mouth%16+(u8)(buf->mouth/16)*10;
  buf->day=buf  -> day%16  +(u8)(buf->day/16)*10;
  buf->hour=buf -> hour%16 +(u8)(buf->hour/16)*10;
  buf->min=buf  -> min%16  +(u8)(buf->min/16)*10;
  buf->sec=buf  -> sec%16  +(u8)(buf->sec/16)*10;
}

void ds_rdinit(void)
{
   GPIOB->DDR &= ~(1<<1);//����ģʽ
   GPIOB->CR1 |=  (1<<1);//��������
   GPIOB->CR2 &=~(1<<1);
}
void ds_wrinit(void)
{
  GPIOB->DDR  |=  (1<<1);
  GPIOB->CR1  |=  (1<<1);
}
/*------------------------------------------------
DS1302��ʼ��
------------------------------------------------*/
void Ds1302_Init(void)
{
  GPIOB->DDR  |=  (5<<0);
  GPIOB->CR1  |=  (5<<0);
  ds_wrinit();
  RST_CLR;			//RST���õ�
  delay_us(5);
  SCK_CLR;			//SCK���õ�
  delay_us(5);
  DSWriteDat(ds1302_sec_add,0x00);				 
}
