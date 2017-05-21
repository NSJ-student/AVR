#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "spi.h"
#include "lcd.h"

int main(void)
{
	long Target_Value, Ambient_Value; //부호 있는 2byte 선언
	//Port_init(); // PORT 초기화
	//LCD_init(); // LCD 초기화
	//EN_HIGH; // CS idle High
	//SPI_init(); // SPI 초기화

	while(1)
	{
		SPI_Write(0xA0);

		SPI_Write(0xA1);

	}

	return 0;
}
