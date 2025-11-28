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
    s8 ch, User_Password[6];
    u32 index;

retry_pass:
    CmdLCD(CLRLCD);
    StrLCD("Enter PWD:");
	  delay_ms(500);
		CmdLCD(CLRLCD);
	  StrLCD("# :ESC/Enter");
	  
    index=0;

    while(1)
    {
        CmdLCD(GOTO_LINE2_POS0+index);
        ch=KeyScan();

        if(ch=='*')
        {
            if(index>0)
            {
                index--;
                CmdLCD(GOTO_LINE2_POS0+index);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0+index);
            }
        }
        else if(ch=='#')
        {
            User_Password[index]='\0';
            break;
        }
				
        else
        {
            if(index>=5)
            {
                CmdLCD(CLRLCD);
							  CmdLCD(GOTO_LINE1_POS0);
                StrLCD("You are pass");
							  CmdLCD(GOTO_LINE2_POS0);
                StrLCD("5 digits only");
							  
                delay_ms(700);
							  CmdLCD(CLRLCD);
                goto retry_pass;
            }
            User_Password[index++]=ch;
            CharLCD(ch);
        }
    }

    if(my_strcmp(User_Password,Current_Password)==1)
        return 1;
    else
    {
			  return 0;
    }
}

int change_password()
{
    s8 oldpwd[6], newpwd[6], confirmpwd[6], ch;
    int index, index1, index2;

retry_old:
    CmdLCD(CLRLCD);
    StrLCD("Old PWD :");
	  delay_s(1);
		CmdLCD(CLRLCD);
	  StrLCD("# :Enter/ESC");
    index=0;
    while(1)
    {
        CmdLCD(GOTO_LINE2_POS0+index);
        ch=KeyScan();
        if(ch=='*')
        {
            if(index>0)
            {
                index--;
                CmdLCD(GOTO_LINE2_POS0+index);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0+index);
            }
        }
        else if(ch=='#')
        {
            oldpwd[index]='\0';
            break;
        }
				
        else
        {
            if(index>=5)
            {
                CmdLCD(CLRLCD);
                StrLCD("ReEnter Old");
                delay_ms(800);
                goto retry_old;
            }
            oldpwd[index++]=ch;
            CharLCD(ch);
        }
    }

    if(my_strcmp(oldpwd,Current_Password)!=1)
    {
        CmdLCD(CLRLCD);
        StrLCD("Wrong Old");
        delay_ms(800);
        goto retry_old;
    }

retry_new:
    CmdLCD(CLRLCD);
    StrLCD("New PWD:");
		delay_s(1);
		CmdLCD(CLRLCD);
		StrLCD("# :Enter/ESC");
    index1=0;
    while(1)
    {
        CmdLCD(GOTO_LINE2_POS0+index1);
        ch=KeyScan();
        if(ch=='*')
        {
            if(index1>0)
            {
                index1--;
                CmdLCD(GOTO_LINE2_POS0+index1);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0+index1);
            }
        }
        else if(ch=='#')
        {
            newpwd[index1]='\0';
            break;
        }
        else
        {
            if(index1>=5)
            {
                CmdLCD(CLRLCD);
                StrLCD("Reenter New");
                delay_ms(800);
                goto retry_new;
            }
            newpwd[index1++]=ch;
            CharLCD(ch);
        }
    }

retry_confirm:
    CmdLCD(CLRLCD);
    StrLCD("Confirm: ");
		delay_s(1);
		CmdLCD(CLRLCD);
		StrLCD("# :Enter/ESC");
    index2=0;
    while(1)
    {
        CmdLCD(GOTO_LINE2_POS0+index2);
        ch=KeyScan();
        if(ch=='*')
        {
            if(index2>0)
            {
                index2--;
                CmdLCD(GOTO_LINE2_POS0+index2);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0+index2);
            }
        }
        else if(ch=='#')
        {
            confirmpwd[index2]='\0';
            break;
        }
        else
        {
            if(index2>=5)
            {
                CmdLCD(CLRLCD);
                StrLCD("ReEnter Cfm");
                delay_ms(800);
                goto retry_confirm;
            }
            confirmpwd[index2++]=ch;
            CharLCD(ch);
        }
    }

    if(my_strcmp(newpwd,confirmpwd)!=1)
    {
        CmdLCD(CLRLCD);
        StrLCD("Mismatch");
        delay_ms(800);
        goto retry_confirm;
    }

    my_strcpy(Current_Password,newpwd);
    CmdLCD(CLRLCD);
    StrLCD("PWD Updated");
    delay_ms(1000);
    CmdLCD(CLRLCD);

    return 1;
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
					   CmdLCD(GOTO_LINE1_POS0);
						 StrLCD("ENTER HOURS(0-23)");
					  
					   						 
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
					   delay_ms(700);
						 temp_hr = temp_hr*10 + (d2-'0');  // final integer 0–23
						 if(temp_hr>=0 && temp_hr<=23)
						{
					   GetRTCTimeInfo(&hour,&min,&sec);
						 SetRTCTimeInfo(temp_hr, min, sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("HOUR UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);

						}else{
						    CmdLCD(CLRLCD);
						    StrLCD("Invalid Hrs");
							  delay_s(1);
						}						 
				 }
				 else if(ch=='2')
         {
					   temp_min=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Min(0-59)");
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
					   delay_ms(700);
						 temp_min = temp_min*10 + (d2-'0');  // final integer 0–59
						if(temp_min>=0 && temp_min<=59)
						{
					   GetRTCTimeInfo(&hour,&min,&sec);
						 SetRTCTimeInfo(hour,temp_min, sec);
					 
						 CmdLCD(CLRLCD);
						 StrLCD("MIN UPDATED");
						 delay_s(2);
						 CmdLCD(CLRLCD);
						 
						}else{
						    CmdLCD(CLRLCD);
						    StrLCD("Invalid Mins");
							  delay_s(1);
						}			
				 }
				 else if(ch=='3')
         {
					   temp_sec=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Sec(0-59)");
					   delay_s(1);
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
						  
					   CharLCD(d1);
					   delay_ms(100);
						 temp_sec = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();
					   
						 CharLCD(d2);
					   delay_ms(700);
						 temp_sec = temp_sec*10 + (d2-'0');  // final integer 0–59
						 if(temp_sec>=0 && temp_sec<=59){
							 GetRTCTimeInfo(&hour,&min,&sec);
							 SetRTCTimeInfo(hour, min, temp_sec);
						 
							 CmdLCD(CLRLCD);
							 StrLCD("Seconds UPDATED");
							 delay_s(1);
							 CmdLCD(CLRLCD);
							 
						 }else{
						    CmdLCD(CLRLCD);
						    StrLCD("Invalid sec");
							  delay_s(1);
						}			
				 }
				 else if(ch=='4')
         {
					   d=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("ENTER DATE(0-6)");
					   delay_s(1);
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d = KeyScan();              
						  
					   CharLCD(d);
					   delay_ms(700);
						 d = (d - '0'); 
					   if(d>=0 && d<=6)
						{
							 GetRTCDay(&day);
							 SetRTCDay(d);
							 CmdLCD(CLRLCD);
							 StrLCD("D-O-WEEK UPDATED");
							 delay_ms(700);
							 CmdLCD(CLRLCD);
							
						 }else{
							  CmdLCD(CLRLCD);
						    StrLCD("Invalid DayKey");
							  delay_s(1);
							  CmdLCD(CLRLCD);
							  
						 }
					   
				 }
				 else if(ch=='5')
         {
					   temp_date=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Date(1-31)");	
             delay_s(1);				   
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(100); 
						 temp_date = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(700);
						 temp_date = temp_date*10 + (d2-'0');  // final integer 0–23
						 if(temp_date>=0 && temp_date<=23){
								 GetRTCDateInfo(&date,&month,&year);
								 SetRTCDateInfo(temp_date,month,year);
							 
								 CmdLCD(CLRLCD);
								 StrLCD("DATE UPDATED");
								 delay_s(1);
								 CmdLCD(CLRLCD);
							   
						 }else{
						    CmdLCD(CLRLCD);
						    StrLCD("Invalid Date");
							  delay_s(1);
						}			
				 }
				 else if(ch=='6')
         {
					   temp_month=0;						
						 CmdLCD(CLRLCD);
						 StrLCD("Enter Month(1-12)");					   
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(100); 
						 temp_month = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(700);
						 temp_month = temp_month*10 + (d2-'0');  // final integer 0–23
						 if(temp_month>=0 && temp_month<=23){
								 GetRTCDateInfo(&date,&month,&year);
								 SetRTCDateInfo(date,temp_month,year);
								 
								 CmdLCD(CLRLCD);
								 StrLCD("Month UPDATED");
								 delay_s(1);
								 CmdLCD(CLRLCD);
							   
						 }else{
						    CmdLCD(CLRLCD);
						    StrLCD("Invalid Month");
							  delay_s(1);
						}			
				 }
				 else if(ch=='7')
         {
					   temp_yr=0;						
						 CmdLCD(CLRLCD);
					 StrLCD("Enter Year :");
             delay_s(1);					 
						 CmdLCD(GOTO_LINE2_POS0);

						 // Read first digit
						 d1 = KeyScan();              
					   CharLCD(d1);
					   delay_ms(100); 
						 temp_yr = (d1 - '0');        // convert to number

						 // Read second digit
						 d2 = KeyScan();					   
						 CharLCD(d2);
					   delay_ms(100);
						 temp_yr = temp_yr*10 + (d2-'0');  // final integer 0–23
						 
					  // Read third digit
					   d3 = KeyScan();					   
						 CharLCD(d3);
					   delay_ms(100);
						 temp_yr = temp_yr*10 + (d3-'0');
						 
						 // Read fourth digit
						 d4 = KeyScan();					   
						 CharLCD(d4);
					   delay_ms(700);
						 temp_yr = temp_yr*10 + (d4-'0');
						 if(temp_date>=0 && temp_date<=4095){
								 GetRTCDateInfo(&date,&month,&year);
								 SetRTCDateInfo(date,month,temp_yr);
							 
								 CmdLCD(CLRLCD);
								 StrLCD("YEAR UPDATED");
								 delay_s(1);
								 CmdLCD(CLRLCD);
							   
						 }else{
						    CmdLCD(CLRLCD);
						    StrLCD("Invalid Year");
							  delay_s(1);
						}			
				 }
				 else if(ch=='8')
         {
					 CmdLCD(CLRLCD);
					 return 0;
				 }
         else{
				   CmdLCD(CLRLCD);
				   StrLCD("Invalid Key");
					 delay_s(1);
					 CmdLCD(CLRLCD);
				 }				 
			 }
}
int Edit_EAT_Info(int *start_hr,int *end_hr,int *start_mn,int *end_mn)
{
        int temp_Hr,temp_mn;
        u8 d1,d2;
        char ch;
input:
        CmdLCD(CLRLCD);
        StrLCD("EDIT YOU WANT");
        delay_ms(800);
        CmdLCD(CLRLCD);

        while(1)
        {

                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("1SHr 2EdH 3SMn");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("4.EndMn 5.Ex");
                ch = KeyScan();

                if(ch=='1')
                {
                        temp_Hr=0;
                        CmdLCD(CLRLCD);
                        StrLCD("ENTER START");
                        CmdLCD(GOTO_LINE2_POS0);

                        d1=KeyScan();
                        CharLCD(d1);
                        delay_ms(100);
                        temp_Hr = d1-'0';

                        d2=KeyScan();
                        CharLCD(d2);
                        delay_s(2);
                        temp_Hr = temp_Hr*10 + (d2-'0');
                        if(temp_Hr>=0 && temp_Hr<=23)
                        {
                                *start_hr=temp_Hr;
                                CmdLCD(CLRLCD);
                                StrLCD("UPDATED");
                                delay_s(1);
                                CmdLCD(CLRLCD);
                                continue;
                        }else
                        {
                                CmdLCD(CLRLCD);
                                StrLCD("Invalid Hours");
                                delay_s(1);
                                goto input;
                        }
                }
                else if(ch=='2')
                {
                        temp_Hr=0;
                        CmdLCD(CLRLCD);
                        StrLCD("ENTER END");
                        CmdLCD(GOTO_LINE2_POS0);

                        d1=KeyScan();
                        CharLCD(d1);
                        delay_ms(100);
                        temp_Hr = d1-'0';

                        d2=KeyScan();
                        CharLCD(d2);
                        delay_s(2);
                        temp_Hr = temp_Hr*10 + (d2-'0');
                        if(temp_Hr>=0 && temp_Hr<=23)
                        {
                                *end_hr=temp_Hr;
                                CmdLCD(CLRLCD);
                                StrLCD("UPDATED");
                                delay_s(1);
                                CmdLCD(CLRLCD);
                                continue;
                        }else{
                                CmdLCD(CLRLCD);
                                StrLCD("Invalid Hours");
                                delay_s(1);
                                goto input;
                        }
                }
                if(ch=='3')
                {
                        temp_mn=0;
                        CmdLCD(CLRLCD);
                        StrLCD("ENTER START");
                        CmdLCD(GOTO_LINE2_POS0);

                        d1=KeyScan();
                        CharLCD(d1);
                        delay_ms(100);
                        temp_mn = d1-'0';

                        d2=KeyScan();
                        CharLCD(d2);
                        delay_s(2);
                        temp_mn = temp_mn*10 + (d2-'0');
                        if(temp_mn>=0 && temp_mn<=59)
                        {
                                *start_mn=temp_mn;
                                CmdLCD(CLRLCD);
                                StrLCD("UPDATED");
                                delay_s(1);
                                CmdLCD(CLRLCD);
                                continue;
                        }else
                        {
                                CmdLCD(CLRLCD);
                                StrLCD("Invalid Mins");
                                delay_s(1);
                                goto input;
                        }
                }
                else if(ch=='4')
                {
                        temp_mn=0;
                        CmdLCD(CLRLCD);
                        StrLCD("ENTER END");
                        CmdLCD(GOTO_LINE2_POS0);

                        d1=KeyScan();
                        CharLCD(d1);
                        delay_ms(100);
                        temp_mn = d1-'0';

                        d2=KeyScan();
                        CharLCD(d2);
                        delay_s(2);
                        temp_mn = temp_mn*10 + (d2-'0');
                        if(temp_mn>=0 && temp_mn<=59)
                        {
                                *end_mn=temp_mn;
                                CmdLCD(CLRLCD);
                                StrLCD("UPDATED");
                                delay_s(1);
                                CmdLCD(CLRLCD);
                                continue;
                        }else{
                                CmdLCD(CLRLCD);
                                StrLCD("Invalid Mins");
                                delay_s(1);
                                goto input;
                        }
                }
                else if(ch=='5')
                {
                        CmdLCD(CLRLCD);
                        return 0;
                }
                else
                {
                        CmdLCD(CLRLCD);
                        StrLCD("Invalid");
                        delay_s(1);
                        CmdLCD(CLRLCD);
                }
        }
}
/*continue; inside the success block:

StrLCD("UPDATED");
delay_s(1);
CmdLCD(CLRLCD);
continue;

The loop jumps back to the top of while()
It does not check remaining conditions
So "Invalid" message is avoided.*/
