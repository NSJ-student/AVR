#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <math.h>
#include "lcd.h"
#include "adc.h"
#include "usart.h"


#define BCOEFFICIENT 		3950	// The beta coefficient of the thermistor (usually 3000-4000)
#define THERMISTORNOMINAL 	10000	// resistance at 25 degrees C
#define TEMPERATURENOMINAL 	25		// temp. for nominal resistance (almost always 25 C)
#define SERIESRESISTOR 		10000	// the value of the 'other' resistor
#define TXLEN				16


// ADC 관련 변수
volatile int AdcCnt = 0;
volatile int AdcFlag = 0;
volatile float fVolt = 0;
volatile long lValue = 0;

// 온도 전송 관련 변수
volatile float steinhart;
volatile unsigned char arrTxBuffer[TXLEN+1];
volatile void * vpTemp;

unsigned char GetASCf(float input, unsigned char ifNum, unsigned char digit);
unsigned char GetASCh(unsigned int uiNum, unsigned char ucNum);

unsigned char GetCheckSum(unsigned char * arrCom);
float fCalcNtc(int wADCVal)	;
float fCalcTemp( float fRntc);

int main(void)
{
	float fValue;

	Lcd_Init();
	ADC_init();
	Usart0_Init();

	ADC_Start();
	Lcd_SetAddr(0);
	Lcd_Print("Temp = ");

	while(1)
	{
		if(AdcFlag != 0)                    
		{
			/*
			// convert the value to resistance
			fValue = (float)1023 / iValue - 1;
			fValue = SERIESRESISTOR  / fValue;
			// Thermistor resistance = tsum
			steinhart = fValue / THERMISTORNOMINAL;     		// (R/Ro)
			steinhart = log(steinhart);                  		// ln(R/Ro)
			steinhart /= BCOEFFICIENT;                   		// 1/B * ln(R/Ro)
			steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); 	// + (1/To)
			steinhart = 1.0 / steinhart;                 		// Invert
			steinhart -= 273.15;     
			*/

			fValue = fCalcNtc(lValue);
			steinhart = fCalcTemp(fValue);

			cli();
			Lcd_SetAddr(7);
			Lcd_Data(GetASCf(steinhart, 2, 0));
			Lcd_Data(GetASCf(steinhart, 1, 0));
			Lcd_Data('.');
			Lcd_Data(GetASCf(steinhart, 0, 1));
			Lcd_Data(GetASCf(steinhart, 0, 2));
			Lcd_Print(" deg");
			sei();

			AdcFlag = 0;
			lValue = 0;
			AdcCnt = 0;
			_delay_ms(500);
			ADC_Start();
		}
	}


	return 0;
}

ISR(USART0_RX_vect)	// 메시지 수신
{
	char Buf = UDR0;

	arrTxBuffer[0] ='$';
	arrTxBuffer[1] ='-';
	arrTxBuffer[2] ='-';
	arrTxBuffer[3] ='M';
	arrTxBuffer[4] ='T';
	arrTxBuffer[5] ='W';

	arrTxBuffer[6] = GetASCf(steinhart, 2, 0);
	arrTxBuffer[7] = GetASCf(steinhart, 1, 0);
	arrTxBuffer[8] = '.';
	arrTxBuffer[9] = GetASCf(steinhart, 0, 1);
	arrTxBuffer[10] = GetASCf(steinhart, 0, 2);
	/*
	vpTemp = arrTxBuffer+6;
	*((float *)vpTemp) = (float)steinhart;
	*/
	arrTxBuffer[11] ='C';
	arrTxBuffer[12] = '*';
	arrTxBuffer[13] = 0;
	arrTxBuffer[13] = GetCheckSum(arrTxBuffer);
	arrTxBuffer[14] = '\r';
	arrTxBuffer[15] = '\n';
	arrTxBuffer[16] = 0;
	Usart_Print(arrTxBuffer);

	Lcd_SetAddr(0x40);
	Lcd_Data('O');
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
		//fVolt = (float)iValue/1024;
		ADC_Stop();

		AdcFlag = 1;
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

unsigned char GetASCh(unsigned int uiNum, unsigned char ucNum)
{
	unsigned int tmp = uiNum;

	tmp = (uiNum>>(4*(ucNum-1)))&0x000F;

	if(tmp >= 10)
		return 'A'+tmp-10;
	else
		return '0'+tmp;
}

unsigned char GetCheckSum(unsigned char * arrCom)
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
