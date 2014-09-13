#include "GSM.h"
extern Datapack uartbuf;

char Postadd[]={"http:// "};//������ո�
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
        UART_SendChar(pack->countlat+'0');
        Dis_fnum(pack->countlat,1,5);
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
	sendChars("{\"longitude\":\"");
	//sendChars("{\"longitude\":\"");
	for(i=0;i<pack->countlon;i++)
	{
                //UART_SendChar(uarttemp)
		UART_SendChar(pack->longitude[i]);
		//UART_SendChar(pack->longitude[i]);
	}
	sendChars("\",\"latitude\":\"");
	//sendChars("\",\"latitude\":\"");
	for(i=0;i<pack->countlat;i++)
	{
                //printf("%c",pack->longitude[i]);
		UART_SendChar(pack->latitude[i]);
		//UART_SendChar(pack->latitude[i]);
	}
	sendChars("\"}");
	//sendChars("\"}");
}
/*
**************************************************
POST���ķ��ͺ���
�����ҵ���ЧЭ��֡ʱ����
עPOST http://hailandev.sinaapp.com/gps/api.php?action=setlocation�ǵ�ͼ�ĵ�ַ,��һ����֮ǰpost���Ե�,�ǵû�����
**************************************************
*/
void Send_PostMessage(Datapack* pack,char* lat1,char* lon1)
{
	int i = 0;
	char num[10];
	Packlen_Tostring(pack,num);
	//latUnit_change(pack);
	//lonUnit_change(pack);
	sendChars("AT+CIPSTART=\"TCP\",\"hailandev.sinaapp.com\",80\r\n");
	sendChars(Host);
	sendChars("\",80\r\n");
	delay_ms(1000);
	sendChars("AT+CIPSEND\r\n");
	delay_ms(1000);
	sendChars("POST ");
	sendChars(Postadd);
	sendChars("HTTP/1.1\r\n");
	sendChars("Referer: http://hailandev.sinaapp.com\r\n");
	sendChars(Host);
	sendChars("\r\n");
	sendChars("Accept:*/*\r\n");
	sendChars("Accept-Language: zh-cn,en-us;q=0.5\r\n");
	sendChars("Content-Type:text/json\r\n");
	sendChars("User-Agent:YunShen1.0\r\n");
	sendChars("Host: hailandev.sinaapp.com\r\n");
	sendChars(Host);
	sendChars("\r\n");
	sendChars("Content-Length: ");
	while(num[i]!='\0')
	{
		UART_SendChar(num[i++]);
	}
	sendChars("\r\n\r\n");
	SendCoordinate(pack);
        
        
        /*sendChars("{\"longitude\":\"");
	for(i=0;i<11;i++)
	{
              
		UART_SendChar(lon1[i]);
	}
	sendChars("\",\"latitude\":\"");
	for(i=0;i<10;i++)
	{
		UART_SendChar(lat1[i]);
	}
	sendChars("\"}");*/
        
        
	sendChars("\r\n\r\n");
	UART_SendChar(0x1a);
	pack->countlat = 0;
	pack->countlon = 0;
	pack->countUTC = 0;
	pack->status = 'V';
        setCharsOLED("OK!",1,6);
        
	
}
/*
**************************************************
GSM��ʼ������
ͷ���þͺ�
**************************************************
*/
void httpInit(void)
{
	sendChars("AT\r\n");
	delay_ms(1000);
	sendChars("ATE1\r\n");
	delay_ms(1000);
	sendChars("AT+CSTT?\r\n");
	delay_ms(1000);
	sendChars("AT+CSTT\r\n");
	delay_ms(1000);
	sendChars("AT+CIICR\r\n");
	delay_ms(1000);
	sendChars("AT+CIFSR\r\n");
	delay_ms(1000);
	
}

/*********************************************END OF FILE**********************/
