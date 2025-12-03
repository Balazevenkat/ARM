#include <LPC21xx.h>
#include "delay.h"
#include "type.h"
#define AL 12
#define AH 8
u32 pattern[]={0xff,0x81,0x42,0x24,0x18,0x24,0x42,0x81};

main()
{
	u32 i;
  IODIR0|=0xff<<8;

  while(1)
  {
    for(i=0;i<=4;i++)
	{
	  delay_ms(100);
	  IOCLR0=0x0f<<AH;
	  IOSET0=pattern[i]<<AH;
	}
	for(i=4;i<8;i++)
	{
	  delay_ms(100);
	  IOSET0=0x0f<<AL;
	  IOCLR0=pattern[i]<<AL;
	}

}
}
	