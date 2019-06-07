#include <htc.h>
#include<xc.h>

#if defined(WDTE_OFF)
__CONFIG(WDTE_OFF & LVP_OFF);
#elif defined (WDTDIS)
__CONFIG(WDTDIS & LVPDIS);
#endif
#define _XTAL_FREQ 4000000



void Lcd_data(char a)
{
    PORTD = a;
    RC5 = 1;
    
    RC4 = 1;
    __delay_ms (10);
    RC4 = 0;
}

void Lcd_cmd(char a)
{
	PORTD = a;
    RC5 = 0;
    
    RC4 = 1;
    __delay_ms (10);
    RC4 = 0;      
}

void initialLCD()
{
    TRISD = 0X00;
    TRISC5 = 0;
    TRISC4 = 0;
    
    __delay_ms(20);
    
   Lcd_cmd(0x30);
    __delay_ms(5);
   Lcd_cmd(0x30);
    __delay_ms(1);
    Lcd_cmd(0x30);
            
    Lcd_cmd(0x38);
    __delay_ms (5);
    Lcd_cmd(0x08);
    __delay_ms (5);
    Lcd_cmd(0x01);
    Lcd_cmd(0x06);
    __delay_ms (5);
    
    Lcd_cmd(0x0C);
    __delay_ms (5);
}

void main(void)
{
 unsigned int a;
 unsigned int i,j;
 unsigned char k[5];
 unsigned char channel=0;
  
TRISB=0;
TRISC=0;
TRISA=0xFF;

ANSEL=1;
ADCON0=0xC1;
ADCON1=0x80;

initialLCD ();
__delay_ms (10);
 if(channel<13)
{ADCON0&=0XC5;
  ADCON0|=channel<<4;
  __delay_ms(2);
 GO_nDONE=1;
 while(GO_nDONE=1);
 j=((ADRESH<<8)+ADRESL); 
 a=j*0.0049;

 for(i=0;i<=2;i++)    //to convert o integer to ASCII
 { k[i]=a%10;
   a=a/10;
 }

 
 for(i=2;i<=0;i--)
 {Lcd_data ( k[i]+0x30);
  
 }
}
}
