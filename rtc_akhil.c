//rtc main.c
#include <LPC21xx.h>
#include<string.h>
#include "rtc.h"
#include "lcd.h"
#include "types.h"
#include "delay.h"
#include "pin_connect_block.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "arduino.h"
#include "init_system.h"
#define EINT_SW 1
#define EINT0_PIN_0_1 3
#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16
u32 present,start,stop;
u32 starthour=00,startmin=0;
u32 stophour=00,stopmin=0;
//#define ENTRY 0
// functions

int is_digit(char dig){//'a'
    if(dig>='0' && dig<='9') return 1;
    return 0;
}
int my_atoi(char *str){
    int i=0,sign=1,decimal=0;
    if(str[i]=='-'||str[i]=='+'){
        if(str[i]=='-'){
            sign=-1;
        }
        i++;
    }
    while(is_digit(str[i])){
        decimal = decimal * 10 + (str[i]-'0');
        i++;                                
    }                                         
    return decimal*sign;
}
//



s8 password[]="12345",curpass[10],newpass[10];

u32 key,j=0;

s32 hour,min,sec,date,month,year,day,temp;
/*void default_time()
{
	SetRTCTimeInfo(14,00,00);
	SetRTCDateInfo(01,12,2025);
	SetRTCDay(4);
	return;
}*/
void display_title()
{
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("TIME GUARD");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("ACCESS SHIELD");
	delay_ms(500);
	CmdLCD(CLEAR_LCD);
}
void display_RTC()
{ 
	  GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
			
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
	
	  GetRTCDay(&day);
		DisplayRTCDay(day);
	  delay_ms(300);
}
u32 validtime()
{
     
	GetRTCTimeInfo(&hour,&min,&sec);
			present=hour*60+min;
			 start=starthour*60+startmin;
			if(present>=start&&present<=stop)
			{
			  CmdLCD(CLEAR_LCD);
			  CmdLCD(GOTO_LINE1_POS0);
			  StrLCD("WITHIN TIME");
			  CmdLCD(GOTO_LINE2_POS0);
			  StrLCD("ACCESS GRANTED");
			  delay_ms(1000);
				CmdLCD(CLEAR_LCD);
				return 1;
			  }
			  else
			  {
			  CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("NOT IN TIME");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("ACCESS DENIED");
				delay_ms(1000);
				CmdLCD(CLEAR_LCD);
				return 0;
				}
			}
void changestartandstoptime()
{
{
    s8 str[4];
    // GET START HOUR
    CmdLCD(CLEAR_LCD);
    StrLCD("START HOURS");
    for(temp = 0; temp < 2; temp++)
    {
        key = Keyscan();
        str[temp] = key;
        CmdLCD(GOTO_LINE2_POS0 + temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan() == 0);
    }
    str[temp] = '\0';
    starthour = my_atoi(str);
    // GET START MINUTE
    CmdLCD(CLEAR_LCD);
    StrLCD("START MINUTES");
    for(temp = 0; temp < 2; temp++)
    {
        key = Keyscan();
        str[temp] = key;
        CmdLCD(GOTO_LINE2_POS0 + temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan() == 0);
    }
    str[temp] = '\0';
    startmin = my_atoi(str);
    // GET STOP HOUR
    CmdLCD(CLEAR_LCD);
    StrLCD("STOP HOURS");
    for(temp = 0; temp < 2; temp++)
    {
        key = Keyscan();
        str[temp] = key;
        CmdLCD(GOTO_LINE2_POS0 + temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan() == 0);
    }
    str[temp] = '\0';
    stophour = my_atoi(str);
    // GET STOP MINUTE
    CmdLCD(CLEAR_LCD);
    StrLCD("STOP MINUTES");
    for(temp = 0; temp < 2; temp++)
    {
        key = Keyscan();
        str[temp] = key;
        CmdLCD(GOTO_LINE2_POS0 + temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan() == 0);
    }
    str[temp] = '\0';
    stopmin = my_atoi(str);

    CmdLCD(CLEAR_LCD);
    StrLCD("TIME SAVED");
    delay_ms(1000);
}
}
u32 checkpassword()
{
	u32 attempts=0,i;
	CmdLCD(CLEAR_LCD);
	while(attempts<3)
	{
	memset(curpass,0,sizeof(curpass));
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER PASSWORD");
	CmdLCD(GOTO_LINE2_POS0);
		i=0;
		while(i<5)
		{
	key=Keyscan();
	if(key>='0'&&key<='9')
	{
		curpass[i++]=key;
		CharLCD('*');
		delay_ms(100);
	}
	else if(key=='B'&&i>0)
	{
		i--;
		curpass[i]='\0';
		CmdLCD(GOTO_LINE2_POS0+i);
		CharLCD(' ');
		CmdLCD(GOTO_LINE2_POS0+i);
	}
		curpass[i]='\0';
	while(Colscan()==0);
}
		if(strcmp(password,curpass)==0)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("CORRECT PWD");
			delay_ms(1000);
			if(validtime())
			return 1;
			else
			return 0;
		}
		else
		{
			attempts++;
		CmdLCD(CLEAR_LCD);
		StrLCD("TRY AGAIN");
		delay_ms(1000);
		CmdLCD(CLEAR_LCD);
		}
		}
		if(attempts==3)
		{
			StrLCD("ATTEMPTS FINISH");
			delay_ms(1000);
				CmdLCD(CLEAR_LCD);
		}
	return 0;
}
void changepassword()
{
	 u32 i=0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER OLD-PWD");
	CmdLCD(GOTO_LINE2_POS0);
		while(i<5)
		{
	key=Keyscan();
	if(key>='0'&&key<='9')
	{
		curpass[i++]=key;
		CharLCD('*');
		delay_ms(100);
	}
	else if(key=='B'&&i>0)
	{
		i--;
		curpass[i]='\0';
		CmdLCD(GOTO_LINE2_POS0+i);
		CharLCD(' ');
		CmdLCD(GOTO_LINE2_POS0+i);
	}
		curpass[i]='\0';
	while(Colscan()==0);
}
		if(strcmp(password,curpass)==0)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("PWD MATCHED");
			delay_ms(1000);
			CmdLCD(CLEAR_LCD);
			StrLCD("ENTER NEW_PWD");
			CmdLCD(GOTO_LINE2_POS0);
			while(j<5)
			{
			key=Keyscan();
	 			if(key>='0' && key<='9')
	       {
					 
		        newpass[j++]=key;
		        CharLCD('*');
		        delay_ms(100);
	       }
	       else if(key=='B' && j>0)
	        {
		        j--;
		        newpass[j]='\0';
		        CmdLCD(GOTO_LINE2_POS0+j);
		        CharLCD(' ');
		        CmdLCD(GOTO_LINE2_POS0+j);
	        }
					 strcpy(password,newpass);
		          newpass[j]='\0';
	            while(Colscan()==0);
          }
			if(strcmp(password,newpass)==0)
			{
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("PWD CHANGED");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("SUCCESSFULLY");
				delay_ms(1000);
				CmdLCD(CLEAR_LCD);
				return;
			}
			else
			{
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("NEW PASS");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("NOT MATCHED");
            delay_ms(1000);
            CmdLCD(CLEAR_LCD);
				    return;
        }
			}
}
void changertc(){
    s8 str[4];
    CmdLCD(CLEAR_LCD);
    StrLCD("SET HOURS");
    for(temp=0;temp<2;temp++){
        key=Keyscan();
        str[temp]=key;
        CmdLCD(GOTO_LINE2_POS0+temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan()==0);
    }
    str[temp] = '\0'; 
    hour=my_atoi(str);

    CmdLCD(CLEAR_LCD);
    StrLCD("SET MINUTES");
    for(temp=0;temp<2;temp++){
        key=Keyscan();
        str[temp]=key;
        CmdLCD(GOTO_LINE2_POS0+temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan()==0);
    }
    str[temp] = '\0'; 
    min=my_atoi(str);

    CmdLCD(CLEAR_LCD);
    StrLCD("SET SECONDS");
    for(temp=0;temp<2;temp++){
        key=Keyscan();
        str[temp]=key;
        CmdLCD(GOTO_LINE2_POS0+temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan()==0);
    }
    str[temp] = '\0'; 
    sec=my_atoi(str);

    SetRTCTimeInfo(hour,min,sec);
    CmdLCD(CLEAR_LCD);
}

void changedate(){
    s8 str[5];
    CmdLCD(CLEAR_LCD);
    StrLCD("SET DATE");
    for(temp=0;temp<2;temp++){
        key=Keyscan();
        str[temp]=key;
        CmdLCD(GOTO_LINE2_POS0+temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan()==0);
    }
    str[temp] = '\0'; 
    date=my_atoi(str);

    CmdLCD(CLEAR_LCD);
    StrLCD("SET MONTH");
    for(temp=0;temp<2;temp++){
        key=Keyscan();
        str[temp]=key;
        CmdLCD(GOTO_LINE2_POS0+temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan()==0);
    }
    str[temp] = '\0'; 
    month=my_atoi(str);

    CmdLCD(CLEAR_LCD);
    StrLCD("SET YEAR");
    for(temp=0;temp<4;temp++){
        key=Keyscan();
        str[temp]=key;
        CmdLCD(GOTO_LINE2_POS0+temp);
        CharLCD(key);
        delay_ms(200);
        while(Colscan()==0);
    }
    str[temp] = '\0'; 
    year=my_atoi(str);

    CmdLCD(CLEAR_LCD);
    StrLCD("0:S 1:M 2:T 3:W");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("4:T 5:F 6:S");
    delay_ms(200);
    key=Keyscan();
    while(Colscan()==0);
    day=key-'0';
    SetRTCDateInfo(date,month,year);
    SetRTCDay(day);
    CmdLCD(CLEAR_LCD);
    return;
}
void open_menu(){
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("1:CPWD 2:CRTC");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("3:CMY 4:CSST 5:EXT");
    
    key=Keyscan();
    while(Colscan()==0);
    CmdLCD(CLEAR_LCD);
    switch(key){
        case '1':
            changepassword();
            break;   
        case '2':
            changertc();
            break;   
        case '3':
            changedate();
            break;
		case '4':
		    changestartandstoptime();
			break; 
        case '5':
					//return;
            break;
        default:CmdLCD(CLEAR_LCD);
				        delay_ms(500);
                StrLCD("INVALID OPTION");
				        break;
    }
	}

void eint0_isr(void) __irq
	{
		CmdLCD(CLEAR_LCD);
     CmdLCD(GOTO_LINE1_POS0);
    StrLCD(" TO SHOW MENU");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("PRESS 1"); 
    key=Keyscan();
    while(Colscan()==0);
    switch(key){
        case '1':
            open_menu();
            break;
        default:
            break;
    }
    EXTINT = 1<<0;
    VICVectAddr = 0;
		CmdLCD(CLEAR_LCD);
}
int main()
{ 
    init_system();
	  display_title();
   	CfgPortPinFunc(0,1,EINT0_PIN_0_1);
    VICIntEnable = 1<<EINT0_VIC_CHNO;
    VICVectCntl0 = (1<<5) | EINT0_VIC_CHNO;
    VICVectAddr0 = (u32)eint0_isr;
    EXTMODE  = 1<<0; 
    EXTPOLAR = 0;  
	SetRTCTimeInfo(00,00,00);
	SetRTCDateInfo(01,12,2025);
	SetRTCDay(4);
while(1)
{
    display_RTC();      // RTC always refreshes

    // Check first — ONLY call Keyscan() when a key is truly pressed
    if(Colscan() == 0)   // key is pressed (because 0 = active)
    {
        key = Keyscan();   // safe now, will not block

        if(key == 'E')
        {
            if(checkpassword())
            {
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("LOGIN SUCCESS");

                // this delay will freeze RTC for 1 sec (normal)
                delay_ms(1000);

                CmdLCD(CLEAR_LCD);
            }
        }
    }

    // If no key is pressed, Colscan()==1 ? Keyscan() is NOT called
    // ? RTC keeps updating
}


}
