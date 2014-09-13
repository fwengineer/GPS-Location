#include "GSM.h"
#include "GPS.h"
extern Datapack Data;

char Postadd[]={"http:// "};//�����һ���ո�
char Host[] ={"http://"}; //����http://
static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

void latUnit_change(Datapack* pack)
{
	int i,flag = 0,num = 0;
	double lat = 0,temp = 0,pointtemp = 0.1;
	num = (pack->latitude[0] - '0')*10;
	num += (pack->latitude[1] - '0');
	for(i=2;i<pack->countlat;i++)
	{
		if(pack->latitude[i]=='.')
		{
			flag = 1;
			continue;
		}
		if(flag)
		{
			temp = temp + (pack->latitude[i]-'0')*pointtemp;
			pointtemp *= 0.1;
		}
		else
		{
			lat = lat*10 + pack->latitude[i]-'0';
		}
		
	}
	lat += temp;
	lat /= 60;
	lat += num;
	num = (int)lat;
	lat -= num;
	pack->latitude[0] = num/10 + '0';
	pack->latitude[1] = num%10 + '0';
	pack->latitude[2] = '.';
	for(i=3;i<pack->countlat;i++)
	{
		lat *= 10;
		num = (int)(lat);
		lat -= num;
		pack->latitude[i] = num+'0';
	}
}
void lonUnit_change(Datapack* pack)
{
	int i,flag = 0,num = 0;
	double lon = 0,temp = 0,pointtemp = 0.1;
	num = (pack->longitude[0] - '0')*100;
	num += (pack->longitude[1] - '0')*10;
	num += (pack->longitude[2] - '0');
	for(i=3;i<pack->countlon;i++)
	{
		if(pack->longitude[i]=='.')
		{
			flag = 1;
			continue;
		}
		if(flag)
		{
			temp = temp + (pack->longitude[i]-'0')*pointtemp;
			pointtemp *= 0.1;
		}
		else
		{
			lon = lon*10 + pack->longitude[i]-'0';
		}
		
	}
	lon += temp;
	lon /= 60;
	lon += num;
	num = (int)lon;
	lon -= num;
	pack->longitude[0] = num/100 + '0';
	pack->longitude[1] = num/10/10 + '0';
	pack->longitude[2] = num%10 + '0';
	pack->longitude[3] = '.';
	for(i=4;i<pack->countlon;i++)
	{
		lon *= 10;
		num = (int)(lon);
		lon -= num;
		pack->longitude[i] = num+'0';
	}
}

/*
**************************************************
�������ݰ�����ת������
����һ��http���Ӻ����������ݳ��Ȳ�ת��Ϊ�ַ�����
**************************************************
*/
static void Packlen_Tostring(Datapack* pack,char* str)
{
	uint8_t num = 0,i = 0,len;
	char temp;
	num = pack->countlat + pack->countlon + strlen("longitude:latitude:,")+10;//+10Ϊ8��'"',��'{','}'
	while(num!=0)
	{
		str[i++] = num%10+'0';
		num = num/10;
	}
	str[i]='\0';
	len = strlen(str);
	for(i=0;i<len/2;i++)
	{
		temp  = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}
}
/*
**************************************************
��γ�ȷ��ͺ���
**************************************************
*/
static void SendCoordinate(Datapack* pack)//ע���Ǹ��������� ���ҵİ���������һ��ҪUSART1,����ԭ���Ҳ���
{
	int i;
	abba_USART_SendString(USART2,"{\"longitude\":\"");
	abba_USART_SendString(USART1,"{\"longitude\":\"");
	for(i=0;i<pack->countlon;i++)
	{
		abba_USART_SendChar(USART2,pack->longitude[i]);
		abba_USART_SendChar(USART1,pack->longitude[i]);
	}
	abba_USART_SendString(USART2,"\",\"latitude\":\"");
	abba_USART_SendString(USART1,"\",\"latitude\":\"");
	for(i=0;i<pack->countlat;i++)
	{
		abba_USART_SendChar(USART2,pack->latitude[i]);
		abba_USART_SendChar(USART1,pack->latitude[i]);
	}
	abba_USART_SendString(USART2,"\"}");
	abba_USART_SendString(USART1,"\"}");
}
/*
**************************************************
POST���ķ��ͺ���
�����ҵ���ЧЭ��֡ʱ����
עPOST http://hailandev.sinaapp.com/gps/api.php?action=setlocation�ǵ�ͼ�ĵ�ַ,��һ����֮ǰpost���Ե�,�ǵû�����
**************************************************
*/
void Send_PostMessage(Datapack* pack)
{
	int i = 0;
	char num[10];
	Packlen_Tostring(pack,num);
	latUnit_change(pack);
	lonUnit_change(pack);
	abba_USART_SendString(USART2,"AT+CIPSTART=\"TCP\",\"");
	abba_USART_SendString(USART2,Host);
	abba_USART_SendString(USART2,"\",80\r\n");
	Delay(0x00ffffff);
	abba_USART_SendString(USART2,"AT+CIPSEND\r\n");
	Delay(0x004fffff);
	abba_USART_SendString(USART2,"POST ");
	abba_USART_SendString(USART2,Postadd);
	abba_USART_SendString(USART2," HTTP/1.1\r\n");
	abba_USART_SendString(USART2,"Referer: ");
	abba_USART_SendString(USART2,Host);
	abba_USART_SendString(USART2,"\r\n");
	abba_USART_SendString(USART2,"Accept:*/*\r\n");
	abba_USART_SendString(USART2,"Accept-Language: zh-cn,en-us;q=0.5\r\n");
	abba_USART_SendString(USART2,"Content-Type:text/json\r\n");
	abba_USART_SendString(USART2,"User-Agent:YunShen1.0\r\n");
	abba_USART_SendString(USART2,"Host: ");
	abba_USART_SendString(USART2,Host);
	abba_USART_SendString(USART2,"\r\n");
	abba_USART_SendString(USART2,"Content-Length: ");
	while(num[i]!='\0')
	{
		abba_USART_SendChar(USART2,num[i++]);
	}
	abba_USART_SendString(USART2,"\r\n\r\n");
	SendCoordinate(pack);
	abba_USART_SendString(USART2,"\r\n\r\n");
	abba_USART_SendChar(USART2,0x1a);
	pack->countlat = 0;
	pack->countlon = 0;
	pack->countUTC = 0;
	pack->status = 'V';
	
}
/*
**************************************************
GSM��ʼ������
ͷ���þͺ�
**************************************************
*/
void httpInit(void)
{
	abba_USART_SendString(USART2,"AT\r\n");
	Delay(0x01fffff);
	abba_USART_SendString(USART2,"ATE1\r\n");
	Delay(0x00ffffff);
	abba_USART_SendString(USART2,"AT+CSTT?\r\n");
	Delay(0x00ffffff);
	abba_USART_SendString(USART2,"AT+CSTT\r\n");
	Delay(0x00ffffff);
	abba_USART_SendString(USART2,"AT+CIICR\r\n");
	Delay(0x00ffffff);
	abba_USART_SendString(USART2,"AT+CIFSR\r\n");
	Delay(0x00ffffff);
	
}

/*********************************************END OF FILE**********************/
