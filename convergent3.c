
//using functions
#include <LPC21xx.h>
#include "type.h"
#include "delay.h"
#include "fun_sup.h"
#define LED_AL 8
u32 pattern[]={0xff,0x81,0x42,0x24,0x18,0x24,0x42,0x81};//act as bytes acess in this porgram
main()
{
	u32 i;
	writebyte(IODIR0,LED_AL,0xff);
	while(1)
	{
		for(i=0;i<=7;i++)
		{
			write2port(1,LED_AL,pattern[i]);
			if(i==0)
			{
				delay_ms(2000);
			}
			else
			{
				delay_ms(100*i);
			}
		}
	}
}