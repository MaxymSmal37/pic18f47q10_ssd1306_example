# SSD1306 OLED Library for PIC18

A simple SSD1306 OLED driver for the **PIC18F47Q10** microcontroller using **hardware I2C**.

---

## Features

- Supports 128x32 SSD1306 OLED via I2C  
- Page, horizontal, and vertical memory addressing  
- Pixel drawing, clear screen, contrast & inversion control  
- Demo animation included  

---

## Files

- `main.c` – Example usage with hardware initialization  
- `i2c_hw.c/h` – Low-level I2C functions using SSP1  
- `ssd1306_display.c/h` – SSD1306 driver logic  

---

## Wiring

| OLED Pin | PIC18F47Q10 |
|----------|-------------|
| VCC      | 5V          |
| GND      | GND         |
| SDA      | RB2         |
| SCL      | RB1         |

> Weak pull-ups are enabled in software. Add 4.7kΩ pull-up resistors if needed.

---

## Quick Start

1. Add files to your MPLAB X project  
2. Connect the OLED display  
3. Flash the MCU  
4. A bar animation will appear on the screen at boot  

---

## Usage Example

```c
ssd1306_InitDisplay();       // Initialize display
ssd1306_SetPixel(10, 10, 1); // Draw a pixel
ssd1306_SetDisplay();        // Refresh the screen
ssd1306_DemoAnimation();     // Run animation
