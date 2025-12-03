#include <LPC21xx.h>
#include "delay.h"
#include "arduino_define.h"
#include "type.h"
#include "arduino1_fun.h"
 void protmode(u32 portNo,u32 pindir)
 {
	 if(portNo==input)
	 {
		 IODIR0|=1<<pindir;
	 }
	 else if(portNo==output)
	 {
		 if(pindir>=32 && pindir<=47 )
		 {
			 IODIR1|=1<<pindir;
		 }
	 }
 }