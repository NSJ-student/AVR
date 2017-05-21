#include "smart2560.h"
#include "lcd.h"

volatile unsigned int tdSec = 0;		// 0.01s 단위 카운트
volatile unsigned int tSec = 0;		// 1s 단위 카운트
volatile unsigned char tFlag = 0;	// 시간 갱신 플래그

int main(void)
{
	SREG &= 0x7F;				// global interrupt disable(register setting 도중 오동작 방지)

	Lcd_Init();		// LCD 초기화
	TCCR1A = 0x00;	// CTC mode
	TCCR1B = 0x0C;	// CTC mode, 256 분주
	TCCR1C = 0x00;	// 비교출력 차단
	TCNT1 = 0x0000;	// 카운터 초기화
	TIMSK1 = 0x02;	// timer interrupt enable
	OCR1A = 624;		// 0.01 sec 간격 타이머

	EICRB = 0x0A;		// falling edge interrupt
	EIMSK = 0x30;	// INT4, INT5 enable

	SREG |= 0x80;				// global interrupt enable

	Lcd_Print("Time= ");
	tFlag = 1;
	
	while(1)
	{
		if(tFlag)		// 타이머 인터럽트가 발생
		{
			Lcd_SetAddr(6);				// 시간 표시 자리 설정
			Lcd_Data(((tSec/60)/10)+'0');
			Lcd_Data(((tSec/60)%10)+'0');
			Lcd_Data(':');
			Lcd_Data(((tSec%60)/10)+'0');
			Lcd_Data(((tSec%60)%10)+'0');
			Lcd_Data(':');
			Lcd_Data(tdSec/10+'0');
			Lcd_Data(tdSec%10+'0');

			tFlag = 0;
		}
	}
	return 0;
}

void __vector_17(void)		// 0.01s timer interrupt
{
	tdSec++;				// 10ms 단위로 증가
	
	if(tdSec == 100)
	{
		tSec++;				// 1s 단위로 증가
		if(tSec >= 3600) tSec = 0;		// 1시간 이상 카운터면 리셋

		tdSec = 0;
	}
	
	tFlag = 1;				// LCD display
}

void __vector_5(void)		// INT4: Timer on/off
{
	// Timer Interrupt 제어
	
	SREG &= 0x7F;				// global interrupt disable
	
	TIMSK1 ^= 0b00000010;		// compare match A interrupt enable/disable

	SREG |= 0x80;				// global interrupt enable
}

void __vector_6(void)		// INT5: Timer reset
{
	// Timer 초기화
	if( !(TIMSK1 & 0x02))		// 타이머가 동작안하는 상태에서
	{
		tdSec = 0;			// 초기화
		tSec = 0;
		tFlag = 1;			// 초기화된 내용 LCD 표시
	}
}

