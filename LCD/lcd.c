//lcd.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "lcd_defines.h"

void delay_us(unsigned int dlyus){
  dlyus *=12;
  while(dlyus--);
}
void delay_ms(unsigned int dlyms){
  dlyms *=12000;
  while(dlyms--);
}
void delay_s(unsigned int dlys){
  dlys *=12000000;
  while(dlys--);
}

void WriteLCD(u8 byte)
{
	//write onto data pins
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	//enable write operations
	IOCLR0=1<<LCD_RW;
	//give high to low signal
	IOSET0=1<<LCD_EN;
	//delay >=450ns
	delay_us(1);
	IOCLR0=1<<LCD_EN;
	delay_ms(2);
}

void CmdLCD(u8 cmd)
{
	//select cmd/inst reg
	IOCLR0=1<<LCD_RS;
	//write cmd to cmd/inst reg
	WriteLCD(cmd);
}

void InitLCD(void)
{
	delay_ms(15);
	//cfg LCD data pins p0.8 to p0.15 as gpio out
	WRITEBYTE(IODIR0,LCD_DATA,0xFF);
	//cfg LCD rs,rw,en pins as gpio out
	IODIR0|=1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
  
	CmdLCD(0x30);
	delay_ms(4);
	delay_us(100);
  CmdLCD(0x30);
  delay_us(100);
  CmdLCD(0x30);
  CmdLCD(MODE_8BIT_2LINE);
  CmdLCD(DSP_ON_CUR_OFF);
  CmdLCD(CLRLCD);
 	CmdLCD(SHIFT_CUR_RIGHT);
}

void CharLCD(u8 asciiVal)
{
	//select data reg
	IOSET0=1<<LCD_RS;
	//write to ddram via data reg
	WriteLCD(asciiVal);
}

void StrLCD(s8 *str)
{
	while(*str)
		CharLCD(*str++);
}

void U32LCD(u32 num)
{
  u8 digit[10];
  s32 i=0;
  if(num==0)
	{
		CharLCD('0');
  }		
	else
	{
		while(num>0)
		{
			digit[i++]=(num%10)+'0';
			num/=10;
		}
		for(--i ;i>=0; i--)
		   CharLCD(digit[i]);
	}
}

void S32LCD(s32 num)
{
  if(num<0)
  {
		CharLCD('-');
		num=-num;
  }		
	U32LCD(num);
}
void F32LCD(f32 fNum,u32 nDP)
{
	u32 num;
	if(fNum<(f32)0.0)
	{
		CharLCD('-');
		fNum=-fNum;
	}
  num=fNum;
  U32LCD(num);
  CharLCD('.');
  while(nDP>0)
  {
    fNum=(fNum-num)*10;		
		num=fNum;
		CharLCD(num+48);
		nDP--;
	}	
}
void BuildCGRAM(u8 *p,u8 nBytes)
{
	u32 i;
	//point to cgram start
	CmdLCD(GOTO_CGRAM_START);
	//select data reg
	IOSET0=1<<LCD_RS;
	
	//write to cgram via data reg
	for(i=0;i<nBytes;i++)
	{
    WriteLCD(p[i]);		
	}	
	//point back to ddram start
	CmdLCD(GOTO_LINE1_POS0);
}
