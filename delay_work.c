#include "delay.h"
void delay_ms( int del_ms)
{
  del_ms*=12000;
  while(del_ms--);
}
void delay_s(unsigned int del_s)
{
	del_s*=120000;
}