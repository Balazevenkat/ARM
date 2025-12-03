#include <LPC21xx.h>
#include "delay.h"
#define OPIN 7
#define IPIN 5
int main()
{
	IODIR0|=1<<OPIN;
	/*while(1)
	{
		if(((IOPIN0>>IPIN)&1)==1)// IOPIN ALWAY 1 SO IN IOSET ON WITH RESPECT TO OPIN 
		{
		IOSET0=1<<OPIN;
		delay_ms(100);
		}			else{
		IOCLR0=1<<OPIN;
		delay_ms(100);
		}
	}*/
	while(1)
	{
		if(((IOPIN0>>IPIN)&1) == 1)
		{
			IOPIN0|=1<<OPIN;
			delay_ms(100);
		}
		else
		{
			IOPIN0&=~(1<<OPIN);
		}
	}
}
