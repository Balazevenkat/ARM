//init system.c
#include "kpm.h"
#include "lcd.h"
#include "rtc.h"
void init_system()
{
	Init_LCD();
	Init_KPM();
	RTC_Init();
}