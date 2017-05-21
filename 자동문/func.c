#include "func.h"
#include "usart.h"

volatile int head = 0;
volatile char Input[3];

void ActionMotor(int angle)
{
	int i;

	SetPosition(angle);

	for(i = 0; i<9; i++)
	{
		USART1_Tx(Move[i]);
	}
}

void ActionSpeed(int aspd)
{
	int i;

	SetSpeed(aspd);
	
	for(i = 0; i<9; i++)
	{
		USART1_Tx(Speed[i]);
	}
}

int AscToInt()
{
	int i;
	int cnt = 0;
	int tmp;
	int ret = 0;

	for(i = 2; i>=0; i--)
	{
		if( Input[i] != 0 )
		{
			tmp = Input[i];
			if((tmp>='0')&&(tmp<='9'))	tmp = tmp-'0';
			else 						tmp = 0;

			switch(cnt)
			{
				case 0: ret = ret + tmp;		break;
				case 1: ret = ret + tmp*10;		break;
				case 2: ret = ret + tmp*100;	break;
				default: break;
			}

			cnt++;
		}
	}
	if(ret>300)	ret = 300;
	if(ret < 0) ret = 0;

	init();

	return ret;
}
int AscToHex()
{
	int i;
	int cnt = 0;
	int tmp;
	int ret = 0;

	for(i = 2; i>=0; i--)
	{
		if( Input[i] != 0 )
		{
			tmp = Input[i];

			if((tmp>='0')&&(tmp<='9'))		tmp = tmp-'0';
			else if((tmp>='a')&&(tmp<='f'))	tmp = tmp-'a'+10;
			else if((tmp>='A')&&(tmp<='F'))	tmp = tmp-'A'+10;
			else							tmp = 0;

			//ret += tmp<<(4*cnt);
			switch(cnt)
			{
				case 0: ret = ret + tmp;		break;
				case 1: ret = ret + (tmp<<4);	break;
				case 2: ret = ret + (tmp<<8);	break;
				default: break;
			}

			cnt++;
		}
	}

	if(ret>0x3FF)	ret = 0x3FF;
	if(ret < 0) 	ret = 0;

	init();

	return ret;
}

void SetPosition(int apos)
{
	long pos;

	pos = (long)apos*0x3FF;
	pos = pos/300;

	// 명령어 설정
	Move[6] = pos&0x00FF;
	Move[7] = (pos&0xFF00)>>8;
	Move[8] = (unsigned char)(~(0x01 + 0x05 + 0x03 + 0x1E  +Move[6] +Move[7]));
}

void SetSpeed(int aspd)
{
	Speed[6] = aspd&0x00FF;
	Speed[7] = (aspd&0xFF00)>>8;
	Speed[8] = (unsigned char)(~(0x01 + 0x05 + 0x03 + 0x1E  +Speed[6] +Speed[7]));
}


void SendDeg_ToPc()
{
	long Deg;

	Deg = Move[6] + (Move[7]<<8);
	Deg = Deg*300;
	Deg = Deg/0x3FF;

	USART0_Tx('D');
	USART0_Tx(':');		
	USART0_Tx('0' + (Deg/100)%10);
	USART0_Tx('0' + (Deg/10)%10);
	USART0_Tx('0' + (Deg%10));
	USART0_Tx('/');
	USART0_Tx(' ');
}

void SendSpeed_ToPc()
{
	USART0_Tx('S');
	USART0_Tx(':');		
	USART0_Tx(GetHex(Speed[7], 0));
	USART0_Tx(GetHex(Speed[6], 1));
	USART0_Tx(GetHex(Speed[6], 0));
	USART0_Tx('/');
	USART0_Tx(' ');
}

char GetHex(int in, int pos)
{	// 각 자리의 헥사값을 아스키로 표현
	in = (in>>(pos*4))&0x000F;
	if(in<10)	return '0'+in;
	else		return 'A'+(in%10);
}

unsigned char GetCheckSum(char * inst, int len)
{
	int i;
	unsigned char ret = 0;

	for(i = 2; i<len-1; i++)
	{
		ret += *(inst+i);
	}

	return ~ret;
}

void init()
{
	int i;

	head = 0;
	for(i = 0; i<3; i++)	Input[i] = 0;
}
