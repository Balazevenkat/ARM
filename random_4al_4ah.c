#include <LPC21xx.h> 
#include "type.h"
#include "delay.h"
#include <stdlib.h>
u32 arr[10]; 
u32 sum=0; 
main() 
{ u32 i;
	IODIR0|=255<<8;
	for(i=0;i<10;i++) 
	{ arr[i]=rand()%256; }
	for(i=0;i<10;i++) 
	{
		sum+=arr[i];
		}
	 
			if(sum!=0)
			{
				IOCLR0=0x0f<<8;
				IOSET0=(sum)<<8;
				delay_ms(2000);
				IOSET0=0x0f<<12;
				IOCLR0=(sum >>4 & 0x0f)<<12;
			}
		
			for(i=0;i<10;i++) 
			{ //active high 
				IOCLR0=0x0f<<8;
				IOSET0=(arr[i]&0x0f)<<8;
        delay_ms(4000);				
				//active low 
				IOSET0=0x0f<<12;
    IOCLR0=(arr[i]>>4 & 0x0f)<<12;
				delay_ms(4000);
				
      }
		while(1);
}
/*
#include <LPC21xx.h>
#include "type.h"
#include "delay.h"
#include <stdlib.h>

u32 arr[10];
u32 sum=0;

int main()
{
    u32 i;

    // Set P0.8 to P0.15 as output
    IODIR0 |= (0xFF << 8);

    // Generate 10 random 8-bit numbers
    for(i = 0; i < 10; i++)
    {
        arr[i] = rand() % 256;  // Random 0–255
    }

    // Optional: sum
    for(i = 0; i < 10; i++)
    {
        sum += arr[i];
    }

    while(1)
    {
        for(i = 0; i < 10; i++)
        {
            // *********** ACTIVE HIGH (P0.8 - P0.11) for LOWER 4 BITS ***********
            IOCLR0 = (0x0F << 8);                  // Clear bits 8-11
            IOSET0 = ((arr[i] & 0x0F) << 8);       // Display lower nibble
            
            delay_ms(5000);

            // *********** ACTIVE LOW (P0.12 - P0.15) for UPPER 4 BITS ***********
            IOSET0 = (0x0F << 12);                 // Make all inactive high
            IOCLR0 = ((arr[i] >> 4) & 0x0F) << 12; // Activate upper nibble as active low

            delay_ms(5000);
        }
    }
}*/
