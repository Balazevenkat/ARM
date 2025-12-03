#include <LPC21xx.h>
#include <stdlib.h>
#include "tydef.h"
#include "time.h"
s32 is_prime(s32 num)
{
	s32 data;
	if(num==2)
	{
		return 1;
	}
	else if (((num%2)==0))
	{
		return 0;
	}
	
	//data=((num%2)==0)?num+1:num;
	for(data=3;data<=(num/2);data+=2)
	{
		if((num%data)==0)
		{
			return 0;
		}
	}
	return 1;
}
s32 main()
{
s32 arr[10],i;
IODIR0|=0XFF<<8;
for(i=0;i<10;i++)
{
 arr[i]=rand()%(50-2)+2;
}
while(1)
{
// while(i!=10)
 for(i=0;i<10;i++)
	{
	 if(is_prime(arr[i]))
	{
  IOCLR0=0XFF<<8;
  IOSET0=(arr[i]^0XF0)<<8;
  delay_ms(2000);
	}
 }
}
}

