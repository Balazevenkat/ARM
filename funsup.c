#include "type.h"
#include <LPC21xx.h>
#include "fun_sup.h"
#include "delay.h"

void writebyte(u32 WORD,u32 BITPOSST,u32 BYTE)
{
	WORD=((WORD&~(0xff<<BITPOSST))|
	             (BYTE<<BITPOSST));
}
void write2port(u32 portNo,u32 BITPOSST,u32 BYTE)
{
	if(portNo == 0)
	{
		IOCLR0=0XFF<<BITPOSST;
		IOSET0=BYTE<<BITPOSST;
	}
	else if(portNo == 1)
	{
		IOCLR1=0XFF<<BITPOSST;
		IOSET1=BYTE<<BITPOSST;
	}
}