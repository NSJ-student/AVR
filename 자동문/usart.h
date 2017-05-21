#ifndef 	__USART_H__
#define 	__USART_H__
	
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

												// 숫자가 잘리지않도록 하기위해 unsigned long으로 확장
#define	F_OSC	((unsigned long)(16000000))			// F_CPU은 Makefile에 define됨
#define	BAUD	115200
#define	UBRR_H	( (unsigned long) ( ( F_OSC/ (16.0*BAUD) )-0.5 )>>8)	// 비동기 모드 , normal mode
#define	UBRR_L	( (unsigned long) ((F_OSC/(16.0*BAUD))-0.5) )

void Usart0_Init(void);
void Usart1_Init(void);

void USART0_Tx( unsigned char);
void USART1_Tx( unsigned char);

void Usart_Print(const char *);

unsigned char USART0_Rx(void);
unsigned char USART1_Rx(void);

#endif	/* __USART_H__ */
