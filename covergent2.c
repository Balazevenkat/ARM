#include<LPC21xx.h>
#include"type.h"
#include"delay.h"
#define DIR_AL 8
const u32 pattern[]={0Xff,0X81,0X42,0X24,0X18,0X24,0X42,0X81};
main()
{
	u32 i;
	IODIR0|=255<<DIR_AL;
	delay_ms(200);
	while(1)
	{
		for( i=0;i<8;i++)
		{
		IOSET0=255<<DIR_AL;
			delay_ms(1000);
			IOCLR0=pattern[i]<<DIR_AL;
			delay_ms(100*i);
			//IOPIN0=(IOPIN0&~(255<<DIR_AL)|(pattern[i]<<DIR_AL));
			delay_ms(300);
		}
	}
}