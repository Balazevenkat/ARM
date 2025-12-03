/*Write an ECP to display below mentioned patterns on 8-led’s (4-active high led’s and
4-active low led’s)
a. Switch ON one by one led from left to right at the rate of 1 second
b. Switch ON one by one led from right to left at the rate of 1 second*/
#include <lpc21xx.h>
#include "delay.h"
#include "type.h"
s32 pattern[]={0x81,0x42,0x24,0x18,0x24,0x42,0x81};
main()
{
	u32 i;
	IODIR0|=255<<8;
	
while(1)
{	
	for(i=0;i<8;i++)
	{
		IOCLR0=255<<8;
		IOSET0=(pattern[i]^0xf0)<<8;
		delay_ms(2000);
		//active high
		/*IOCLR0=0x0f<<8;
		IOSET0=(pattern[i]&0x0f)<<8;
		delay_ms(2000);
		
		//active low
		IOSET0=0x0f<<12;
		IOCLR0=((pattern[i]>>4)^0xf0)<<12;
		delay_ms(2000);*/
	}
}
}