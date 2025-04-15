
#ifndef SS1306_DISPLAY_H
#define SS1306_DISPLAY_H

#include <stdint.h>
#include <stddef.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 32

#define SSD1306_I2C_ADDR 0x3C

void ssd1306_InitDisplay(void);
void ssd1306_WriteCommand(uint8_t command);
void ssd1306_WriteData(uint8_t* data, size_t size);

void ssd1306_ClearDisplay(void);
void ssd1306_SetDisplay(void);
void ssd1306_SetDisplay_Horisontal(void);
void ssd1306_SetDisplay_Vertical(void);

void ssd1306_EnableDisplay(uint8_t state);
void ssd1306_SetContrast(uint8_t value);
void ssd1306_SetInversionMode(uint8_t setInversion);
void ssd1306_SetEntireMode(uint8_t state);

void ssd1306_SetPixel(int16_t x, int16_t y, uint8_t color);
void ssd1306_DemoAnimation(void);

#endif // SS1306_DISPLAY_H
