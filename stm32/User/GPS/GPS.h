#ifndef __GPS_H
#define __GPS_H


#include "stm32f10x.h"
#include "abba_USART.h"
//#include "GSM.h"
typedef struct 
{
	char UTC[11];//UTCʱ��
	char status;//��ǰ���ݰ���״̬ �������ж��Ƿ�Ϊ��Ч����
	char latitude[10];//γ��
	char lat;//�ϱ�γ
	char longitude[11];//����
	char lon;//������
	uint8_t countUTC;//��ǰUTC���鳤��
	uint8_t countlat;//ͬ��(γ��)
	uint8_t countlon;//ͬ��(����)
}Datapack;
//��ʼ��ʱ�ǵ� �����鳤�ȸ���ȫ��ֵΪ0  statusΪ'V'
uint8_t GPRMC_Analyze(char temp,Datapack* pack);
void Sendpack(Datapack* pack);


#endif //__GPS_H

