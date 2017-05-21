#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "func.h"


void ADC_init()
{
	ADCSRA = 0xA0;	// ADC enable, auto-trigger, ºÐÁÖºñ 2
	ADCSRB = 0x00;	// free-running mode
	ADMUX = 0xC0;	//	Vref = 2.56V, ADC0 Ã¤³Î(PF0) »ç¿ë 	

	_delay_ms(1);	
	ADCSRA |= 0x40;
}

void AC_init()
{
	ACSR = 0x40;					// ACD=0:    enable AC
								// ACBG=1: positive input: 1.1V
								// use ADC channel as negative input
	ADCSRA = 0x00;					// ADEN=0 : Disable ADC
	ADCSRB = 0x40;					// ACME=1:  use ADC channel for negative input
	ADMUX = 0x01;				// negative input : ADC1 = PF1
}

int ADC_Compare(int open)
{
	int result;

	while( (ADCSRA&0x10) != 0x10 );
	result = (ADCH&0x00FF)<<8;
	result += (ADCL&0x00FF);

	if( result > 0x1FF )	// ¹® ¿­¸²
	{
		ActionMotor(170);	// ¹® ¿­¸²
		_delay_us(100);
		open = 1;
	}
	else					// ¹® ´ÝÈû
	{
		if(open == 1)
		{
			_delay_ms(3000);	// Áö¿¬
			open = 0;
		}
		else
		{
			ActionMotor(130);	// ¹® ´ÝÈû
			_delay_us(100);
		}
	}

	return open;
}

int AC_Compare(int open)
{
	if( (ACSR&0x20) == 0x20)	// V+ > V-
	{
		if(open == 1)
		{
			_delay_ms(3000);	// Áö¿¬
			open = 0;
		}
		else
		{
			ActionMotor(130);	// ¹® ´ÝÈû
			_delay_us(100);
		}
	}	
	else						// V+ < V-
	{
		ActionMotor(170);	// ¹® ¿­¸²
		_delay_us(100);
		open = 1;
	}

	return open;
}
