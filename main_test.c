#include "types.h"
#include <lpc21xx.h>
#include "arduino.h"
#include "delay.h"
#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "pin_connect_block.h"
#include "pin_functions_defines.h"

#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16
#define EINT0_PIN_0_1 PIN_FUNC4

#define EINT1_VIC_CHNO 15
#define EINT1_STATUS_LED 17
#define EINT1_PIN_0_3 PIN_FUNC4

#include <string.h>
#include "kpm_defines.h"
#include "kpm.h"

s32 hour, min, sec, date, month, year, day;
s32 enhr=2,exhr=8;
#define ENTRY 0
#define INER 1

void eint0_isr(void) __irq;
void eint1_isr(void) __irq;

cu8 UserCGRAM[5][8] = {
    {0x1B,0x0E,0x04,0x0E,0x1B,0x00,0x00,0x00}, // Wrong
		{0x0E,0x11,0x11,0x1F,0x1B,0x1B,0x1F,0x00},
		{0x06,0x00,0x00,0x1F,0x1B,0x1B,0x1F,0x00},
    {0x04,0x06,0x1F,0x06,0x04,0x00,0x00,0x00}, // Arrow
    {0x04,0x0E,0x0E,0x04,0x00,0x04,0x00,0x00},  // Warning
};

u32 flag = 0;
s8 password[] = "1234", pass[10];
u32 key, i, j = 0;

u32 check_entry_hours()
{
   u32 chr=HOUR;//current hour
	 if(enhr<=chr && exhr>=chr)
	 {
		 return 1;
	 }
	 return 0;
}
void DISPLAY_RTC()
{
    GetRTCTimeInfo(&hour, &min, &sec);
    DisplayRTCTime(hour, min, sec);

    GetRTCDateInfo(&date, &month, &year);
    DisplayRTCDate(date, month, year);

    GetRTCDay(&day);
    DisplayRTCDay(day);
}

void check_password()
{
	if(check_entry_hours()==0)
	{
		CmdLCD(0x01);
		StrLCD("  Login-Hours  ");
		CmdLCD(0xc0);
		StrLCD("    Invaild  ");
		delay_ms(1000);
		CmdLCD(0x01);
	}
	else
	{
		
    u32 attempt = 0;

    while (attempt < 3)
    {
        i = 0;
        memset(pass, 0, sizeof(pass));

        CmdLCD(0x01);
			BuildCGRAM((u8 *)UserCGRAM[1], 8);

            CmdLCD(0x80);
            CharLCD(0);
            CmdLCD(0x80 + 2);
        //CmdLCD(0x80);
        StrLCD("ENTER PASSWORD");

        CmdLCD(0xC0 + 5);

        while (i < 4)
        {
            key = Keyscan();

            if (key >= '0' && key <= '9')
            {
                pass[i] = key;

                CmdLCD(0xC0 + 5 + i);
                CharLCD('*');

                i++;

                while (Colscan() == 0);
            }
            else if (key == 'B')
            {
                if (i > 0)
                {
                    i--;
                    pass[i] = '\0';

                    CmdLCD(0xC0 + 5 + i);
                    CharLCD(' ');

                    CmdLCD(0xC0 + 5 + i);
                }

                while (Colscan() == 0);
            }
						else{
							 i--;
						    }
        }

        pass[i] = '\0';

        if (strcmp(password, pass) == 0)
        {
					 flag=1;
            CmdLCD(0x01);
					BuildCGRAM((u8 *)UserCGRAM[2], 8);

            CmdLCD(0x80);
            CharLCD(0);
            CmdLCD(0x80 + 2);
            StrLCD("LOGIN SUCCESS");
            CmdLCD(0xC0);
            StrLCD("  HI BALAZE  ");
            delay_ms(2000);
            CmdLCD(0x01);
            break;
        }
        else
        {
            CmdLCD(0x01);
            BuildCGRAM((u8 *)UserCGRAM[0], 8);

            CmdLCD(0x80);
            CharLCD(0);
            CmdLCD(0x80 + 2);
            StrLCD("WRONG PASSWORD");

            delay_ms(2000);
            CmdLCD(0x01);

            attempt++;
        }

        if (attempt == 3)
        {
            CmdLCD(0x80);
            StrLCD("MAX ATTEMPTS");
            CmdLCD(0xC0);
            StrLCD("ACCESS DENIED");
            flag=0;
            delay_ms(2000);
            CmdLCD(0x01);
        }
    }
	}
}

s8 *menu[4] = {
    "A:EDIT_PASSWORD",
    "E:EDIT_TIME",
    "D:CHANGE_DATE",
    "B:BACK"
};
void change_time()
{
    u32 d1, d2;
    u32 data;
    StrLCD("Enter valid Hour");
	  delay_ms(1200);  
	CmdLCD(0x01);
    // ----------- HOUR INPUT -----------
    do {
        CmdLCD(0x01);
        StrLCD("Enter HH (00-23):");
        CmdLCD(0xC0);

        d1 = get_digit();
        //CharLCD(d1);

        d2 = get_digit();
        //CharLCD(d2);

        data = (d1 - '0') * 10 + (d2 - '0');
			  CharLCD(data);
        
    } while(data > 23);      // VALID: 00–23 ONLY

    hour = data;


    // ----------- MINUTE INPUT -----------
    do {
        CmdLCD(0x01);
        StrLCD("Enter MM((00-59)):");
        CmdLCD(0xC0);

        d1 = get_digit();
        //CharLCD(d1);

        d2 = get_digit();
        //CharLCD(d2);

        data = (d1 - '0') * 10 + (d2 - '0');
        CharLCD(data);
    } while(data > 59);      // VALID: 00–59 ONLY

    min = data;


    // ----------- SECOND INPUT -----------
    do {
        CmdLCD(0x01);
        StrLCD("Enter SS(00-59):");
        CmdLCD(0xC0);

        d1 = get_digit();
        //CharLCD(d1);

        d2 = get_digit();
        //CharLCD(d2);

        data = (d1 - '0') * 10 + (d2 - '0');
         CharLCD(data);
    } while(data > 59);      // VALID: 00–59 ONLY

    sec = data;


    // ----------- UPDATE RTC -----------
    SetRTCTimeInfo(hour, min, sec);

    CmdLCD(0x01);
    StrLCD("TIME UPDATED");
    CmdLCD(0xC0);
    StrLCD("Back 'B'");
    delay_ms(1000);
    CmdLCD(0x01);
}

void change_date()
{
    u32 d1, d2, d3, d4;
    u32 data;

    // ----------- DATE (01–31) -----------
    do {
        CmdLCD(0x01);
        StrLCD("Enter Date:");
        CmdLCD(0xC0);

        d1 = get_digit();
        //CharLCD(d1);
        d2 = get_digit();
        //CharLCD(d2);
        
        data = (d1-'0')*10 + (d2-'0');
			  CharLCD(data);
    
    } while(data == 0 || data > 31);   // VALID ONLY 01–31

    date = data;


    // ----------- MONTH (01–12) -----------
    do {
        CmdLCD(0x01);
        StrLCD("Enter Month:");
        CmdLCD(0xC0);

        d1 = get_digit();
       // CharLCD(d1);
        d2 = get_digit();
        //CharLCD(d2);

        data = (d1-'0')*10 + (d2-'0');
        CharLCD(data);
    } while(data == 0 || data > 12);   // VALID ONLY 01–12

    month = data;


    // ----------- YEAR (NO VALIDATION) -----------
    CmdLCD(0x01);
    StrLCD("Enter Year:");
    CmdLCD(0xC0);

    d1 = get_digit(); //CharLCD(d1);
    d2 = get_digit(); //CharLCD(d2);
    d3 = get_digit(); //CharLCD(d3);
    d4 = get_digit(); //CharLCD(d4);

    year = (d1-'0')*1000 + (d2-'0')*100 + (d3-'0')*10 + (d4-'0');
      CharLCD(data);
    
    // ----------- SET DATE INTO RTC -----------
    SetRTCDateInfo(date, month, year);


    // ----------- DAY SELECTION (0–6) -----------
    do {
        CmdLCD(0x01);
        StrLCD("day:0.S 1.M 2.TU");
        CmdLCD(0xC0);
        StrLCD("3.W 4.Th 5.F 6.S");

        d1 = get_digit();
        //CharLCD(d1);

        data = d1 - '0';
        CharLCD(data);
    } while(data > 6);   // VALID ONLY 0–6

    day = data;
    SetRTCDay(day);


    // ----------- SUCCESS MESSAGE -----------
    CmdLCD(0x01);
    StrLCD("DATE UPDATED");
    CmdLCD(0xC0);
    StrLCD("Back 'B'");
    delay_ms(1000);
    CmdLCD(0x01);
}

void change_password()
	{
		StrLCD("Enter Current");
		CmdLCD(0xc0);
		StrLCD("  Password  ");
		delay_ms(1500);
		
		check_password();
		
		if(flag==1)
		{
			s8 new_pass[10];
    u32 i = 0;
		CmdLCD(0x01);
    StrLCD("   PASSWORD   ");
    CmdLCD(0xC0);
    StrLCD("    MATCHED   ");
    delay_ms(1500);
    CmdLCD(0x01);
			
    memset(new_pass, 0, sizeof(new_pass));

    CmdLCD(0x01);
    StrLCD("New Password:");
    CmdLCD(0xC0);   // Line 2

    while (i < 4)
    {
        u32 k = Keyscan();

        if (k >= '0' && k <= '9')
        {
            new_pass[i] = k;
            CharLCD(new_pass[i]);          // Show *
            i++;

            while (Colscan() == 0);
        }
        else if (k == 'B')         // BACKSPACE
        {
            if (i > 0)
            {
                i--;
                new_pass[i] = '\0';

                CmdLCD(0xC0 + i);
                CharLCD(' ');      // clear position

                CmdLCD(0xC0 + i);  
            }

            while (Colscan() == 0);
        }
        else
        {
					i--;
            // Ignore wrong keys
        }
    }

    new_pass[4] = '\0';

    // ---- Save into GLOBAL password[] ----
    strcpy(password, new_pass);

    // ---- Confirmation ----
    CmdLCD(0x01);
    StrLCD("PASSWORD UPDATED");
    CmdLCD(0xC0);
    StrLCD("Press B Back");
    delay_ms(1500);
    CmdLCD(0x01);
		return;
}
	else
		{
			CmdLCD(0x01); 
			StrLCD("Back(HOME)'B'");
			delay_ms(1000);
			CmdLCD(0x01);
			return;
		}
		
}
void open_menu()
{
    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("Check menu");
    CmdLCD(0xc0);
	  StrLCD("Press C");
    while (1)
    {
        u32 k = Keyscan();
        switch (k)
        {
            case 'C':
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD(menu[j]);

                j++;
                if (j >= 4) j = 0;

                CmdLCD(0xC0);
                StrLCD("Press C Next");

                delay_ms(200);
                break;

						case 'E':
                CmdLCD(0x01);
						    change_time();
                break;
						case 'A':
							  CmdLCD(0x01);
						    change_password();
						    CmdLCD(0xC0);
						    break;
            case 'B':
                CmdLCD(0x01);
                return;
						case 'D':
                change_date();
                break;

            default:
							CmdLCD(0x01);
							 StrLCD("inavalid Key");
						    delay_ms(1000);
						   CmdLCD(0x01);
                return;
        }
    }
}
void eint0_isr(void) __irq{
    //eint0 isr user activity begins
    //toggle EINT0 status led upon interrupt fired/raised
    IOPIN1 ^= 1<<EINT0_STATUS_LED;
    //eint0 isr user activity ends
    //clear EINT0 status in External Interrupt Peripheral 
	  CmdLCD(0x01);
	  open_menu();
	  
    EXTINT = 1<<0;
    //clear EINT0 status in VIC peripheral
    VICVectAddr = 0;
}

int main()
{
	u32 key;
    Init_LCD();
    RTC_Init();
    Init_KPM();

    IODIR0 &= ~((1<<ENTRY));
	  
    IODIR1 |= 1 << EINT0_STATUS_LED;
    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("    Time-Guard   ");
    CmdLCD(0xC0);
    StrLCD("  Access Shield  ");
    delay_ms(2000);

    CmdLCD(0x01);

    hour = 9; min = 0; sec = 0;
    date = 30; month = 11; year = 2025;
    
    SetRTCTimeInfo(hour, min, sec);
    SetRTCDateInfo(date, month, year);
    SetRTCDay(1);
    //cfg p0.1 pin as EINT0 input pin
    CfgPortPinFunc(0,1,EINT0_PIN_0_1);
		
		VICIntEnable = 1<<EINT0_VIC_CHNO ;
		
		 //cfg EINT0 as v.irq,highest priority 0
    VICVectCntl0 = (1<<5) | EINT0_VIC_CHNO;
    //load eint0_isr address in hardware lut sfr for v.irq
    VICVectAddr0 = (u32)eint0_isr;
		
		   //cfg External Interrupt peripheral
    //Enable EINT0,EINT1 ,def all eint's are any enable
    //EXTINT = 0
    //cfg EINT0,EINT1 for edge triggering
    EXTMODE = 1<<0;
		
    while (1)
    {
			  /*while(1)
				{
					DISPLAY_RTC();
				}*/
        do
        {
					DISPLAY_RTC();
					 //key=Keyscan();
					 //while(Colscan()==0);
        }while (digitalRead(ENTRY));//key!='*');
//digitalRead(ENTRY)
        if (digitalRead(ENTRY)==0)
        {
            check_password();//Login 
        }
				
    }
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*s8  key1,key2;
	u32 flag=0;
  // Initialize RTC 
	RTC_Init();
		
  // Initialize the LCD
	Init_LCD();
	key1=key_scan();
	SetRTCTimeInfo(00,00,00);
	SetRTCDateInfo(30,10,2025);
	SetRTCDay(1);
  // Set the initial time (hours, minutes, seconds)
	

  while (1) 
	{
    // Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
  }*/

