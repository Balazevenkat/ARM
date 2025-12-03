#include<LPC21xx.h>
#include "LCD_defines.h"
#include "delay.h"
#include "type.h"

// pinsin port 1 16 - 19 row
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19
//FOR COLUM
#define col 20
s32 kpm[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};

void inti()
{
 IODIR1|=15<<ROW0;
}
s32 col_scan()
{
 s32 status; status = (((IOPIN1 >> col)&15)<15) ? 0: 1; return status;
}
s32 row_check()
{
  //check rows
  s32 r;
   for(r=0;r<=3;r++)
   {
        IOPIN1=((IOPIN1&~(15<<ROW0))|(~(1<<r)<<ROW0));
    //IOCLR1=15<<ROW0;
        //IOSET1=(1<<r)<<ROW0;
        //(~(1<<r)&0X0F)<<ROW0;
        if(col_scan()==0)
        {
        break;
        }
   }
	  IOCLR1=15<<ROW0;
   return r;
}
s32 col_check()
{
           u32 c;
           for(c=0;c<=3;c++)
           {
           if(((IOPIN1>>(col+c))&1)==0)
           {
           break;
           }
           }
           return c;
}
u32 keyscan()
{

u32 r,c,keyv;
//inti();
while(col_scan());
r=row_check();
c=col_check();
keyv=kpm[r][c];
return keyv;
}
s32 main()
{
 s32 key,cou=0,pos=0,dly=10000;
 INIZ();
 inti();
 strLCD("KEYPAD testing");
 while(1)
 {
 key=keyscan();
	 //LCD_cmd(0x80);
	 if(cou<10)
	 {
		 strLCD("enter passoword within 2 min");
		 while(dly)
		 {
			cou++;
		 dly--;
		 }
		 while(1)
		{
			LCD_cmd(0x1c);
			delay_ms(100);
		}
		while(1)
		{
			LCD_cmd(0x18);
			delay_ms(100);
		}
	 }
	 else
	 {
		 break;
	 }
	 
	 LCD_cmd(0xC0+pos);
	 LCD_int_DIS1(key);
	 pos++;
	 if(pos>15)
		 pos=0;
    while(col_scan()==0);
 }
   //while(1);
}