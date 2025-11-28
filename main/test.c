#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
#define Succuss_LED 0//P0.0
void open_edit_menu(void);

#include "operations.h"
#include "rtc.h"

#define PIN_FUNC4 3
#define EINT0_VIC_CHNO  14
#define EINT0_STATUS_LED 16  //@p1.16
#define EINT0_PIN_0_1    PIN_FUNC4

void cfgportpinfunc(u32 portNo,u32 pinNo,u32 pinFunc);
void eint0_isr(void) __irq
{       
        open_edit_menu();
        CmdLCD(CLRLCD);
        delay_ms(200);
        EXTINT = 1<<0;
        VICVectAddr=0;
}
int start_hr = 17;
int end_hr   = 18;
int start_mn = 00;
int end_mn   = 30;  // 5:30 to 6:30 PM allowable time

int main()
{
    s32 hour,min,sec,date,month,year,day;
    int res;
    char ch;
    int a_DOW=0;

    RTC_Init();
    IODIR0 |=1<<Succuss_LED;
    InitLCD();
    Init_KPM();

    SetRTCTimeInfo(17,14,10);
    SetRTCDateInfo(28,11,2025);
    SetRTCDay(4);

    cfgportpinfunc(0,1,EINT0_PIN_0_1);
    VICIntEnable  = 1<<EINT0_VIC_CHNO;
    VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
    VICVectAddr0=(u32)eint0_isr;
    EXTMODE =1<<0;


    while(1)
    {
        do{
            GetRTCTimeInfo(&hour,&min,&sec);
            DisplayRTCTime(hour,min,sec);

            GetRTCDateInfo(&date,&month,&year);
            DisplayRTCDate(date,month,year);

            GetRTCDay(&day);
            DisplayRTCDay(day);
					  

        }while(ColScan()==1);


        if(ColScan()==0)
        {
            ch = KeyScan();

            if(ch=='+')
            {
                CmdLCD(CLRLCD);
                StrLCD("Enter password");
                CmdLCD(GOTO_LINE2_POS0);
                res = check_password();

                GetRTCTimeInfo(&hour,&min,&sec);   // always read fresh time
                GetRTCDay(&day);

                if(res)
                {
                    if(hour>=start_hr && hour<=end_hr && min>=start_mn && min<=end_mn&& day!=a_DOW)
                    {
                        CmdLCD(CLRLCD);
                        StrLCD("ACCESS ALLOWED");
                        IOSET0 = 1<<Succuss_LED;
                        delay_s(1);
                        IOCLR0 = 1<<Succuss_LED;
                        CmdLCD(CLRLCD);
                    }
                    else
                    {
                        CmdLCD(CLRLCD);
                        StrLCD("NOT ALLOWED");
                        delay_s(1);
                        CmdLCD(CLRLCD);
                    }
                }
                else
                {
                    CmdLCD(CLRLCD);
                    StrLCD("wrong pwd");
                    delay_s(1);
                    CmdLCD(CLRLCD);
                }
            }
        }
    }
}

void open_edit_menu(void)
{
                                char ch;
                                CmdLCD(CLRLCD);
                                CmdLCD(GOTO_LINE1_POS0);
                                StrLCD("1.ERTCI 2.EDAT");       // edit rtc info // edit device allowed time
                                CmdLCD(GOTO_LINE2_POS0);
                                StrLCD("3.PWDCHG 4.EXIT");

                                ch = KeyScan();

                                if(ch=='1')
                                {
                                        Edit_RTC_Info();
                                }
                                else if(ch=='2')
                                {
                                        Edit_EAT_Info(&start_hr,&end_hr,&start_mn,&end_mn);
                                }

                                else if(ch=='3')
                                {
                                        change_password();
                                }
                                else if(ch=='4')
                                {
                                        CmdLCD(CLRLCD);
                                }
                                else{
                                         CmdLCD(CLRLCD);
                                         StrLCD("Invalid Key");
                                         delay_s(1);
																	       CmdLCD(GOTO_LINE1_POS0);
                                         CmdLCD(CLRLCD);	
                                         CmdLCD(GOTO_LINE2_POS0);
                                         CmdLCD(CLRLCD);																	
                                }
}
void cfgportpinfunc(u32 portNo,u32 pinNo,u32 pinFunc)
{
    if(portNo==0)
        {
           if(pinNo<16)
           {
              PINSEL0=((PINSEL0)&(~(3<<(pinNo*2)))|(pinFunc<<(pinNo*2)));
           }
           else if (pinNo >= 16 && pinNo <=31)
           {
                  PINSEL1=((PINSEL1)&(~(3<<((pinNo-16)*2)))|(pinFunc<<((pinNo-16)*2)));
           }
        }
}
