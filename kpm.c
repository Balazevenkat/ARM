//kpm.c
#include<LPC21xx.h>
#include"types.h"
#include"lcd.h"
#include"kpm_defines.h"

u32 kpmLUT[4][4] = {{'1','2','3','B'},
    {'4','5','6','+'},
    {'7','8','9','-'},
    {'E','0','*','/'}};
/*u32 kpmLUT[4][4] = {{'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','E','D'}};	*/

void Init_KPM(void)
{
 IODIR1|=15<<ROW0;
 }

u32 Colscan(void)
 {
  u32 status;
  status=(((IOPIN1>>COL0)&15)<15)?0:1;
  return status;
  }

u32 Rowcheck(void)
{
 u32 r;
 for(r=0;r<=3;r++)
 {
   IOPIN1=((IOPIN1&~(15<<ROW0))|(~(1<<r)<<ROW0));
   if(Colscan()==0)
   {
    break;
	}
 }
 IOCLR1=15<<ROW0;
 return r;
 }
u32 Colcheck(void)
{
  u32 c;
  for(c=0;c<=3;c++)
  {
   if(((IOPIN1>>(COL0+c))&1)==0)
   {
     break;
	 }
	 }
	 return c;
	 }
u32 Keyscan(void)
{
 u32 r,c,keyV;
  Init_KPM();
  while(Colscan());
  r=Rowcheck();
  c=Colcheck();
  keyV=kpmLUT[r][c];
  return keyV;
  }
u32 get_digit()
{
    u32 k;

    while (1)
    {
        k = Keyscan();

        if (k >= '0' && k <= '9')     // only digits allowed
        {
            CharLCD(k);

            while (Colscan() == 0);  // wait until key release

            return k;
        }
    }
}
u32 get_key()
{
    u32 k;

    // wait until NO key is pressed
    while(Keyscan() != 0);

    // wait until a key IS pressed
    do {
        k = Keyscan();
    } while(k == 0);

    // wait until user releases key
    while(Keyscan() != 0);

    return k;
}
u32 get_two_digit_value()
{
    char buf[3] = {0};
    int i = 0;
    char key;

    CmdLCD(0xC0);

    while (1)
    {
        key = Keyscan();

        if (key >= '0' && key <= '9')   // Digit pressed
        {
            if (i < 2)
            {
                buf[i++] = key;
                CharLCD(key);
            }
        }
        else if (key == 'B')           // Backspace
        {
            if (i > 0)
            {
                i--;
                buf[i] = '\0';

                // Move cursor back and erase
                CmdLCD(0x10);  // Cursor left
                CharLCD(' ');  // Replace with blank
                CmdLCD(0x10);  // Move back again
            }
        }

        if (i == 2)   // Two digits entered
            break;

        while (Colscan() == 0);  // Wait for key release
    }

    return (buf[0] - '0') * 10 + (buf[1] - '0');
}

