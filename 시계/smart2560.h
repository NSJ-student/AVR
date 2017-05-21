#ifndef   __SMART2560_H__
#define  __SMART2560_H__

/* global interrupt register */

#define 	SREG		(*((volatile unsigned char *)0x5F))

#define 	ACSR		(*((volatile unsigned char *)0x50))

/* ADC register */

#define 	ADCL		(*((volatile unsigned char *)0x78))
#define 	ADCH		(*((volatile unsigned char *)0x79))
#define 	ADCSRA		(*((volatile unsigned char *)0x7A))
#define 	ADCSRB		(*((volatile unsigned char *)0x7B))
#define 	ADMUX		(*((volatile unsigned char *)0x7C))

/*  external interrupt register */

#define 	EICRA		(*((volatile unsigned char *)0x69))
#define 	EICRB		(*((volatile unsigned char *)0x6A))
#define 	EIMSK		(*((volatile unsigned char *)0x3D))
#define 	EIFR		(*((volatile unsigned char *)0x3C))

/* timer/counter1 register */

#define 	TIMSK1 		(*((volatile unsigned char *)0x6F))
#define 	TIFR1		(*((volatile unsigned char *)0x36))
#define 	TCCR1A		(*((volatile unsigned char *)0x80))
#define 	TCCR1B 		(*((volatile unsigned char *)0x81))
#define 	TCCR1C 		(*((volatile unsigned char *)0x82))
#define 	TCNT1L		(*((volatile unsigned char *)0x84))
#define 	TCNT1H		(*((volatile unsigned char *)0x85))
#define 	OCR1AL 		(*((volatile unsigned char *)0x88))
#define 	OCR1AH		(*((volatile unsigned char *)0x89))

#define 	OCR1A		(*((volatile unsigned int *)0x88))
#define 	TCNT1		(*((volatile unsigned int *)0x84))

/* timer/counter register */

#define 	TIMSK0 		(*((volatile unsigned char *)0x6E))
#define 	TIFR0		(*((volatile unsigned char *)0x35))
#define 	TCCR0A		(*((volatile unsigned char *)0x44))
#define 	TCCR0B 		(*((volatile unsigned char *)0x45))
#define 	TCNT0 		(*((volatile unsigned char *)0x46))
#define 	OCR0A 		(*((volatile unsigned char *)0x47))

/* gpio register */

#define	PINA		(*((volatile unsigned char *)0x20))
#define	DDRA		(*((volatile unsigned char *)0x21))
#define	PORTA		(*((volatile unsigned char *)0x22))

#define	DDRB		(*((volatile unsigned char *)0x24))
#define	PORTB		(*((volatile unsigned char *)0x25))

#define	PINC		(*((volatile unsigned char *)0x26))
#define	DDRC		(*((volatile unsigned char *)0x27))
#define	PORTC		(*((volatile unsigned char *)0x28))

#define	PIND		(*((volatile unsigned char *)0x29))
#define	DDRD		(*((volatile unsigned char *)0x2A))
#define	PORTD		(*((volatile unsigned char *)0x2B))

#define	PINE		(*((volatile unsigned char *)0x2C))
#define	DDRE		(*((volatile unsigned char *)0x2D))
#define	PORTE		(*((volatile unsigned char *)0x2E))

#define	PINF		(*((volatile unsigned char *)0x2F))
#define	DDRF		(*((volatile unsigned char *)0x30))
#define	PORTF		(*((volatile unsigned char *)0x31))

#define	DDRG		(*((volatile unsigned char *)0x33))
#define	PORTG		(*((volatile unsigned char *)0x34))

/* USART용 매크로 */

#define	UBRR0L		(*((volatile unsigned char *)0xC4))
#define	UBRR0H		(*((volatile unsigned char *)0xC5))
#define	UBRR1L		(*((volatile unsigned char *)0xCC))
#define	UBRR1H		(*((volatile unsigned char *)0xCD))

#define	UDR0		(*((volatile unsigned char *)0xC6))
#define	UDR1		(*((volatile unsigned char *)0xCE))

#define	UCSR0A		(*((volatile unsigned char *)0xC0))
#define	UCSR0B		(*((volatile unsigned char *)0xC1))
#define	UCSR0C		(*((volatile unsigned char *)0xC2))
#define	UCSR1A		(*((volatile unsigned char *)0xC8))
#define	UCSR1B		(*((volatile unsigned char *)0xC9))
#define	UCSR1C		(*((volatile unsigned char *)0xCA))

/* UCSRA register bit */

#define	RXC			7
#define	TXC			6
#define	UDRE		5
#define	FE			4
#define	DOR			3
#define	UPE			2
#define	U2X			1
#define	MPCM		0

/* UCSRB register bit */

#define	RXCIE		7
#define	TXCIE		6
#define	UDRIE		5
#define	RXEN		4
#define	TXEN		3
#define	UCSZ2		2
#define	RXB8		1
#define	TXB8		0

/* UCSRC register bit */

#define	UMSEL		6
#define	UPM1		5
#define	UPM0		4
#define	USBS		3
#define	UCSZ1		2
#define	UCSZ0		1
#define	UCPOL		0

/*
void __vector_1(void)__attribute__((signal, used, externally_visible));		// INT0의 인터럽트 함수

void __vector_1(void)__attribute__((signal, used, externally_visible));		// INT0의 인터럽트 함수
void __vector_2(void)__attribute__((signal, used, externally_visible));		// INT1의 인터럽트 함수
void __vector_3(void)__attribute__((signal, used, externally_visible));		// INT2의 인터럽트 함수
void __vector_4(void)__attribute__((signal, used, externally_visible));		// INT3의 인터럽트 함수
void __vector_21(void)__attribute__((signal, used, externally_visible));	// Timer0 CTC mode
void __vector_25(void)__attribute__((signal, used, externally_visible));		// USART RX의 인터럽트 함수
*/
void __vector_17(void)__attribute__((signal, used, externally_visible));		// Timer1 compare match A
void __vector_5(void)__attribute__((signal, used, externally_visible));		// INT0의 인터럽트 함수
void __vector_6(void)__attribute__((signal, used, externally_visible));		// INT0의 인터럽트 함수

#endif	/* __SMART2560_H__ */
