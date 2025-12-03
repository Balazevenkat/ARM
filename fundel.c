#include "delay.h"
void delay_ms(unsigned int del_ms){
  del_ms*=12000;
  while(del_ms--);
}
