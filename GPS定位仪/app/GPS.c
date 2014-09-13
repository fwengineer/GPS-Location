#include "GPS.h"

/*
**************************************************
Э��֡���Һ���
�ڴ��ڽ����ж�����ʱ���ַ��Ӹ���
���ҵ���ЧЭ��֡ʱ�᷵��1,���򷵻�0
���ﵱ�ҵ���Ч�����ǻ�ֹͣUSART1�Ľ����ж�,һ������������1ʱ�Ϳ��Ե���GSM.h���Send_PostMessage();
**************************************************
*/

uint8_t GPRMC_Analyze(char temp,Datapack* pack)
{
	static uint8_t status = 0;
	switch(status)
	{
		case 0:
			if(temp=='G')
			{
				status = 1;
			}
			break;
		case 1:
			if(temp == 'P')
			{
				status = 2;
			}
			else
			{
				status = 0;
			}
			break;
		case 2:
			if(temp == 'R')
			{
				status = 3;
			}
			else 
			{
				status = 0;
			}
			break;
		case 3:
			if(temp == 'M')
			{
				status = 4;
			}
			else 
			{
				status = 0;
			}
			break;
		case 4:
			if(temp == 'C')
			{
				status = 5;
			}
			else 
			{
				status = 0;
			}
			break;
		case 5:
			if(temp==',')
			{
				status = 6;
			}
			else
			{
				status = 0;
			}
			break;
		case 6:
			if(temp == ',')
			{
				status = 7;
			}
			else 
			{
				if( !((temp>='0' && temp <='9') || temp =='.'))
				{
					status = 0;
					pack->countlat = 0;
					pack->countlon = 0;
					pack->countUTC = 0;
					pack->status = 'V';
				}
				else
				{
					pack->UTC[pack->countUTC++] = temp;
				}
			}
			break;
		case 7:
			if(temp == ',')
			{
				status = 8;
			}
			else
			{
				pack->status = temp;
			}
			break;
		case 8:
			if(temp == ',')
			{
				status = 9;
			}
			else 
			{
				if( !((temp>='0' && temp <='9') || temp =='.'))
				{
					status = 0;
					pack->countlat = 0;
					pack->countlon = 0;
					pack->countUTC = 0;
					pack->status = 'V';
				}
				else
				{
					pack->latitude[pack->countlat++] = temp;
				}
			}
			break;
		case 9:
			if(temp == ',')
			{
				status = 10;
			}
			else
			{
				pack->lat = temp;
			}
			break;
		case 10:
			if(temp == ',')
			{
				status = 11;
			}
			else 
			{
				if( !((temp>='0' && temp <='9') || temp =='.'))
				{
					status = 0;
					pack->countlat = 0;
					pack->countlon = 0;
					pack->countUTC = 0;
					pack->status = 'V';
				}
				else
				{
					pack->longitude[pack->countlon++] = temp;
				}
			}
			break;
		case 11:
			if(temp == ',')
			{
				status = 0;
				//USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
                                sim();
				return 1;
			}
			else
			{
				pack->lon = temp;
			}
			break;
	}
	return 0;
}
/*
**************************************************
���ڵ����õ�  ����Ҫ���ӵ�
**************************************************
*/

void Dispack(Datapack* pack)
{
	uint8_t i;
	
        if(pack->status=='A')
	{
          //printf("��λ\n");  
            addrOLED(1,3);
            setCharOLED(pack->lat);
            /*for(i=0;i<pack->countlat-5;i++)
            {
              setCharOLED(pack->latitude[i]);
            }
            
            addrOLED(1,4);
            for(i=0;i<pack->countlon;i++)
            {
                    setCharOLED(pack->longitude[i]);
            }*/
            //setCharOLED(pack->lon);
	}
}

void Sendpack(Datapack* pack)
{
	uint8_t i;
	if(pack->status=='V')
	{
	    printf("��λ��Ч\n");
	}
	else 
	{
              printf("ʱ��\t");
              for(i=0;i<pack->countUTC;i++)
              {
                      printf("%c",pack->UTC[i]);
              }
              printf("\nγ��\t");
              for(i=0;i<pack->countlat;i++)
              {
                      printf("%c",pack->latitude[i]);
              }
              printf("%c",pack->lat);
              printf("\n����\t");
              for(i=0;i<pack->countlon;i++)
              {
                      printf("%c",pack->longitude[i]);
              }
              printf("%c\n",pack->lon);
	}
	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

/*********************************************END OF FILE**********************/
