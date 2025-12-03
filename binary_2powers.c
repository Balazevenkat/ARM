#include <LPC21xx.h>
#include "delay.h"
#include "type.h"

/*binary_of_powerof2.c
//#include <LPC21xx.h>
//#include "types.h"

#define OPINS     8 // @p0.8 to p0.15 pin
#define TRIG_PIN  0 // @p0.0
main()
{
	u32 i;
	//cfg p0.8 to p0.15 pins as gpio out
	IODIR0 |= 255<<OPINS;
	while(1)
	{
		for(i=0;i<=7;)
		{
		 if(((IOPIN0>>TRIG_PIN)&1)==0)
		 {
      			 
	    IOPIN0=((IOPIN0&~(255<<OPINS))|
			       ((1<<i)<<OPINS));
			 delay_ms(200);
			while(((IOPIN0>>TRIG_PIN)&1)==0);
			i++; 
		 }
	 }		 
  }
}
*/
#define DIR_0_8 8
main()
{
	u32 i,tem=1;
	IODIR0|=0xff<<DIR_0_8;
	
		for(i=DIR_0_8;i<0x7f;i++)//i<255 means 2 to 128 binary range in ioset 
		{
			i=tem*2;
			tem=i;
		IOCLR0=0xff<<DIR_0_8;
		delay_ms(200);
		IOSET0=tem<<DIR_0_8;
		delay_ms(200);
			
		}
		while(1);
	}
