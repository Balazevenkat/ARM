#include<LPC21xx.h>
#include"type.h"
#include"delay.h"
/*
const u32 pattern[]={0Xff,0X81,0X42,0X24,0X18,0X24,0X42,0X81};
main()
{
	u32 i;
	IODIR0|=255<<8;
	delay_ms(200);
	while(1)
	{
		for( i=0;i<8;i++)
		{
		IOSET0=255<<8;
			delay_ms(1000);
			IOCLR0=pattern[i]<<8;
			delay_ms(100*i);
		}
	}
}
  | LED wiring      | Correct order                 |
| --------------- | ----------------------------- |
| **Active HIGH** | `IOSET0` ? ON, `IOCLR0` ? OFF |
| **Active LOW**  | `IOCLR0` ? ON, `IOSET0` ? OFF |
1(IOCLR0 = 255 << 8;           // Make all LOW (turn OFF for active low) 
delay_ms(1000);
IOSET0 = pattern[i] << 8;    // Turn ON selected LEDs
delay_ms(100*i); )  and  2 (IOSET0=pattern[i]<<8; 
			delay_ms(1000);
			IOCLR0=255<<8;
			delay_ms(100*i);) in 1 active high and 2 active LOW 
*/
const u32 pattern[]={0Xff,0X81,0X42,0X24,0X18,0X24,0X42,0X81};
main()
{
	u32 i;
	IODIR0|=255<<8;
	delay_ms(200);
	while(1)
	{
		for( i=0;i<8;i++)
		{
		IOSET0=pattern[i]<<8;
			delay_ms(1000);
			IOCLR0=255<<8;
			delay_ms(100*i);
		}
	}
}