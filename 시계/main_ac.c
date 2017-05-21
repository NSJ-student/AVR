#include "smart2560.h"

int main(void)
{
	SREG &= 0x7F;	// global interrupt disable(register setting 도중 오동작 방지)

	DDRB = 0xFF;		// LED
	
	TCCR1A = 0x00;	// CTC mode
	TCCR1B = 0x04;	// CTC mode, 256 분주
	TCCR1C = 0x00;	// 비교출력 차단
	TCNT1 = 0x0000;	// 카운터 초기화
	TIMSK1 = 0x02;	// compare match A interrupt enable
	OCR1A = 62499;	// 1 sec 간격 타이머

	SREG |= 0x80;	// global interrupt enable

	PORTB = 0x00;	// LED all off
	
	while(1);
	
	return 0;
}

void __vector_17(void)		// 1s timer interrupt
{
	PORTB ^= 0xFF;	// LED toggle
}


