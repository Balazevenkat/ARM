/*Write an ECP to print the binary equivalent of odd digits in a given integer on 8 LEDS
@ 5 seconds. */
#include <lpc21xx.h>
#include "delay.h"
#include "type.h"
main()
{
	u32 data=4536,num;
	IODIR0|=255<<8;
	
	while(1)
		{	while(data!=0)
	{
		num=data%10;
		if(num%2!=0)
		{
			IOCLR0=0XFF<<8;
			IOSET0=num<<8;
			delay_ms(2000);
		}
		data/=10;
	}
}
}