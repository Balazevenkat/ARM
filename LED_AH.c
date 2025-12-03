#include<LPC21xx.h>
#include"delay.h"
#include"type.h"
#define LED_AH_0_8 8
main()
{
	IODIR0|=1<<LED_AH_0_8;
	while(1)
	{
		IOCLR0=1<<LED_AH_0_8;
		delay_ms(400);
		IOSET0=1<<LED_AH_0_8;
		delay_ms(400);
	}
}
	