#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

void Spi_Init(void)
{
	// B0 : /SS, B1 : SCK, B2 : MOSI, B3 : MISO
	DDRB = 0xF7;	// SPI에 사용하는 핀

	SPCR = 0x3D;	// MSB first, CPOL=1, CPHA=1, SCK=Fosc/16
	SPSR = 0x00;

	return;
}

void SPI_Write(unsigned char byte)
{
	// /CS = 0

	// SPDR 
	// Delay 10ms
	// Data 쓰기
	// Delay 10ms
	// Data 쓰기

	// Delay 50ms

	// Data 쓰기
	// Delay 10ms
	// Data 쓰기
	// Delay 10ms
	// Data 쓰기

	// /CS = 1

	return;
}

/*
long Check_Temp(unsigned char datum) // Sonix 컴파일러에는 Long 이 2byte 입니다.
{
	long temp_bank=0;

	SIOB = datum; // Buffer 레지스터에 저장
	NOP(1);
	EN_LOW; // Enable Low
	delay_us(10); // 10us delay
	FSTART = 1; // SPI 전송 시작
	while(FSTART==1); // 전송 완료 flag check
	buffer2=SIOB; // dummy

	SIOB = 0x22; // 0x22 or 0x00 가능합니다.
	delay_ms(10); // 10ms delay
	FSTART = 1; // SPI 전송 시작
	while(FSTART==1); // 전송 완료 flag check
	buffer=SIOB; // 하위 Byte 저장

	SIOB = 0x22; // 0x22 or 0x00 가능합니다.
	delay_ms(10); // 10ms delay
	FSTART = 1; // SPI 전송 시작
	while(FSTART==1); // 전송 완료 flag check
	buffer1=SIOB; // 상위 Byte 저장

	EN_HIGH; // Enable High
	temp_bank=(buffer1*256)+buffer; // 상위, 하위 Byte 온도 계산식.

	// temp_bank : 최종 온도
	return temp_bank;
}
*/
