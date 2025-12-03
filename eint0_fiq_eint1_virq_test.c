#include<LPC21xx.h>
#include "types.h"
#include "pin_functions_defines.h"
#include "pin_connect_block.h"

#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16
#define EINT0_PIN_0_1 PIN_FUNC4

#define EINT1_VIC_CHNO 15
#define EINT1_STATUS_LED 17
#define EINT1_PIN_0_3 PIN_FUNC4

#define EINT2_VIC_CHNO 16
#define EINT2_STATUS_LED 18
#define EINT2_PIN_0_7 PIN_FUNC4

void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
void eint2_isr(void) __irq;
u32 gCount;
main(){
    //cfg EINT0,EINT1,EINT2 status led pin as gpio output
    IODIR1 |= 1<<EINT0_STATUS_LED | 1<<EINT1_STATUS_LED | 1<<EINT2_STATUS_LED;

    //cfg p0.1 pin as EINT0 input pin
    CfgPortPinFunc(0,1,EINT0_PIN_0_1);
    //cfg p0.3 pin as EINT1 input pin
    CfgPortPinFunc(0,3,EINT1_PIN_0_3);
    //cfg p0.7 pin as EINT2 input pin
    CfgPortPinFunc(0,7,EINT2_PIN_0_7);

    //cfg VIC peripheral for EINT0,EINT1,EINT2
    //cfg EINT0 is fiq type,
    //cfg EINT1 & EINT2 as irq type, def all are anyway irq
    VICIntSelect= 1<<EINT0_VIC_CHNO;
    //required to manipulate startup.s for fiq as follows
    //comment below line in startup.s
    // ;FIQ_Handler    B     FIQ_Handler
    // & add the 2 following lines in startup.s
    //IMPORT eint0_fiq_isr
    //FIQ_Handler    B      eint0_fiq_isr

    //Enable EINT0,EINT1,EINT2 via VIC
    VICIntEnable = 1<<EINT1_VIC_CHNO | 1<<EINT0_VIC_CHNO | 1<<EINT2_VIC_CHNO;

    //cfg EINT1 as v.irq,highest priority 0
    VICVectCntl0 = (1<<5) | EINT1_VIC_CHNO;

    //load eint1_isr address in hardware lut sfr for nv.irq
    VICVectAddr0 = (u32)eint1_virq_isr;

    //cfg EINT2 as nv.irq
    //load eint2_nvirq_isr addr in hardware lut sfr for nv.irq
    VICDefVectAddr = (u32)eint2_nvirq_isr;

    //cfg External Interrupt peripheral
    //Enable EINT0,EINT1,EINT2 ,def all eint's are any enable
    //EXTINT = 0
    //cfg EINT0,EINT1,EINT2 for edge triggering
    EXTMODE = 1<<2 | 1<<1 | 1<<0;
    //cfg EINT0,EINT1,EINT2 for falling edge triggering,def FE anyway
    //EXTPOLAR = 0;
    //enter regular operations
    while(1){
        gCount++;
    }
}

void eint0_isr(void) __irq{
    //eint0 isr user activity begins
    //toggle EINT0 status led upon interrupt fired/raised
    IOPIN1 ^= 1<<EINT0_STATUS_LED;
    //eint0 isr user activity ends
    //clear EINT0 status in External Interrupt Peripheral 
    EXTINT = 1<<0;
    //clear EINT0 status in VIC peripheral
    // VICVectAddr = 0;
}

void eint1_isr(void) __irq{
    //eint1 isr user activity begins
    //toggle EINT1 status led upon interrupt fired/raised
    IOPIN1 ^= 1<<EINT1_STATUS_LED;
    //eint1 isr user activity ends
    //clear EINT1 status in External Interrupt Peripheral 
    EXTINT = 1<<1;
    //clear EINT1 status in VIC peripheral
    VICVectAddr = 0;
}

void eint2_isr(void) __irq{
    //eint2 isr user activity begins
    //toggle EINT2 status led upon interrupt fired/raised
    IOPIN1 ^= 1<<EINT2_STATUS_LED;
    //eint2 isr user activity ends
    //clear EINT2 status in External Interrupt Peripheral 
    EXTINT = 1<<2;
    //clear EINT2 status in VIC peripheral
    VICVectAddr = 0;
}