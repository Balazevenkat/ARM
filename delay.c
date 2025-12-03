#include "tydef.h"
void delay_ms(u32 del_ms)
{
	del_ms*=12000;
	while(del_ms--);
}

void delay_s(u32 del_s)
{
	del_s*=12000000;
	while(del_s--);
}
void delay_us(u32 del_us)
{
	del_us*=12;
	while(del_us--);
}