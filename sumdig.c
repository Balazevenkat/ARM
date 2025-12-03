/* Write an ECP to print the binary equivalent of sum of the digits for the given integer
on LEDS (4-Active High LEDS& 4-Active Low LEDS). */
#include <lpc21xx.h>
#include "def_dely.h"
#include "def_type1.h"
s32 sum=0;
main()
{
	s32 data=459;
	
	IODIR0|=255<<8;
	while(data!=0)
	{ 
		sum+=data%10;
		data/=10;
	}
	while(1)
	{
		/*IOCLR0=0XFF<<8;
		IOSET0=(sum^0xf0)<<8;
		delay_ms(200);*/
		IOCLR0=0x0f<<8;
				IOSET0=(sum&0x0f)<<8;
        delay_ms(400);				
				//active low 
				IOSET0=0x0f<<12;
    IOCLR0=(sum>>4 & 0x0f)<<12;
				delay_ms(400);
	}
}
	