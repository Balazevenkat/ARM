/*Write an ECP to display binary equivalent of 0-255 on 8-leds (4-active high led’s and
4-active low led’s)*/
#include <LPC21xx.h>
#include "delay.h"
#include "type.h"
main()
{
	u32 i;
	IODIR0|=255<<8;
	while(1)
	{
	for(i=0;i<=255;i++)
	{
		IOCLR0=255<<8;
		IOSET0=(i^0xf0)<<8;
		delay_ms(900);
	}
  }
}