/*Write an ECP to print the binary equivalent of product of the digits for the given
integer on LEDS (4-Active High LEDS& 4-Active Low LEDS).
Note: if the product is >255, Switch on alternate LEDS. 
akhil chepina data^oxfo follow iyethe output ostha dii but delay apply kadhu same with mana chesii AL AH kuda 
*/
#include<lpc21xx.h>
#include "delay.h"
#include "type.h"
#include "ardino_def.h"
#include "ardino_fun.h"
#define pinstart 8
s32 pro=1;

main()
{
	s32 data=66;
 u32 num;
 portmode(pinstart,8,OUTPUT);
 //while(1)
 //{
  //write2pins(pinstart,8,data);

	 while(data>0)
	 {
		 num=data%10;
		 pro*=num;
		 data/=10;
	 }
	 if(pro>255)
	 {
	 IOCLR0=255<<8;
  IOSET0=(0xaa^0xf0)<<8;
	 }else
	 {
	 IOCLR0=255<<8;
  IOSET0=(pro^0x0f)<<8;
	 }
 
/*{
  u32 pow=1,i;
  for(i=0;i<8;i++)
  {
	IOCLR0=(0xff)<<8;
	IOSET0=pow<<8;
	pow*=2;
		delay_ms(500);
   }
   }*/
 while(1);
	//IOCLR0=255<<8; if we keep this blinks withoudelay
	 //delay_ms(4000);
		//active hifh		
	/* IOSET0=(data&0x0f)<<8;
        delay_ms(400);				
				//active low 
				IOSET0=0x0f<<12;
    IOCLR0=(data>>4 & 0x0f)<<12;
				delay_ms(400);	 */
  }
  
 