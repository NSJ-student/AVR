#ifndef   __LCD_H__
#define  __LCD_H__

#define	LCD_BUS		PORTC
#define	LCD_CTL		PORTG

#define	LCD_BUS_DDR	DDRC	
#define	LCD_CTL_DDR	DDRG

#define	LCD_PIN_RS		0
#define	LCD_PIN_RW		1
#define	LCD_PIN_EN		2

#define 	LCD_INST_CLR	0x01	// clear display
#define 	LCD_INST_HOME	0x02	// cursor home
#define 	LCD_INST_ENT	0x06	// increase mode(I/D = 1), shift off(S = 0)
#define 	LCD_INST_DSP	0x0F	// display on(D = 1), cursor on(C = 1), blink on(B = 1)
#define 	LCD_INST_CUR	0x14	// cursor right shift(R/L = 1)
#define 	LCD_INST_FUNC	0x38	// data length 8bit(DL = 1), 2 line(N = 1), 5x8 font(F = 0)


void Lcd_Avr_Pin_Init(void);
void Lcd_Inst(unsigned char ucInst);
void Lcd_Data(unsigned char);
void Lcd_Init(void);
void Lcd_Print(const char *);

void Lcd_SetAddr(unsigned char);

void Lcd_CGRAM_Init(void);
void Lcd_CGRAM_Data(unsigned char);
void Lcd_CGRAM_Set(unsigned char, const unsigned char *);

void Lcd_Cursor(unsigned char x, unsigned char y);
void Lcd_LineClear(unsigned char line);

#endif	/* __LCD_H__ */
