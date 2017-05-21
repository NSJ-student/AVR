#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <math.h>
#include "adc.h"
#include "usart.h"


#define BCOEFFICIENT 		3950	// The beta coefficient of the thermistor (usually 3000-4000)
#define THERMISTORNOMINAL 	10000	// resistance at 25 degrees C
#define TEMPERATURENOMINAL 	25		// temp. for nominal resistance (almost always 25 C)
#define SERIESRESISTOR 		10000	// the value of the 'other' resistor

#define TXLEN				16		// 송신 버퍼 길이

#define ADC_NON		0
#define ADC_CMP		1
#define ADC_RDY		2

// ADC 관련 변수
volatile int AdcCnt = 0;
volatile int AdcFlag = 0;
volatile float fVolt = 0;
volatile long lValue = 0;
volatile float steinhart;

// 온도 전송 관련 변수
volatile int uFlag = 0;
volatile unsigned char arrTxBuffer[TXLEN+1] = {'$', '-', '-', 'M', 'T', 'W', 	// 헤더
												'0', '0', '.', '0','0', 		// 온도값
												'C', '*', 						// 온도 단위
												0x00, 							// 체크섬
												'\r', '\n', 0};					// 끝 문자

unsigned char GetASCf(float input, unsigned char ifNum, unsigned char digit);
unsigned char GetIntf(float input, unsigned char ifNum, unsigned char digit);
unsigned char GetASCh(unsigned int uiNum, unsigned char ucNum);
unsigned char GetCheckSum(volatile unsigned char * arrCom);

float fCalcNtc(int wADCVal)	;
float fCalcTemp( float fRntc);

int main(void)
{	
	unsigned char ucFnd[16] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
	};	
	unsigned char ucSel[4] = {0x0E, 0x0D, 0x0B, 0x07};
	unsigned char ucTemp[4] = {0x3F, 0x3F, 0x3F, 0x39};
	float fValue;
	unsigned int i = 0;
	unsigned char uartHead = 0;

	DDRC = 0xFF;
	DDRD = 0xFF;
	ADC_init();
	Usart0_Init();

	ADC_Start();

	while(1)
	{
		PORTD = ucSel[i%4];
		PORTC = ucTemp[i%4];
		i++;
		_delay_us(500);

		if(i>800)
		{
			i = 0;
			
			if(AdcFlag == ADC_RDY)
			{
				AdcFlag = ADC_NON;
				lValue = 0;
				AdcCnt = 0;
				ADC_Start();
			}
		}

		if(AdcFlag == ADC_CMP)
		{
			fValue = fCalcNtc(lValue);
			steinhart = fCalcTemp(fValue);

			ucTemp[0] = ucFnd[GetIntf(steinhart, 2, 0)];
			ucTemp[1] = ucFnd[GetIntf(steinhart, 1, 0)];
			ucTemp[1] = ucTemp[1]|0x80;
			ucTemp[2] = ucFnd[GetIntf(steinhart, 0, 1)];

			AdcFlag = ADC_RDY;
			lValue = 0;
			AdcCnt = 0;
		}


		if(uFlag != 0)
		{
			if(arrTxBuffer[uartHead] != 0)
			{
				USART0_Tx(arrTxBuffer[uartHead]);
				++uartHead;
			}
			else
			{
				uartHead = 0;
				uFlag = 0;
			}
		}
	}

	return 0;
}

ISR(USART0_RX_vect)	// 메시지 수신
{
	UDR0;

	arrTxBuffer[6] = GetASCf(steinhart, 2, 0);
	arrTxBuffer[7] = GetASCf(steinhart, 1, 0);

	arrTxBuffer[9] = GetASCf(steinhart, 0, 1);
	arrTxBuffer[10] = GetASCf(steinhart, 0, 2);

	arrTxBuffer[13] = 0;
	arrTxBuffer[13] = GetCheckSum(arrTxBuffer);

	uFlag = 1;
}

ISR(ADC_vect)
{
	AdcCnt++;
	if((AdcCnt > 3) && (AdcCnt <= 102))
	{
		lValue += ADC&0x03FF;
	}
	else if(AdcCnt > 102)
	{
		lValue += ADC&0x03FF;
		lValue = (int)(lValue/100);
		ADC_Stop();

		AdcFlag = ADC_CMP;
	}
}

unsigned char GetASCf(float input, unsigned char ifNum, unsigned char digit)
{
	float fNum;
	unsigned char tmp;
	int i;

	if(ifNum > 0)
	{
		tmp = (unsigned char)input;
		while(ifNum != 1)
		{
			tmp = tmp/10;
			ifNum--;
		}
		tmp = tmp%10;
	}
	else
	{
		fNum = input - (unsigned char)input;

		for(i=0; i<digit; i++) fNum = fNum*10;
		tmp	= (unsigned char)( (unsigned int)fNum%10);
	}

	return '0'+tmp;
}
unsigned char GetIntf(float input, unsigned char ifNum, unsigned char digit)
{
	float fNum;
	unsigned char tmp;
	int i;

	if(ifNum > 0)
	{
		tmp = (unsigned char)input;
		while(ifNum != 1)
		{
			tmp = tmp/10;
			ifNum--;
		}
		tmp = tmp%10;
	}
	else
	{
		fNum = input - (unsigned char)input;

		for(i=0; i<digit; i++) fNum = fNum*10;
		tmp	= (unsigned char)( (unsigned int)fNum%10);
	}

	return tmp;
}

unsigned char GetASCh(unsigned int uiNum, unsigned char ucNum)
{
	unsigned int tmp = uiNum;

	tmp = (uiNum>>(4*(ucNum-1)))&0x000F;

	if(tmp >= 10)
		return 'A'+tmp-10;
	else
		return '0'+tmp;
}

unsigned char GetCheckSum(volatile unsigned char * arrCom)
{
	int ucSum = 0;
	int i;

	for(i = 0; i<TXLEN-3; i++)
	{
		ucSum = ucSum + arrCom[i];
	}

	return (unsigned char)((~ucSum)&0xFF);
}

// calculate resistor value
float fCalcNtc(int wADCVal)	// from ADC
{ 
	float fRntc;

  	fRntc = 10000 *  (float) wADCVal / ( 1023.0  - (float) wADCVal);  // 10000 = pullup resistor
	return(fRntc);
}

// calculate temperature from resistorvalue
float fCalcTemp( float fRntc)
{
	float fTemp;

  	fTemp = (1.0 / ( (log(fRntc/THERMISTORNOMINAL))/BCOEFFICIENT  + 1.0/298.0)) - 273.0; //log = ln 
	return( fTemp);
}
