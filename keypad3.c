#include <LPC21xx.h>
#include"delay.h"
#include"types.h"
//LCD access macro's
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

//KEY_pad acess macro
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

#define col 20
s8  KPM[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};



void port_mode(u32 bit,u32 npins)
{
	IODIR0|=((1>>npins)-1)<<bit;
}
void digital_write(s32 data,s32 bit)
{
	bit?(IOSET0=1<<data):(IOCLR0=1<<data);
}
void write2pins(s32 star_bit,s32 data)
{
	IOCLR0=0xFF<<star_bit;
	IOSET0=(data&0xff)<<star_bit;
}

void write_LCD(u32 byte)
{
	digital_write(LCD_RW,0);
	write2pins(LCD_data,byte);
	digital_write(LCD_EN ,1);
	delay_ms(1);
	digital_write(LCD_EN,0);
	delay_ms(2);
}
void LCD_cmd(u32 byte)
{
	digital_write(LCD_RS,0);// rs was passing 0 
	write_LCD(byte);
}
void char_LCD(s8 ascii)
{
	digital_write(LCD_RS,1);//rs need pass data so,high
	write_LCD(ascii);
}
void strLCD(s8 *p)
{
	while(*p)
	{
	char_LCD(*p);
	p++;
	}
}
void int_to_ascii(s32 n)
{
	s8 dig[10],ch=0;
	s32 val,i=0;
	if(n==0)
	{
		char_LCD(ch);
	}
	while(n>0)
	{
		val=n%10;
		dig[i]=val+48;
		i++;
		n=n/10;
	}
	for(--i;i>=0;i--)
	{
		char_LCD(dig[i]);
	}
	
}
void INZI()
{
	port_mode(LCD_data,11);
	delay_ms(15);
	LCD_cmd(MODE_8_BIT_LINE1);
	delay_ms(4100);
	LCD_cmd(MODE_8_BIT_LINE1);
	delay_ms(100);
	LCD_cmd(MODE_8_BIT_LINE1);
	LCD_cmd(MODE_8_BIT_LINE2);
	LCD_cmd(DIS_ON_CUR_OFF);
	LCD_cmd(0x06);
}
void inti_kpm()
{
	IODIR1|=15<<ROW0;   // Rows = output
  //  IOCLR1  = (0x0F << ROW0); 
}
s32 col_scan()
{
	s32 status;
	status = (((IOPIN1 >> col) & 15) < 15) ? 0 : 1;

	return status;
}

s32 row_check()
{
	s32 r=0;
	for(r=0;r<=3;r++)
	{
		//IOPIN1=((IOPIN1)&~(15<<ROW0))|(~(1<<r)<<ROW0);
		IOCLR1=15<<ROW0;
		IOSET1=(~(1<<r)&0x0f)<<ROW0;
		if(col_scan()==0)
		{
			break;
		}
	}
	IOCLR1  = (0x0F << ROW0);
	return r;
}
u32 col_check()
{
	s32 i=0;
	for(i=0;i<=3;i++)
	{
		if(((IOPIN1>>(col+i))&1)==0)
		{
			break;
		}
	}
	return i;
}
s8 key_scan()
{
	u32 r,c;
	s8 keyv;
	//inti_kpm();
	while(col_scan());
	r=row_check();
	c=col_check();
	keyv=KPM[r][c];
	return keyv;
}
/*s32 main()
{
	s32 key;
	u8 pos=0;
	INZI();
	strLCD("keypad");
	delay_ms(900);
	LCD_cmd(0x80);
	strLCD("Password:");
	inti();
	while(1)
	{
		key=key_scan();
		LCD_cmd(0xc0+pos);
		//strLCD(" ");
		//LCD_cmd(0xc0);
		if(pos>15)
			pos=0;
		int_to_ascii(key);
		while(col_scan()==0);
	}
}*/
