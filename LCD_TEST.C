#include <LPC21xx.h>
#include"time.h"
#include"type.h"
#define OUTPUT 1
#define CLR_DIS 0x01
#define DIS_OFF 0x80
#define DSP_ON_CUR_BLINK 0X0F
#define CUR_shif_RIGH 0x06
#define CUR_shif_left 0x07
//intinalize
#define MODE_8BIT_LINE1 0x30// it access the same as 0x03 but in 8bit (over all D0-D7)
#define MODE_8BIT_LINE2 0x38// same but line 2
//access
#define LCD_DATA 8
#define LCD_RS 16
#define LCD_RW 17
#define LCD_EB 18
void port_mode(u32 bit,u32 npin,u32 pindir)
{
                 if(OUTPUT==pindir)
                 {
                 IODIR0|=((1<<npin)-1)<<bit;
                 }
}
void digital_write(u32 data,u32 bit)
{
	if(bit)
    IOSET0 = 1 << data;
else
    IOCLR0 = 1 << data;

}
void write2_pins(u32 bit,u32 npin,u32 data)
{
  IOCLR0=((1<<npin)-1)<<bit;
  IOSET0=data<<bit;// good way (data&0xff)<<bit
}
void write_LCD(u32 byte)
{
	//any LCD rw is 0 becaue we not take any input form LCD
	digital_write(LCD_RW,0);
	//pins access to know the data on d0-d7
	write2_pins(LCD_DATA,8,byte);
	//provide hig to low pulse for latching
	digital_write(LCD_EB,1);
	delay_us(1);
		digital_write(LCD_EB,0);
	delay_ms(2);
}

void cmd_LCD(u32 byte)
{
	//intinally 16 were Low L
	digital_write(LCD_RS,0);
	//to write into LCD
	write_LCD(byte);
}
	

void INIT_cmd()
{
  port_mode(LCD_DATA,8,OUTPUT);
	IODIR0 |= (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_EB);

	delay_ms(15);
	cmd_LCD(MODE_8BIT_LINE1);
	delay_ms(4100);
	cmd_LCD(MODE_8BIT_LINE1);
	delay_ms(100);
	cmd_LCD(MODE_8BIT_LINE1);
	cmd_LCD(MODE_8BIT_LINE2);
	cmd_LCD(DSP_ON_CUR_BLINK);
	cmd_LCD(CLR_DIS);
	cmd_LCD(CUR_shif_RIGH);//also know entry mode
}
void char_LCD(u8 ascii)
{
	digital_write(LCD_RS,1);
	write_LCD(ascii);
}
void strLCD(s8*p)
{
	while(*p)
	char_LCD(*p++);
}
int main()
{
	INIT_cmd();
	strLCD("HELLO");
	while(1);
}