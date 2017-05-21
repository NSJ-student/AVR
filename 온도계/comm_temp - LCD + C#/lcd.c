#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "lcd.h"

void Lcd_Avr_Pin_Init(void)
{
	LCD_BUS_DDR = 0xFF;		// 모두 출력모드로
	LCD_CTL_DDR |= (1<<LCD_PIN_RS)|(1<<LCD_PIN_RW)|(1<<LCD_PIN_EN);	// LCD의 제어핀들을 출력모드로 (0x07과 같다)

	return;
}

void Lcd_Init(void)
{
	Lcd_Avr_Pin_Init();			// AVR pin 초기화

	_delay_ms(100);				// LCD booting을 기다린다

	Lcd_Inst(LCD_INST_FUNC);	// LCD 기능들 초기화
	Lcd_Inst(LCD_INST_DSP);
	Lcd_Inst(LCD_INST_ENT);
	Lcd_Inst(LCD_INST_CUR);
	Lcd_Inst(LCD_INST_CLR);
	Lcd_Inst(LCD_INST_HOME);

	_delay_ms(5);

	return;
}

void Lcd_Inst(unsigned char ucInst)	// LCD에 명령을 전달, lcd.c에서만 호출가능
{
	LCD_BUS = ucInst;

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	_delay_us(10);
	
	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN 활설화
	_delay_us(50);													// (최소 150ns 필요)LCD가 제대로 동작하기위한 지연시간	

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	_delay_us(10);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	return;
}

void Lcd_Data(unsigned char ucData)	// LCD에 Data를 전달
{
	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	_delay_us(10);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN 활성화
	_delay_us(50);													// (최소 150ns 필요)LCD가 제대로 동작하기위한 지연시간	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	_delay_us(10);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	return;
}

void Lcd_Print(const char * ucString)	// 들어온 문자열을 수정하지않기위해서 const를 붙인다
{
	while( 0 != *ucString )
	{
		Lcd_Data(*ucString);
		++ucString;
	}

	return;
}


void Lcd_SetAddr(unsigned char ucAddr)
{
	Lcd_Inst( 0x80 | ucAddr );	// 커서 위치를 설정한다
	
	return;
}

void Lcd_Cursor(unsigned char x, unsigned char y)
{
	unsigned char ucAddr;

	ucAddr = (0x40*y) + x;

	Lcd_Inst( 0x80 | ucAddr );	// 커서 위치를 설정한다

	return;
}

void Lcd_LineClear(unsigned char line)
{
	char * clear = "                ";
	
	Lcd_SetAddr( (line*0x40) );
	Lcd_Print(clear);
}

void Lcd_CGRAM_Init(void)
{	
	unsigned char NO[8] 	= {0x1F, 0x15, 0x15, 0x1B, 0x15, 0x15, 0x1F, 0x1F};
	unsigned char OK[8] 	= {0x1F, 0x1B, 0x15, 0x15, 0x15, 0x15, 0x1B, 0x1F};
	
	Lcd_CGRAM_Set(0, NO);		
	Lcd_CGRAM_Set(1, OK);

	Lcd_SetAddr(0);	

	return;
}

void Lcd_CGRAM_Data(unsigned char ucData)
{
	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	_delay_us(10);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN 활설화
	_delay_us(50);													// (최소 150ns 필요)LCD가 제대로 동작하기위한 지연시간	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	_delay_us(10);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	return;
}

void Lcd_CGRAM_Set(unsigned char ucAddr, const unsigned char * ucData)
{
	unsigned int uiCnt = 0;

	Lcd_Inst( 0x40 | (ucAddr<<3) );

	for( uiCnt = 0; uiCnt < 8; uiCnt++)
	{
		Lcd_CGRAM_Data(*ucData);
		ucData++;
	}
	
	return;
}

