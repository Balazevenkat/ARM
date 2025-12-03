/*Create a display on 8 LED’s (4-active high and 4-active low) connected to port0 (0.0-
0.7) in the given pattern.
a. First all LEDs should be OFF, at 1st second, LED 0 and LED 7 (P0.0 and
P0.7) should be ON
b. At 2nd second, LED 1 and LED 6 (P0.1 and P0.6) should be ON
c. At 3rd second, LED 2 and LED 5 (P0.2 and P0.5) should be ON
d. At 4th second, LED 3 and LED 4 (P0.3 and P0.4) should be ON
e. Repeat above pattern for 5 times and stop the process.*/
#include <lpc21xx.h>
#include "delay.h"
#include "type.h"
s32 con[]={0x00,0xff};
s32 pattern[]={0x81,0x42,0x24,0x18,0x24,0x42,0x81};
main()
{
	u32 i,t=5;
	IODIR0|=255<<8;
	while(t>0)
	{
	for(i=0;i<2;i++)
		{
			IOCLR0=0xff<<8;
		IOSET0=((con[i]^0xf0)<<8);
		delay_ms(1000);
		}
	for(i=0;i<8;i++)
	{
		IOCLR0=0xff<<8;
		IOSET0=((pattern[i]^0xf0)<<8);
		delay_ms(500);
	}
	t--;
  }
	while(1);
}