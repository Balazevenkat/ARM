/*. Flash an LED connected to any port line at the rate of 1 second for 10 times and stop. 
*/
#include <lpc21xx.h>
#include "delay.h"
#include "type.h"
main()
{
	u32 i=10;
	IODIR0|=0xffff<<8;
	while(i>0)
	{
	IOCLR0=0xffff<<8;
		delay_ms(1000);
	IOSET0=0xffff<<8;
 delay_ms(1000);
		i--;
	}
while(1); 
}
