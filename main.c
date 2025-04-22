/*
 * File:   main.c
 * Author: maxymsmal
 *
 * Created on April 9, 2025, 11:25 PM
 */

// Config bytes
#pragma config WDTE = OFF
#pragma config LVP = ON

#include <pic18.h>
#include <xc.h>
#include "i2c_hw.h"
#include "ssd1306_display.h"

#define _XTAL_FREQ 32000000UL

void hw_init(void);

void main(void)
{
  hw_init();
 
  __delay_ms(100);

  LATEbits.LATE0 = 0;

  ssd1306_InitDisplay();

  LATEbits.LATE0 = 1;

  __delay_ms(100);

  while (1) { 
    ssd1306_DemoAnimation();
    __delay_ms(1000);
  }
}

void hw_init(void)
{
  OSCCON1bits.NOSC = 0x6;
  OSCFRQbits.FRQ3 = 0x08;
 // OSCFRQ = 0x08;


  ANSELBbits.ANSELB1 = 0;
  ANSELBbits.ANSELB2 = 0;

  TRISBbits.TRISB5 = 0;
  TRISBbits.TRISB4 = 0;

  TRISEbits.TRISE0 = 0; 
  TRISEbits.TRISE1 = 0; 

  LATEbits.LATE1 = 1;
  LATEbits.LATE0 = 0;

  WPUBbits.WPUB1 = 1;
  WPUBbits.WPUB2 = 1;

  SSP1CLKPPS = 0x09;
  RB1PPS = 0x0F;

  SSP1DATPPS = 0x0A;
  RB2PPS = 0x10;
  
  SSP1CON1bits.SSPM3 = 1; /// Clock = F_OSC / (4 * (SSP1ADD + 1))
  LATEbits.LATE0 = 1;

  SSP1ADD = 0x13;//0x9F;   // Set the boud rate devider
}