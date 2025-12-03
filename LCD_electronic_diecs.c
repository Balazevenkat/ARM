//0 0 21 DL N F * * Set Interface Length

/*#include <LPC21xx.h>
#include <stdlib.h>
#include "time.h"
#include "type.h"

//switch for dices
#define SW 4

// pins RS,RW,E as below
#define LCD_DATA 8
#define LCD_RS   16
#define LCD_RW   17 // not required in kit based performance
#define LCD_EN   18 // so,indirectly we need to access upto 18th pin from 8th pin total 11

//LCD access command in hex
#define MODE_8_BIT_LINE1 0x30
#define MODE_8_BIT_LINE2 0x38
#define CLR_DIS 0x01
#define DIS_ON_cur_blink  0x0f
#define DIS_ON 0x0c

// to make use of pins need to set bit help of GPIO
void port_mode(u32 start_bit, u32 npins)
{
    IODIR0 |= ((1 << npins) - 1) << start_bit;
}

void digital_write(u32 data, u32 bit)
{
    bit ? (IOSET0 = 1 << data) : (IOCLR0 = 1 << data);
}

void write2pins(u32 bit, u32 npins, u32 data)
{
    IOCLR0 = ((1 << npins) - 1) << bit;
    IOSET0 = data << bit;
}


void write2pins(u32 byte,u32 bit)
{
  IOCLR0=0xff<<bit;
  IOSET0=(byte&0xff)<<bit;
}



void write_LCD(u32 byte)
{
    digital_write(LCD_RW, 0);
    write2pins(LCD_DATA, 8, byte);
    digital_write(LCD_EN, 1);
    delay_us(1);
    digital_write(LCD_EN, 0);
    delay_ms(2);
}

// LCD_cmd this function is used only initialization purpose
void LCD_cmd(u32 byte)
{
    digital_write(LCD_RS, 0);
    write_LCD(byte);
}

void INIZ_LCD()
{
    port_mode(LCD_DATA, 11);
    delay_ms(15);
    LCD_cmd(MODE_8_BIT_LINE1);
    delay_ms(4);

    port_mode(LCD_DATA, 11);
    delay_ms(15);
    LCD_cmd(MODE_8_BIT_LINE1);
    delay_ms(4);
    delay_us(100);

    LCD_cmd(MODE_8_BIT_LINE1);
    delay_us(100);
    LCD_cmd(MODE_8_BIT_LINE1);
    LCD_cmd(MODE_8_BIT_LINE2);
    LCD_cmd(CLR_DIS);
    LCD_cmd(DIS_ON_cur_blink);
    //LCD_cmd(0x06);
}

void charLCD(s8 ascii)
{
    digital_write(LCD_RS, 1);
    write_LCD(ascii);
}

void strLCD(s8 *p)
{
    while (*p)
        charLCD(*p++);
}

void int_ascii(s32 n)
{
    s8 digi[10];
    s32 i = 0, val;

    if (n == 0)
    {
        charLCD('0');
    }

    while (n > 0)
    {
        val = n % 10;
        digi[i] = val + 48;
        i++;
        n /= 10;
    }

    for (--i; i >= 0; i--)
    {
        charLCD(digi[i]);
    }
}

void LCD_int(s32 n)
{
    if (n < 0)
    {
        charLCD('-');
        n = -n;
    }
    int_ascii(n);
}

void LCD_float(s32 n)
{
    if (n < 0.0)
    {
        charLCD('-');
        n = -n;
    }
    int_ascii(n);
}

int main()
{
    s32 dices, seed = 0;

    INIZ_LCD();
    IODIR0 |= SW << 1;

    strLCD("Electronic Diecs");

    while (1)
    {
        LCD_cmd(0xC0);

        if (((IOPIN0 >> SW) & 1) == 0)
        {
            dices = (rand() % 6) + 1;
            int_ascii(dices);
            srand(seed++);
            delay_ms(200);
        }
    }
}

*/
#include<LPC21xx.h>
#include<stdlib.h>
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

           
s32 main()
{
	int seed,r;
	INIZ();
	//charLCD('A');
	strLCD("ELECTRONIC DIECS");
	//LCD_cmd(0xc0);//line 2
IODIR0|=SW<<1;
//	IODIR0 &= ~(1 << SW); 
	while(1)
	{
		LCD_cmd(0xC0);
		if(((IOPIN0>>SW)&1)==1)
		{
			
			r=(rand()%6)+1;
			LCD_int_DIS(r);
			srand(seed++);
		delay_ms(200);
		}
	}
	
}
/*
#include <LPC21xx.h>
#include <stdlib.h>
#include "time.h"
#include "type.h"

#define LCD_data 8
#define LCD_RS 16
#define LCD_RW 17
#define LCD_EN 18
#define SW 4

#define CLR_DIS 0x01
#define MODE_8_BIT_LINE1 0x30
#define MODE_8_BIT_LINE2 0x38
#define DIS_ON_CUR_OFF 0x0C
#define DIS_SHF_RIG 0x06

//------------------------------------------------------

void portmode(u32 starting_bit,u32 npins)
{
    IODIR0 |= ((1 << npins) - 1) << starting_bit;
}

void digital_write(u32 data,u32 bit)
{
    bit ? (IOSET0 = 1 << data) : (IOCLR0 = 1 << data);
}

void write2pins(s32 data,s32 bit)
{
    IOCLR0 = (0xFF << bit);      // CLEAR ONLY 8 PINS
    IOSET0 = (data & 0xFF) << bit;
}

void write_LCD(u32 byte)
{
    digital_write(LCD_RW,0);
    write2pins(byte, LCD_data);

    digital_write(LCD_EN,1);
    delay_us(1);
    digital_write(LCD_EN,0);
    delay_ms(2);
}

void LCD_cmd(u32 byte)
{
    digital_write(LCD_RS,0);
    write_LCD(byte);
}

void charLCD(s8 ascii)
{
    digital_write(LCD_RS,1);
    write_LCD(ascii);
}

void strLCD(s8 *p)
{
    while(*p)
        charLCD(*p++);
}

//------------------------------------------------------
// FIXED LCD INITIALIZATION (yours was wrong order)
//------------------------------------------------------
void INIZ(void)
{
    portmode(LCD_data,11);

    delay_ms(15);
    LCD_cmd(MODE_8_BIT_LINE1);

    delay_ms(5);
    LCD_cmd(MODE_8_BIT_LINE1);

    delay_us(100);
    LCD_cmd(MODE_8_BIT_LINE1);

    LCD_cmd(MODE_8_BIT_LINE2);
    LCD_cmd(CLR_DIS);
    LCD_cmd(DIS_ON_CUR_OFF);
    LCD_cmd(DIS_SHF_RIG);
}

//------------------------------------------------------
// FIXED NUMBER PRINT (your version printed garbage)
//------------------------------------------------------
void LCD_int_DIS(s32 n)
{
    s8 dig[10];
    int i = 0;

    if(n == 0)
    {
        charLCD('0');
        return;       // important (your code missed this)
    }

    while(n > 0)
    {
        dig[i++] = (n % 10) + '0';
        n /= 10;
    }

    while(--i >= 0)
        charLCD(dig[i]);
}

//------------------------------------------------------

s32 main()
{
    int seed = 0, r;

    INIZ();
    strLCD("ELECTRONIC DIECS");

    // FIXED ? switch should be INPUT
    IODIR0 &= ~(1 << SW);

    while(1)
    {
        LCD_cmd(0xC0);

        if(((IOPIN0 >> SW) & 1) == 0)
        {
            r = (rand() % 6) + 1;
            LCD_int_DIS(r);

            srand(seed++);
            delay_ms(200);
        }
    }
}
*/
