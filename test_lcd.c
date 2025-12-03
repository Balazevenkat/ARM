// 0 0 1 DL N F * *  Set Interface Length (HD44780 command format)
// Using LPC2148 - LCD (8-bit mode) example
#include <LPC21xx.h>
#include "time.h"
#include "tydef.h"   // contains u32, s8 etc

// pins RS, RW, E as below
#define LCD_data 8
#define LCD_RS   16
#define LCD_RW   17  // not required in kit based performance
#define LCD_EN   18  // so, indirectly we need to access upto 18th pin from 8th pin total 11

// LCD access command in hex
#define MODE_8_BIT_LINE1 0x30 // because N is '0'  // 0 0 1 DL N F * * Set Interface Length; F also zero: 8 dots/char
#define MODE_8_BIT_LINE2 0x38 // f remains same only N changes so access second line
#define CLR_DIS          0x01

/* Display control examples:
   0x0C -> Display ON, Cursor OFF, Blink OFF
   0x0E -> Display ON, Cursor ON,  Blink OFF
   0x0F -> Display ON, Cursor ON,  Blink ON
*/
#define DIS_ON_cur_blink 0x0F
#define DIS_ON           0x0C

// to make use of pins need to set bit help of GPIO
void port_mode(us32 start_bit, us32 npins)
{
    // configure npins starting from start_bit as outputs
    // ((npins << start_bit) - 1) << start_bit  => mask for npins bits shifted
    IODIR0 |= (((1 << npins) - 1) << start_bit);
}

void digital_write(us32 data, us32 bit)
{
    // bit ? set : clear
    bit ? (IOSET0 = 1 << data) : (IOCLR0 = 1 << data);
}

void write2pins(us32 byte, us32 bit)
{
    // clear target pins then set according to lower 8 bits of byte
    IOCLR0 = 0xFF << bit;
    IOSET0 = (byte & 0xFF) << bit;
}

void write_LCD(us32 byte)
{
    // any how not reading any information by RW so, default 0 (write)
    digital_write(LCD_RW, 0);
    // now accessing byte by write2pins
    write2pins(byte, LCD_data);
    // pulse enable
    digital_write(LCD_EN, 1);
    delay_ms(1);
    digital_write(LCD_EN, 0);
    delay_ms(2);
}

// LCD_cmd this function is used only initialization purpose
void LCD_cmd(us32 byte)
{
    // RS LOW for command
    digital_write(LCD_RS, 0);
    // follow up to go RW and E
    write_LCD(byte);
}

void INIT_LCD()
{
    // set port direction for data pins (from LCD_data start, 11 pins total: 8 data + control bits up to EN)
    port_mode(LCD_data, 11);
    delay_ms(15);

    // Initialization sequence (HD44780)
    LCD_cmd(MODE_8_BIT_LINE1);
    delay_ms(4100);

    LCD_cmd(MODE_8_BIT_LINE1);
    delay_ms(100);

    LCD_cmd(MODE_8_BIT_LINE1);

    LCD_cmd(MODE_8_BIT_LINE2);

    LCD_cmd(CLR_DIS);            // clear display
    //LCD_cmd(DIS_ON_cur_blink);  // display on, cursor on, blink on
	  LCD_cmd(0x0C);
}

void charLCD(s8 ascii)
{
    // RS HIGH for data
    digital_write(LCD_RS, 1);
    write_LCD(ascii);
}

void strLCD(s8 *p)
{
    while (*p)
        charLCD(*p++);
}

int main()
{
	us32 n=0;
    INIT_LCD();
    strLCD("Vector");
	  while(n!=5)
		{
		LCD_cmd(0xc0);
	  strLCD("Institue");
		delay_ms(800);
		LCD_cmd(0xc0);
		strLCD("         ");			
			n++;
		}
    while (1) { /* loop forever */ }
}
