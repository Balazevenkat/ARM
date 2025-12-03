#include <LPC21xx.h>
#include "tydef.h"
#include "time.h"
#define sw1 7
#define sw2 5
s32 main()
{
 s32 i,data=0;
 IODIR0|=255<<8;
while(1)
 {
   while(data<=255)
   {
     if(((IOPIN0>>sw1)&1)==0)
	 {
		 //while(((IOPIN0>>sw1)&1)==0)
		 //{
	   IOCLR0=255<<8;
	   IOSET0=(data^0XF0)<<8;
	   delay_ms(500);
		 data++;
		 //}
	 }
	 else if(((IOPIN0>>sw2)&1)==0)
	 {
		 data =255;
		 while(data>=0)
		 {
		 IOCLR0=255<<8;
	   IOSET0=(data^0XF0)<<8;
	   delay_ms(500);
			 data--;
		 }
	 }
	 else
	 {
		 data=1;
		 break;
   }
	 //while(1);
   }
 }
 }