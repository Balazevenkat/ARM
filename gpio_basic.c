#include <LPC21xx.h>
#include "delay.h"
#include "type.h"
#define PIN 7;
main()
{
	/*IODIR0|=1<<PIN;
	while(1)
	{
		//IF US3E IOPIN0 TO TOGGLE SAME REFLECT TO THE ENTRIE IOSET PIN 
		IOPIN0^=1<<PIN;
	}*/
	
	/*IODIR0|=1<<PIN;
	while(1)
	{
	// IT REFLECT WHOLE PATICULAR PIN IN SET CLR IOPIN TOO BECAUSE WE SET DIRCTION
		IOCLR0=1<<PIN;
		delay_ms(200);
	IOSET0=1<<PIN;
	delay_ms(300);
	}*/

	while(1)
	{
		// ONLY REFLECT ON THE SET PIN CLR SFRS IN GPIO
	IOCLR0=1<<PIN;
	delay_ms(200);
	IOSET0=1<<PIN;
	delay_ms(300);
	}
}