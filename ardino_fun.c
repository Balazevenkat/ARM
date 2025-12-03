#include <lpc21xx.h>
#include "ardino_fun.h"
#include "ardino_def.h"
#include "type.h"
void portmode(s32 pinstart,s32 npins,u32 pindir)
{
 if(pinstart<32)
 {
   if(pindir==OUTPUT)
   {
   IODIR0|=(((1<<npins)-1)<<pinstart);
   }
   else
   {
   IODIR0&=~(((1<<npins)-1)<<pinstart);
   }
 }
   else if (pinstart >= 32 && pinstart <= 47)
  {
   if(pindir==OUTPUT)
   {
     IODIR1|=(((1<<npins)-1)<< pinstart-16);
   }
   else
   {
    IODIR1&=~(((1<<npins)-1)<<pinstart-16);
   }
   }
  }
void write2pins(s32 pinstart,s32 npins,u32 data)
	{
		if(pinstart<32)
		{
			IOCLR0=(((1<<npins)-1)<<pinstart);
			IOSET0=(data<<pinstart);
			//IOPIN0=(IOPIN0&~(((1<<npins)-1)<<pinstart)|(data<<pinstart));
		}
		else
		{
			if(pinstart>=32 && pinstart<=47)
		{
			IOCLR0=(((1<<npins)-1)<<(pinstart-16));
			IOSET0=(data<<(pinstart-16));
		}
	}
}
	
	
 