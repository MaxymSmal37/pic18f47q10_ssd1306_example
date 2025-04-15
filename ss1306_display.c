
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ss1306_display.h"
#include "i2c_hw.h"

uint8_t buffer[SSD1306_WIDTH * (SSD1306_HEIGHT / 8)];


void ssd1306_InitDisplay(void)
{
  ssd1306_WriteCommand(0xAE); 
  ssd1306_WriteCommand(0xD5);
  ssd1306_WriteCommand(0x80);
  ssd1306_WriteCommand(0xA8);
  ssd1306_WriteCommand(0x1F); 
  ssd1306_WriteCommand(0xD3);
  ssd1306_WriteCommand(0x00);
  ssd1306_WriteCommand(0x40);
  ssd1306_WriteCommand(0x8D);
  ssd1306_WriteCommand(0x14);
  ssd1306_WriteCommand(0x20);
  ssd1306_WriteCommand(0x00);
  ssd1306_WriteCommand(0xA1);
  ssd1306_WriteCommand(0xC8);
  ssd1306_WriteCommand(0xDA);
  ssd1306_WriteCommand(0x02);
  ssd1306_WriteCommand(0x81);
  ssd1306_WriteCommand(0x8F);
  ssd1306_WriteCommand(0xD9);
  ssd1306_WriteCommand(0xF1);
  ssd1306_WriteCommand(0xDB);
  ssd1306_WriteCommand(0x40);
  ssd1306_WriteCommand(0xA4);
  ssd1306_WriteCommand(0xA6);
  ssd1306_WriteCommand(0x2E);
  ssd1306_WriteCommand(0xAF);

  ssd1306_ClearDisplay();
  ssd1306_SetDisplay();
}

void ssd1306_WriteCommand(uint8_t command)
{
  I2C1_open();
  I2C1_startCondition();

  I2C1_sendData((SSD1306_I2C_ADDR << 1) & ~0x01);
  if (I2C1_getAckstatBit())
  {
    I2C1_stopCondition();
    I2C1_close();
  }

  I2C1_sendData(0x00);
  if (I2C1_getAckstatBit())
  {
    I2C1_stopCondition();
    I2C1_close();
  }

  I2C1_sendData(command);
}

void ssd1306_WriteData(uint8_t *data, size_t size)
{
  I2C1_open();
  I2C1_startCondition();

  I2C1_sendData((SSD1306_I2C_ADDR << 1) & ~0x01);

  if (I2C1_getAckstatBit()){
    I2C1_stopCondition();
    I2C1_close();
  }

  I2C1_sendData(0x40);
  if (I2C1_getAckstatBit()) {
    I2C1_stopCondition();
    I2C1_close();
  }

  for (size_t i = 0; i < size; i++) {
    I2C1_sendData(data[i]);

    if (I2C1_getAckstatBit()) {
      break;
    }
  }
}

void ssd1306_SetDisplay(void)
{
  for (uint8_t page = 0; page < (SSD1306_HEIGHT / 8); page++)
  {
    ssd1306_WriteCommand(0xB0 + page);
    ssd1306_WriteCommand(0x00);
    ssd1306_WriteCommand(0x10);

    ssd1306_WriteData(&buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
  }
}

void ssd1306_SetDisplay_Horisontal(void)
{
  ssd1306_WriteCommand(0x20);                 // Memory Addressing Mode
  ssd1306_WriteCommand(0x00);                 // Horizontal Addressing Mode

  ssd1306_WriteCommand(0x21);                 // column address
  ssd1306_WriteCommand(0);                    // Start column
  ssd1306_WriteCommand(SSD1306_WIDTH - 1);
  
  ssd1306_WriteCommand(0x22); // Set page address
  ssd1306_WriteCommand(0);    // Start page
  ssd1306_WriteCommand((SSD1306_HEIGHT / 8) - 1); // End page

  ssd1306_WriteData(buffer, SSD1306_WIDTH * (SSD1306_HEIGHT / 8));
}

void ssd1306_SetDisplay_Vertical(void)
{
    ssd1306_WriteCommand(0x20);                 // Memory Addressing Mode
    ssd1306_WriteCommand(0x01);                 // Vertical Addressing Mode
    
    ssd1306_WriteCommand(0x21);                 // column address
    ssd1306_WriteCommand(0);                    // Start column
    ssd1306_WriteCommand(SSD1306_WIDTH - 1);
    
    ssd1306_WriteCommand(0x22); // Set page address
    ssd1306_WriteCommand(0);    // Start page
    ssd1306_WriteCommand((SSD1306_HEIGHT / 8) - 1); // End page

    ssd1306_WriteData(buffer, SSD1306_WIDTH * (SSD1306_HEIGHT / 8));
}

void ssd1306_ClearDisplay(void)
{
  memset(buffer, 0, sizeof(buffer));
}

void ssd1306_EnableDisplay(uint8_t state)
{
  ssd1306_WriteCommand(state ? 0xAF : 0xAE);
}

void ssd1306_SetContrast(uint8_t value)
{
  ssd1306_WriteCommand(0x81);
  ssd1306_WriteCommand(value);
}

void ssd1306_SetInversionMode(uint8_t setInversion)
{
  ssd1306_WriteCommand(setInversion ? 0xA7 : 0xA6);
}

void ssd1306_SetEntireMode(uint8_t state)
{
  ssd1306_WriteCommand(state ? 0xA5 : 0xA4);
}

void ssd1306_SetPixel(int16_t x, int16_t y, uint8_t color)
{
  if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT)
    return;

  uint16_t byteIndex = x + (y / 8) * SSD1306_WIDTH;
  uint8_t bitMask = 1 << (y % 8);

  if (color)
    buffer[byteIndex] |= bitMask;
  else
    buffer[byteIndex] &= ~bitMask;
}

void ssd1306_DemoAnimation(void) {
    for (int i = 0; i < 120; i += 5)
    {
        ssd1306_ClearDisplay();

        for (int x = i; x < i + 30 && x < 128; x++)
        {
            for (int y = 5; y < 25; y++)
            {
                ssd1306_SetPixel(x, y, 1);
            }
        }

        ssd1306_SetDisplay();
        //ssd1306_SetDisplay_Horisontal();
        //ssd1306_SetDisplay_Vertical();
    }
}

