#ifndef __GPS_H
#define __GPS_H


#include "Sys.h"
typedef struct 
{
      char UTC[11];//UTCʱ��
      char status;//��ǰ���ݰ���״̬ �������ж��Ƿ�Ϊ��Ч����
      char latitude[10];//γ��
      char lat;//�ϱ�γ
      char longitude[11];//����
      char lon;//������
      u8 countUTC;//��ǰUTC���鳤��
      u8 countlat;//ͬ��(γ��)
      u8 countlon;//ͬ��(����)
}Datapack;
//��ʼ��ʱ�ǵ� �����鳤�ȸ���ȫ��ֵΪ0  statusΪ'V'
uint8_t GPRMC_Analyze(char temp,Datapack* pack);
//void Sendpack(Datapack* pack);
void Dispack(Datapack* pack);


#endif //__GPS_H

