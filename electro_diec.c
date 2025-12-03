#include <lpc21xx.h>
#include "delay.h"
#include "type.h"
#include "ardino_def.h"
#include "ardino_fun.h"
#define cfg_7seg 8
const s32 segLUT[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
main()
{
	u32 i;
	portmode(cfg_7seg,8,OUTPUT);
	while(1){
	for(i=0;i<10;i++)
	{
		write2pins(cfg_7seg,8,segLUT[i]);
		delay_ms(500);
	}
}
}