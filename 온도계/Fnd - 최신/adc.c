#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "adc.h"

void ADC_init(void)
{
	DDRF = 0xFE;
	ADCSRA = 0xA0;	// ADC enable, auto-trigger, 분주비 2
	ADCSRB = 0x00;	// free-running mode
	ADMUX  = 0x40;	//	Vref = AVCC, ADC0 채널(PF0) 사용 	

	_delay_ms(1);	
	ADCSRA |= 0x40;	// ADC 시작
}

void AC_init(void)
{
	ACSR = 0x40;		// ACD=0:    enable AC
					// ACBG=1: positive input: 1.1V
					// use ADC channel as negative input
	ADCSRA = 0x00;		// ADEN=0 : Disable ADC
	ADCSRB = 0x40;		// ACME=1:  use ADC channel for negative input
	ADMUX = 0x01;	// negative input : ADC1 = PF1
}

void ADC_Start(void)
{
	cli();

	ADCSRA = 0xA8;
	_delay_ms(1);
	ADCSRA |= 0x40;

	sei();
}

void ADC_Stop(void)
{
	cli();

	ADCSRA = 0x00;
	
	sei();
}
