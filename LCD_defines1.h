#include"type.h"
#define LCD_data 8
#define LCD_RS 16
#define LCD_RW 17
#define LCD_EN 18
#define SW 4
#define CLR_DIS 0x01
#define MODE_8_BIT_LINE1 0x30
#define MODE_8_BIT_LINE2 0x38
#define DIS_ON_CUR_OFF 0x0C
#define DIS_ON_CUR_ON  0x0E
#define DIS_ON_CUR_ON_BLINK 0x0f
#define DIS_SHF_RIG 0x06
#define DIS_SHF_LEF 0x07
#define GO_TO_line1 0x80
#define GO_TO_line2 0xC0
#define cgram_ad 0x40
void LCD_cmd(u32 byte);
void INIZ(void);
void LCD_int_DIS(s32 n);
void LCD_int_DIS1(s32 n);
void strLCD(s8 *p);
