#include "pin_connect_block.h"
#include "PIN_FUN_DEF.h"

int main()
{
 //cfg p0.0 for function 4
 cfgportpinfunc(0,0,RSVD_0_0);
 //cfg p0.0 for function 3
 cfgportpinfunc(0,0,PWM1_0_0);
 //cfg p0.0 for function 2
 cfgportpinfunc(0,0,TXDO_0_0);
 //cfg p0.0 for function 1
 cfgportpinfunc(0,0,GPIO_0_0);
 while(1);

}
