#include "usart.h"

void Usart0_Init(void)
{
	UBRR0H = UBRR_H;
	UBRR0L = UBRR_L;

	UCSR0A = (0<<U2X)|(0<<MPCM);
	UCSR0B = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);
	UCSR0C = (0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
	// non parity, 8bit, 1 stop bit

	return;
}

void Usart1_Init(void)
{
	UBRR1H = UBRR_H;
	UBRR1L = UBRR_L;

	UCSR1A = (0<<U2X)|(0<<MPCM);
	UCSR1B = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);
	UCSR1C = (0<<UMSEL)|(1<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);

	return;
}

void USART0_Tx( unsigned char ucData )
{
	// Wait for empty transmit buffer (empty UDR)
	// UCSR0A를 (1<<UDRE)로 MASK시켜서 UCSR0A의 UDRE자리의 비트를 추출
	// UCSR0A의 UDRE비트가 1이면 무한루프를 돈다
	// UCSR0A의 UDRE비트가 0이면 루프를 나와 다음 코드로 나간다
	// Polling: 인터럽트에비해 CPU자원낭비가 생긴다
	while ( 0 == ( UCSR0A & (1<<UDRE)) );


	// Put data into buffer, sends the data 
	UDR0 = ucData;

	return;
}

void USART1_Tx( unsigned char ucData )
{
	while ( 0 == ( UCSR1A & (1<<UDRE)) );

	UDR1 = ucData;

	return;
}

void Usart_Print(const unsigned char * ucString)
{
	while( 0 != *ucString )
	{
		USART0_Tx(*ucString);
		++ucString;
	}

	return;
}

unsigned char USART0_Rx( void )
{
	// Wait for data to be received 	
	while ( !( UCSR0A  &  (1<<RXC) ) )	;	//	UCSRA: Datasheet 184p 	
										//	Polling 기법(UCSRA의 수신완료비트 RXC가 1이 될?蒻㎟沮? wait)

	// Get and return received data from buffer 
	return UDR0;		// 수신된 데이터를 함수를 호출한 곳에 전달한다
}

unsigned char USART1_Rx( void )
{
	// Wait for data to be received 
	while ( !( UCSR1A  &  (1<<RXC) ) )	;

	// Get and return received data from buffer 
	return UDR1;
}

