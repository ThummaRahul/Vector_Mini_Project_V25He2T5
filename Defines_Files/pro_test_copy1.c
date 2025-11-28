#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
//#define Succuss_LED 0//P0.19
int check_password(void);
int my_strcmp(s8 *s1,s8 *s2);
int Edit_RTC_Info(void);
int change_password(void);
s8 Current_Password[]= "12345";
/************************************/

#include "rtc.h"
#include "lcd.h"

s32 hour,min,sec,date,month,year,day;

/************************************/
void my_strcpy(s8 *dest, s8 *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';   // terminate destination string
}

int main()
{
						int res;
            char ch;
	          //IODIR0 |=1<<Succuss_LED;
	          InitLCD();
            RTC_Init();	
						Init_KPM();
												
            SetRTCTimeInfo(12,14,10);
						SetRTCDateInfo(30,11,2025);
						SetRTCDay(4);
	
						while (1) 
						{
							// Get and display the current time on LCD
							GetRTCTimeInfo(&hour,&min,&sec);
							DisplayRTCTime(hour,min,sec);
							GetRTCDateInfo(&date,&month,&year);
							DisplayRTCDate(date,month,year);
							GetRTCDay(&day);
							DisplayRTCDay(day);
						
							/***************************/
							
						  ch=KeyScan();
							if(ch=='+')
							{
								        CmdLCD(CLRLCD); 
									      StrLCD("Enter password");	      	          
												res = check_password();
												if(res)
												{
//													    IOSET0=1<<Succuss_LED;	
//													    delay_ms(10);
//													    IOCLR0=1<<Succuss_LED;	
//													    delay_ms(10);
															CmdLCD(CLRLCD);
															StrLCD("valid password");													    
															//delay_s(1);
													    delay_ms(100);            
                              CmdLCD(CLRLCD);
												}
												else
												{
															CmdLCD(CLRLCD);
															StrLCD("Wrong Password");
															//delay_s(1);
													   delay_ms(100);            
                             CmdLCD(CLRLCD); 	
												}						    									
						  }
							else if(ch=='-')
              {
							       CmdLCD(CLRLCD); 
								     CmdLCD(GOTO_LINE1_POS0);
									   StrLCD("1.ERTCI 2.EDAT");	// edit rtc info // edit device allowed time
                     CmdLCD(GOTO_LINE2_POS0);
									   StrLCD("3.PWDCHG 4.EXIT ");
								     
                     ch=KeyScan();
                     if(ch=='1')
                     {
											    Edit_RTC_Info();
										 }
										 else if(ch=='2')
                     {
										     
										 }
                     else if(ch=='3')
										 {
										     change_password();  
										 }else if(ch=='4')
                     {
											 CmdLCD(CLRLCD); 
										 }										 								
							}						 
						  GetRTCTimeInfo(&hour,&min,&sec);
							DisplayRTCTime(hour,min,sec);
							GetRTCDateInfo(&date,&month,&year);
							DisplayRTCDate(date,month,year);
							GetRTCDay(&day);
							DisplayRTCDay(day);
						}
}

int my_strcmp(s8 *s1,s8 *s2)
{
					int i;
					for(i=0;i<5;i++)
					{
					     if(s1[i]!=s2[i])
					     return 0;
					}
					return 1;
}
int check_password(void)
{
				s8 ch;
				s8 User_Password[6];
	      u32 index=0;
			  
				while(1)
				{
					  CmdLCD(GOTO_LINE2_POS0+index);
						delay_ms(10);
					  ch = KeyScan();
					
						if(ch=='*')
						{						
									if(index==0)
									continue;
									index--;
									CmdLCD(GOTO_LINE2_POS0+index);
									CharLCD(' ');
									CmdLCD(GOTO_LINE2_POS0+index);
						}
						else if(ch=='#')
						{
									User_Password[index]='\0';
									break;
						}
						else
						{
									User_Password[index++]=ch;//update the key value into						
									
									CharLCD(ch);
							    
						}
      }
			
			if(my_strcmp(User_Password,Current_Password))
			{
			  return 1;
			}
			else{
			     return 0;
		  }
}
int change_password()
{
    s8 oldpwd[6], newpwd[6], confirmpwd[6];
    int i;

    CmdLCD(CLRLCD);
	  CmdLCD(GOTO_LINE1_POS0);
    StrLCD("Old PWD:");
    delay_ms(10);

    // read old password
	  CmdLCD(GOTO_LINE2_POS0);
    for(i=0; i<5; i++)
    {
			  CmdLCD(GOTO_LINE2_POS0+i);
        oldpwd[i] = KeyScan();
        CharLCD('*');
        delay_ms(10);
    }
		StrLCD(oldpwd);
		StrLCD(Current_Password);
    oldpwd[5] = '\0';

    // compare with system password
    if((my_strcmp(oldpwd, Current_Password)) != 1)
    {
        CmdLCD(CLRLCD);
        StrLCD("Wrong Old PWD");
        delay_ms(100);
        CmdLCD(CLRLCD);
			  return 0;
    }

    // enter new password
    CmdLCD(CLRLCD);
    StrLCD("New PWD:");
    CmdLCD(GOTO_LINE2_POS0);
    for(i=0; i<5; i++)
    {
			  CmdLCD(GOTO_LINE2_POS0+i);
        newpwd[i] = KeyScan();
        CharLCD('*');
        delay_ms(10);
    }
    newpwd[5] = '\0';

    // confirm new password
    CmdLCD(CLRLCD);
    StrLCD("Confirm:");
    //delay_ms(100);
    CmdLCD(GOTO_LINE2_POS0);
    for(i=0; i<5; i++)
    {
			  CmdLCD(GOTO_LINE2_POS0+i);
        confirmpwd[i] = KeyScan();
        CharLCD('*');
        delay_ms(10);
    }
    confirmpwd[5] = '\0';

    // compare new and confirm
    if(my_strcmp(newpwd, confirmpwd) != 1)
    {
        CmdLCD(CLRLCD);
        StrLCD("Mismatch");
        delay_ms(500);
        return 0;
    }

    // update system password
    my_strcpy(Current_Password, newpwd);

    CmdLCD(CLRLCD);
    StrLCD("PWD Updated");
    delay_ms(100);
		CmdLCD(CLRLCD);

    return 1;
}
int Edit_RTC_Info(void)
{
	     int temp_hr,temp_min,temp_sec,temp_day,temp_month,temp_yr;
	     u8 d1,d2,d3,d4,d;
	     //s32 hr,mn,se,da,mo,yr,dy;
	     char ch;
	     
	     //delay_ms(50);
	     CmdLCD(CLRLCD);
	     StrLCD("EDIT YOU WANT");	
			 CmdLCD(CLRLCD);
	
	     while(1)
       {
				 CmdLCD(GOTO_LINE1_POS0);
				 StrLCD("1Hr 2Mn 3Sc 4WD");	// edit rtc info // edit device allowed time
				 CmdLCD(GOTO_LINE2_POS0);
				 StrLCD("5Dy 6Mt 7yr 8Ex");
				 //delay_ms(20);
				 //CmdLCD(CLRLCD);
				 ch = KeyScan();
				 if(ch=='1')
				 {
						 temp_hr=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER HOURS");
					   //delay_ms(30);
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(10); 
						 temp_hr = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_hr = temp_hr*10 + (d2-'0');  // final integer 0–23
						 
						 SetRTCTimeInfo(temp_hr, min, sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("HOUR UPDATED");
						 delay_ms(30);
						 CmdLCD(CLRLCD);						 
				 }
				 else if(ch=='2')
         {
					   temp_min=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER MINUTES");
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
						 
					   CharLCD(d1);
					   delay_ms(10); 
						 temp_min = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();
					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_min = temp_min*10 + (d2-'0');  // final integer 0–23
						 
						 SetRTCTimeInfo(hour,temp_min, sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("MIN UPDATED");
						 delay_ms(50);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='3')
         {
					   temp_sec=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER Seconds");
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
						  
					   CharLCD(d1);
					   delay_ms(10);
						 temp_sec = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();
					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_sec = temp_sec*10 + (d2-'0');  // final integer 0–23
						 
						 SetRTCTimeInfo(hour, min, temp_sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("Seconds UPDATED");
						 delay_ms(50);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='4')
         {
					   d=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER DATE(1-7)");
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d = KeyScan();              
						  
					   CharLCD(d);
					   delay_ms(10);
						 d = (d - '0'); 
					   SetRTCDay(d);
					   CmdLCD(CLRLCD);
						 StrLCD("D-O-WEEK UPDATED");
						 delay_ms(50);
						 CmdLCD(CLRLCD);
					   
				 }
				 else if(ch=='5')
         {
					   temp_day=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Date ");					   
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(10); 
						 temp_day = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_day = temp_day*10 + (d2-'0');  // final integer 0–23
						 
					   SetRTCDateInfo(temp_day,month,year);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("DATE UPDATED");
						 delay_ms(30);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='6')
         {
					   temp_month=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Month ");					   
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(10); 
						 temp_month = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_month = temp_month*10 + (d2-'0');  // final integer 0–23
						 
					   SetRTCDateInfo(day,temp_month,year);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("Month UPDATED");
						 delay_ms(30);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='7')
         {
					   temp_yr=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Year ");					   
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(10); 
						 temp_yr = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_yr = temp_yr*10 + (d2-'0');  // final integer 0–23
						 
					  // Read third digit
					   d3 = KeyScan();					   
						 CharLCD(d3);
					   delay_ms(20);
						 temp_yr = temp_yr*10 + (d3-'0');
						 
						 // Read fourth digit
						 d4 = KeyScan();					   
						 CharLCD(d4);
					   delay_ms(20);
						 temp_yr = temp_yr*10 + (d4-'0');
						 
					   SetRTCDateInfo(day,month,temp_yr);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("YEAR UPDATED");
						 delay_ms(30);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='8')
         {
					 CmdLCD(CLRLCD);
					 return 0;
				 }			 
			 }
}
//			 GetRTCTimeInfo(&hour,&min,&sec);
//       DisplayRTCTime(hour,min,sec);
//			 GetRTCDateInfo(&date,&month,&year);
//			 DisplayRTCDate(date,month,year);
//			 GetRTCDay(&day);
//			 DisplayRTCDay(day);
//void my_GetRTCDay(s32 *day)
//{
//	*day = DOW; 
//}
//void my_SetRTCDateInfo(u32 date, u32 month, u32 year)
//{
//	DOM = date;
//	MONTH = month;
//	YEAR = year;	
//}
//void my_SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
//{
//	HOUR = hour;
//	MIN = minute;
//	SEC = second;
//}
//#define SEC        
//#define MIN            
//#define HOUR           
//#define DOM            
//#define DOW            
////#define DOY            
//#define MONTH          
//#define YEAR 
//            my_SetRTCTimeInfo(hr,mn,se);
//						my_SetRTCDateInfo(da,mo,yr);
//						my_SetRTCDay(dy);

