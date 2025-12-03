#include<stdlib.h>
#include<LPC21xx.h>
#include "type.h"
#include "delay.h"
#define DIR 8
int is_prime(int num)
{
	u32 i;
	if((num%2)==0)
	{
		return 0;
	}
	else
	{
		for(i=2;i<=num/2;i++)
		{
			if((num%i)==0)
			{
				return 0;
			}
		}
		return 1;
	}
}
int main()
{
	u32 arr[5],i,j;

	IODIR0|=(1<<DIR);
	while(1)
	{
	for(i=0;i<5;i++)
	{
		arr[i]=rand()%(30-20+1)+20;
		if(is_prime(arr[i]))
		{
			IOSET0=arr[i]<<DIR;
		//IOPIN0=(arr[i]<<DIR);
		delay_ms(200);
		}
		else
		{
			IOCLR0=arr[i]<<DIR;
			delay_ms(200);
		}
	}
  }
}
