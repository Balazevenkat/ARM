#include <LPC21xx.h>
#include"time.h"
#include"tydef.h"
#define readbit(word,bit) ((word>>bit)&1)
#define SW_AL_AH 16
#define SW1_AL_AH 7
s32 pattern[]={0xFF,0x81,0x42,0x24,0x18};

s32 main()
{
 us32 i;
 IODIR0|=0xFF<<8;
 while(1)
 {
//  if((readbit(IOPIN0,SW_AL_AH))==0)
    if(((IOPIN0>>16)&1)==0)
	 {
   IOCLR0=0XFF<<8;
   IOSET0=(pattern[1]^0xf0)<<8;
		delay_ms(1000);
   }
	if((readbit(IOPIN0,SW1_AL_AH))==0)
  {
   IOCLR0=0XFF<<8;
   IOSET0=(pattern[2]^0xf0)<<8;
		delay_ms(1000);
   }
   }
}   