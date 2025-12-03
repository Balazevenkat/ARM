//Store 5 numbers in an array, sum them, and show if sum’s LSB is active high (LED ON).
#include <LPC21xx.h>
#include <stdlib.h>
#include "type.h"
#include "delay.h"
u32 arr[5];
s32 sum=0;
void active_high(s32 num)
{
	IOCLR0=0xff<<8;
	IOSET0=num<<8;
	delay_ms(1000);
}
main()
{
	s32 i;
	IODIR0|=0xff<<8;
	for(i=0;i<5;i++)
	{ 
		arr[i]=rand()%50;
	}
	while(1)
	{
		for(i=0;i<5;i++)
		{
		active_high(arr[i]&1);
		}
	}
}