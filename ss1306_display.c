
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ss1306_display.h"
#include "i2c_hw.h"

uint8_t buffer[SSD1306_WIDTH * (SSD1306_HEIGHT / 8)];

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

  I2C1_sendData(0x00); // Control byte for command
  if (I2C1_getAckstatBit())
  {
    I2C1_stopCondition();
    I2C1_close();
  }

  I2C1_sendData(command);

end:
  I2C1_stopCondition();
  I2C1_close();
}

void ssd1306_WriteData(uint8_t *data, size_t size)
{
  I2C1_open();
  I2C1_startCondition();

  I2C1_sendData((SSD1306_I2C_ADDR << 1) & ~0x01);
  if (I2C1_getAckstatBit())
    goto end;

  I2C1_sendData(0x40); // Control byte for data
  if (I2C1_getAckstatBit())
    goto end;

  for (size_t i = 0; i < size; i++)
  {
    I2C1_sendData(data[i]);
    if (I2C1_getAckstatBit())
      break;
  }

end:
  I2C1_stopCondition();
  I2C1_close();
}

void ssd1306_InitDisplay(void)
{
  ssd1306_WriteCommand(0xAE); // DISPLAYOFF
  ssd1306_WriteCommand(0xD5);
  ssd1306_WriteCommand(0x80); // CLOCKDIV
  ssd1306_WriteCommand(0xA8);
  ssd1306_WriteCommand(0x1F); // MULTIPLEX (for 128x32)
  ssd1306_WriteCommand(0xD3);
  ssd1306_WriteCommand(0x00); // OFFSET
  ssd1306_WriteCommand(0x40); // STARTLINE
  ssd1306_WriteCommand(0x8D);
  ssd1306_WriteCommand(0x14); // CHARGEPUMP (internal)
  ssd1306_WriteCommand(0x20);
  ssd1306_WriteCommand(0x00); // MEMORYMODE (horizontal)
  ssd1306_WriteCommand(0xA1); // SEGREMAP
  ssd1306_WriteCommand(0xC8); // COMSCANDEC
  ssd1306_WriteCommand(0xDA);
  ssd1306_WriteCommand(0x02); // COMPINS (128x32)
  ssd1306_WriteCommand(0x81);
  ssd1306_WriteCommand(0x8F); // CONTRAST (default)
  ssd1306_WriteCommand(0xD9);
  ssd1306_WriteCommand(0xF1); // PRECHARGE (internal)
  ssd1306_WriteCommand(0xDB);
  ssd1306_WriteCommand(0x40); // VCOMDETECT ? ? ???? ???? 0x20!
  ssd1306_WriteCommand(0xA4); // DISPLAYALLON_RESUME
  ssd1306_WriteCommand(0xA6); // NORMALDISPLAY
  ssd1306_WriteCommand(0x2E); // DEACTIVATE_SCROLL
  ssd1306_WriteCommand(0xAF); // DISPLAYON

  ssd1306_ClearDisplay();
  ssd1306_SetDisplay();
}

void ssd1306_SetDisplay(void)
{
  for (uint8_t page = 0; page < (SSD1306_HEIGHT / 8); page++)
  {
    ssd1306_WriteCommand(0xB0 + page);
    ssd1306_WriteCommand(0x00); // Column low
    ssd1306_WriteCommand(0x10); // Column high

    ssd1306_WriteData(&buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
  }
}

void ssd1306_ClearDisplay(void)
{
  for (uint8_t page = 0; page < (SSD1306_HEIGHT / 8); page++)
  {
    buffer[page] = 0x00;
  }
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

void ssd1306_DrawPixel(int16_t x, int16_t y, uint8_t color)
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
