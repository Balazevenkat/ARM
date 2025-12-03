/*Write an ECP to print the binary equivalent of power of 2 numbers with in the range of
0-255 @ 5 seconds*/
/*#include <lpc21xx.h>
#include "delay.h"
#include "type.h"

main()
{
	s32 i;
	IODIR0|=255<<8;
	while(1)
	{
		s32 pow=1;
	for(i=0;i<8;i++)
	{
		
		IOCLR0=0xff<<8;
		IOSET0=(pow^0xf0)<<8;
		delay_ms(5000);
	  pow= pow*2;
	}
  }
}*/
//both are correct but below is up 8 all leds are active high later active low 
//above code form starting 4 bits are active high soo,first only it decides active high or active low
#include <lpc21xx.h>
#include "delay.h"
#include "type.h"

int main()
{
    s32 pow;
    int i;

    IODIR0 |= 0xFF << 8;  // P0.8-P0.15 as output

    while(1)
    {
        pow = 1;  // Start with 2^0

        for(i = 0; i < 8; i++)
        {
            IOCLR0 = 0xFF << 8;  // Clear all LEDs first

            if(i < 4) // Lower 4 bits ? Active HIGH
            {
                IOSET0 = pow << 8;      // Turn ON lower 4 LEDs
            }
            else      // Upper 4 bits ? Active LOW
            {
                IOSET0 = (~pow & 0xF0) << 8; // Invert upper 4 bits
            }

            delay_ms(5000);
            pow = pow * 2;  // Next power of 2
        }
    }
}

		