#include<LPC21xx.h>
#include "time.h"
#include "tydef.h"
s32 shig=0;
s32 main()
{
	s32 data=459,num,hig=0;
	IODIR0|=255<<8;
	while(data>0)
	{ 
		num=data%10;
		if(num>hig)
		{
			shig=hig;
			hig=num;
		}
		if(hig>num && shig<num)
		{
			shig=num;
		}
		data/=10;
	}
	IOCLR0=0XFF<<8;
	IOSET0=(shig^0xf0)<<8;
	while(1);
}
		

