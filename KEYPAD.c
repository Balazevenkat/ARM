#include<lpc21xx.h>
#include"time.h"
#include"type.h"
#include"LCD_defines.h"
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

#define col 20
u32 keyv;
u32  KPM[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
void inti_kpm()
{
	// first we need to acces the iodir for the row and col
	IODIR1|=15<<ROW0;//<0x0f<16
}
u32 col_scan()
{
	u32 status;
	status=(((IOPIN1>>20)&15)<<15)?0:1;//
	return status;
}
s32 row_check()
{
	s32 r;
	for(r=0;r<=3;r++)
	{
		IOPIN1=((IOPIN1)&~(15<<ROW0))|(~(1<<r)<<ROW0);
	
	if((col_scan())==0)
	{
		break;
	}
  }
	IOCLR1=15<<r;//when switch relaes the re intilziing the position 
	return r;
}
u32 col_check()
{
	s32 i=0;
	for(i=0;i<=3;i++)
	{
		if(((IOPIN1>>(col+i))&1)==0)
		{
			break;
		}
	}
	return i;
}
u32 key_scan()
{
	u32 r,c,keyv;
	inti_kpm();
	while(col_scan());
	r=row_check();
	c=col_check();
	keyv=KPM[r][c];
	return keyv;
}
s32 main()
{

	INIZ();
	inti_kpm();
	LCD_cmd(0x80);
	strLCD("KPM test");
	while(1)
	{
		u32 key;
		key=key_scan();
		LCD_cmd(0xc0);
		strLCD("  ");
		LCD_int_DIS(keyv);
    while((col_scan())==0);
	}
}