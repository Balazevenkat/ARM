#include<LPC21xx.h>
#include<stdlib.h>
//#include"LCD_defines.h"
#include"time.h"
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
//cs8 Cgram[]={0x1d,0x05,0x05,0x1f,0x14,0x14,0x17,0x00};//0x00,
/*0x0A,
0x00,
0x00,
0x11,
0x0E,
0x00,
0x00*/
void portmode(u32 starting_bit,u32 npins)
{
  IODIR0|=((1<<npins)-1)<<starting_bit;
}
void digital_write(u32 data,u32 bit)
{
	bit?(IOSET0=1<<data):(IOCLR0=1<<data);
}
/*void write2pins(u32 bit, u32 npin, u32 data)
{
    IOCLR0 = ((1 << npin) - 1) << bit;
    IOSET0 = data << bit;
}*/
void write2pins(s32 bit,s32 data)
{
	// data were geting in byte know 8 bits is sufficent
	IOCLR0=0xFF<< bit;
	IOSET0=(data & 0xFF)<<bit;
}
void write_LCD(u32 byte)
{
	//write rw 0 always 
	digital_write(LCD_RW,0);
	// writing byte is data accsessing pins
	write2pins(LCD_data,byte);
	//enable must
	digital_write(LCD_EN,1);
	delay_ms(1);
	digital_write(LCD_EN,0);
	delay_ms(2);
}
void LCD_cmd(u32 byte)
{
	// intialization LCD_RS should be low 0
	digital_write(LCD_RS,0);
	//write to LCD
	write_LCD(byte);
}
void charLCD(s8 ascii)
{
	digital_write(LCD_RS,1);//rs need pass data so,high
	write_LCD(ascii);
}
void strLCD(s8 *p)
{
	while(*p)
	{
	charLCD(*p);
	p++;
	}
}	
void INIZ(void)
{ 
	portmode(LCD_data,11);
	LCD_cmd(MODE_8_BIT_LINE1);
	delay_ms(15);
	LCD_cmd(MODE_8_BIT_LINE1);
	delay_us(4100);
	LCD_cmd(MODE_8_BIT_LINE2);
	delay_us(100);
	LCD_cmd(DIS_ON_CUR_OFF );
	LCD_cmd(CLR_DIS);
	LCD_cmd(DIS_SHF_RIG);
}
void LCD_int_DIS1(s32 n)
{
    s8 buf[10];
    s32 i = 0;

    if(n == 0)
    {
        charLCD('0');
        return;
    }

    // convert number to string
    while(n > 0)
    {
        buf[i++] = (n % 10) + '0';
        n = n / 10;
    }

    // print in correct order
    while(i--)
    {
        charLCD(buf[i]);
    }
}

void LCD_int_DIS(s32 n)
{
    s32 val, i = 0;
    s8 dig[10];

    if(n == 0)
    {
        charLCD('0');
    }

    while(n > 0)   // FIXED only this line
    {
        val = n % 10;
        dig[i] = val + 48;
        i++;
        n /= 10;
    }

    for(--i; i >= 0; i--)
    {

        charLCD(dig[i]);
    }
}
/*void cgram(s32 cgram,s32 bytes)
{
	s32 i=0;
	LCD_cmd(cgram);//address of cgram staring 0x40
	for(i=0;i<bytes;i++)
	{
		digital_write(LCD_RS,1);
		write_LCD(Cgram[i]);
	}
}
           *s32 main()
{
	INIZ();
	cgram(cgram_ad,8);
	LCD_cmd(0x80);//go to line1
	charLCD(0); 
	while(1);
}*/