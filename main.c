/*
 * File:   main.c
 * Author: maxymsmal
 *
 * Created on April 9, 2025, 11:25 PM
 */
#pragma config WDTE = OFF /* WDT operating mode->WDT Disabled */
#pragma config LVP = ON   /* Low-voltage programming enabled, RE3 pin is MCLR */

#include <pic18.h>
#include <xc.h>
#include "i2c_hw.h"
#include "ss1306_display.h"

#define _XTAL_FREQ 32000000UL

void main(void)
{
  OSCCON1bits.NOSC = 0x6;
  OSCFRQbits.FRQ3 = 0x08;

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

  /// Clock = F_OSC / (4 * (SSP1ADD + 1))
  SSP1CON1bits.SSPM3 = 1;

  // Set the boud rate devider
  SSP1ADD = 0x9F;

  __delay_ms(100);

  ssd1306_InitDisplay();

  LATEbits.LATE0 = 1;

  __delay_ms(100);

  for (int x = 10; x < 100; x++)
  {
    for (int y = 10; y < 20; y++)
    {
      ssd1306_DrawPixel(x, y, 1);
    }
  }

  ssd1306_SetDisplay();

  while (1) { }
}