#include "rtc.h"
#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
s8 Current_Password[]= "12345";
#include "operations_defines.h"
            
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
						//CmdLCD(CLRLCD);
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
    s8 oldpwd[6], newpwd[6], confirmpwd[6],ch;
    int i,index;

    CmdLCD(CLRLCD);
	  CmdLCD(GOTO_LINE1_POS0);
    StrLCD("Old PWD:");
    delay_ms(500);
	  index=0;
    while(index<6)
				{
					  CmdLCD(GOTO_LINE2_POS0+index);
						//CmdLCD(CLRLCD);
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
									oldpwd[index]='\0';
									break;
						}
						else
						{
									oldpwd[index++]=ch;//update the key value into														
									CharLCD(ch);
							    
						}
      }
    // read old password
	  /* CmdLCD(GOTO_LINE2_POS0);
    for(i=0; i<5; i++)
    {
			  //CmdLCD(GOTO_LINE2_POS0+i);
        oldpwd[i] = KeyScan();
        //CharLCD('*');
			  CharLCD(oldpwd[i]);
        delay_ms(50);
			  if(oldpwd[i]=='*')
						{						
									if(i==0)
									continue;
									i--;
									CmdLCD(GOTO_LINE2_POS0+i);
									CharLCD(' ');
									CmdLCD(GOTO_LINE2_POS0+i);
						}
    }*/
		//StrLCD(oldpwd);
		//StrLCD(Current_Password);
    oldpwd[5] = '\0';
    delay_ms(1000);
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
		delay_ms(1000);
    CmdLCD(GOTO_LINE2_POS0);
    for(i=0; i<5; i++)
    {
			  CmdLCD(GOTO_LINE2_POS0+i);
        newpwd[i] = KeyScan();
        CharLCD('*');
        delay_ms(10);
			  if(newpwd[i]=='*')
						{						
									if(i==0)
									continue;
									i--;
									CmdLCD(GOTO_LINE2_POS0+i);
									CharLCD(' ');
									CmdLCD(GOTO_LINE2_POS0+i);
						}
			  
    }
    newpwd[5] = '\0';
    delay_ms(400);
    // confirm new password
    CmdLCD(CLRLCD);
    StrLCD("Confirm:");
    delay_ms(1000);
    CmdLCD(GOTO_LINE2_POS0);
    for(i=0; i<5; i++)
    {
			  CmdLCD(GOTO_LINE2_POS0+i);
        confirmpwd[i] = KeyScan();
        CharLCD('*');
        delay_ms(10);
			  if(confirmpwd[i]=='*')
						{						
									if(i==0)
									continue;
									i--;
									CmdLCD(GOTO_LINE2_POS0+i);
									CharLCD(' ');
									CmdLCD(GOTO_LINE2_POS0+i);
						}
    }
    confirmpwd[5] = '\0';
    delay_ms(400);
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
    delay_ms(1000);
		CmdLCD(CLRLCD);
    
    //return 1;
}
int Edit_RTC_Info(void)
{
	     int temp_hr,temp_min,temp_sec,temp_date,temp_month,temp_yr;
	     u8 d1,d2,d3,d4,d;
	     //s32 hr,mn,se,da,mo,yr,dy;
	     char ch;
	     //delay_ms(50);
	     CmdLCD(CLRLCD);
	     StrLCD("EDIT YOU WANT");	
	     delay_ms(1000);
			 CmdLCD(CLRLCD);
	
	     while(1)
       {
				 CmdLCD(GOTO_LINE1_POS0);
				 StrLCD("1Hr 2Mn 3Sc 4WD");	// edit rtc info // edit device allowed time
				 CmdLCD(GOTO_LINE2_POS0);
				 StrLCD("5Dy 6Mt 7yr 8Ex");
				 delay_ms(200);
				 //CmdLCD(CLRLCD);
				 ch = KeyScan();
				 if(ch=='1')
				 {
						 temp_hr=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER HOURS");
					   delay_s(1);
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(100); 
						 temp_hr = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(100);
						 temp_hr = temp_hr*10 + (d2-'0');  // final integer 0–23
						 
					   GetRTCTimeInfo(&hour,&min,&sec);
						 SetRTCTimeInfo(temp_hr, min, sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("HOUR UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);						 
				 }
				 else if(ch=='2')
         {
					   temp_min=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER MINUTES");
					   delay_s(1);
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
						 
					   CharLCD(d1);
					   delay_ms(100); 
						 temp_min = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();
					   
						 CharLCD(d2);
					   delay_ms(100);
						 temp_min = temp_min*10 + (d2-'0');  // final integer 0–23
						 
					   GetRTCTimeInfo(&hour,&min,&sec);
						 SetRTCTimeInfo(hour,temp_min, sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("MIN UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='3')
         {
					   temp_sec=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER Seconds");
					   delay_s(1);
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
						 
					   GetRTCTimeInfo(&hour,&min,&sec);
						 SetRTCTimeInfo(hour, min, temp_sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("Seconds UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='4')
         {
					   d=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER DATE(1-7)");
					   delay_s(1);
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d = KeyScan();              
						  
					   CharLCD(d);
					   delay_ms(10);
						 d = (d - '0'); 
					 
					   GetRTCDay(&day);
					   SetRTCDay(d);
					   CmdLCD(CLRLCD);
						 StrLCD("D-O-WEEK UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);
					   
				 }
				 else if(ch=='5')
         {
					   temp_date=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Date ");	
             delay_s(1);				   
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(10); 
						 temp_date = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(20);
						 temp_date = temp_date*10 + (d2-'0');  // final integer 0–23
						 
					   GetRTCDateInfo(&date,&month,&year);
					   SetRTCDateInfo(temp_date,month,year);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("DATE UPDATED");
						 delay_s(2);
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
						 
					   GetRTCDateInfo(&date,&month,&year);
					   SetRTCDateInfo(date,temp_month,year);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("Month UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='7')
         {
					   temp_yr=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Year ");
             delay_s(1);					 
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
						 
						 GetRTCDateInfo(&date,&month,&year);
					   SetRTCDateInfo(date,month,temp_yr);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("YEAR UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);
				 }
				 else if(ch=='8')
         {
					 CmdLCD(CLRLCD);
					 return 0;
				 }			 
			 }
}
