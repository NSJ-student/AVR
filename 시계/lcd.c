#include "lcd.h"

#define	DNUM1	120
#define	DNUM2	480
#define	DNUM3	120

static unsigned int uiCharCnt;

void Lcd_Avr_Pin_Init(void)
{
	LCD_BUS_DDR = 0xFF;		// 모두 출력모드로
	LCD_CTL_DDR |= (1<<LCD_PIN_RS)|(1<<LCD_PIN_RW)|(1<<LCD_PIN_EN);	// LCD의 제어핀들을 출력모드로 (0x07과 같다)

	return;
}

void Lcd_Inst(unsigned char ucInst)	// LCD에 명령을 전달, lcd.c에서만 호출가능
{
	volatile unsigned int uiCnt;

	LCD_BUS = ucInst;

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	DELAY(DNUM1);
	
	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN 활설화
	DELAY(DNUM2);													// (최소 150ns 필요)LCD가 제대로 동작하기위한 지연시간	

	LCD_CTL = (0<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	DELAY(DNUM3);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	return;
}

void Lcd_Data(unsigned char ucData)	// LCD에 Data를 전달
{
	volatile unsigned int uiCnt;

	if( 15 < uiCharCnt )				// 주소가 15보다 크면
	{
		if( 40 > uiCharCnt )			// 주소가 40보다 작다면
		{
			uiCharCnt = 40;			// 2 줄의 맨 앞

			Lcd_SetAddr(uiCharCnt);	
		}
		else if( 55 < uiCharCnt )		// 주소가 55보다 크면
		{
			uiCharCnt = 0;			// 첫 줄의 맨 앞

			Lcd_SetAddr(uiCharCnt);	
		}
	}

	++uiCharCnt;

	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	DELAY(DNUM1);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN 활설화
	DELAY(DNUM2);													// (최소 150ns 필요)LCD가 제대로 동작하기위한 지연시간	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	DELAY(DNUM3);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	return;
}

void Lcd_Init(void)
{
	volatile unsigned int uiCnt;

	Lcd_Avr_Pin_Init();			// AVR pin 초기화

	DELAY(65000);				// LCD booting을 기다린다

	Lcd_Inst(LCD_INST_FUNC);	// LCD 기능들 초기화
	Lcd_Inst(LCD_INST_DSP);
	Lcd_Inst(LCD_INST_ENT);
	Lcd_Inst(LCD_INST_CUR);
	Lcd_Inst(LCD_INST_CLR);
	Lcd_Inst(LCD_INST_HOME);

	uiCharCnt = 0;

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
	if( 15 < ucAddr )				// 주소가 15보다 크면
	{
		if( 40 > ucAddr )			// 주소가 40보다 작다면
		{
			ucAddr = 40;			// 다음 줄의 맨 앞
		}
		else if( 55 < ucAddr )		// 주소가 55보다 크면
		{
			ucAddr = 0;			// 첫 줄의 맨 앞
		}
	}
	uiCharCnt = ucAddr;
	
	Lcd_Inst( 0x80 | ucAddr );	// 커서 위치를 설정한다
	
	return;
}

void Lcd_CGRAM_Init(void)
{	
	unsigned char Nam[8] 	= {0x12, 0x12, 0x13, 0x1E, 0x02, 0x1F, 0x11, 0x1F};
	unsigned char Su[8] 	= {0x04, 0x04, 0x0A, 0x11, 0x00, 0x1F, 0x04, 0x04};
	unsigned char Jin[8] 	= {0x1D, 0x09, 0x15, 0x15, 0x01, 0x10, 0x10, 0x1F};
	
	Lcd_CGRAM_Set(0, Nam);		
	Lcd_CGRAM_Set(1, Su);
	Lcd_CGRAM_Set(2, Jin);

	Lcd_SetAddr(uiCharCnt);	

	return;
}

void Lcd_CGRAM_Data(unsigned char ucData)
{
	volatile unsigned int uiCnt;
	
	LCD_BUS = ucData;

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	DELAY(DNUM1);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(1<<LCD_PIN_EN);		// EN 활설화
	DELAY(DNUM2);													// (최소 150ns 필요)LCD가 제대로 동작하기위한 지연시간	

	LCD_CTL = (1<<LCD_PIN_RS)|(0<<LCD_PIN_RW)|(0<<LCD_PIN_EN);		// datasheet timing diagram의 맨 앞
	DELAY(DNUM3);													// (최소 40ns 필요)LCD가 제대로 동작하기위한 지연시간

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

