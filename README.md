# PIC18 libraty for SSD1306 OLED Display

## Objective

This repository contains bare-metal C code for interfacing a **0.91" SSD1306 OLED display** using I2C on a **PIC18F47Q10** microcontroller.  
The example initializes the display and demonstrates basic drawing functionality including a simple pixel animation.

## Related Documentation

- [PIC18F47Q10 Datasheet](https://www.microchip.com/en-us/product/PIC18F47Q10)
- [SSD1306 OLED Display Datasheet (Adafruit)](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
- [TB3261 - Writing C Code for PIC18](https://www.microchip.com/wwwappnotes/appnotes.aspx?appnote=en1002117)

## Software Used

- [MPLAB® X IDE 6.0 or newer](https://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® XC8 Compiler 2.40 or newer](https://www.microchip.com/mplab/compilers)
- [Microchip Code Configurator (optional)](https://www.microchip.com/mplab/mplab-code-configurator)

## Hardware Used

- [PIC18F47Q10 Curiosity Nano](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
- 0.91" I2C SSD1306 OLED Display (128x32 or 128x64)
- Breadboard, jumper wires

---

## Setup

**Development board configuration:**

| Pin        | Function       | Notes             |
|------------|----------------|-------------------|
| RB1        | SDA (I2C Data) | External pull-up  |
| RB2        | SCL (I2C Clock)| External pull-up  |
| RE0        | Status LED     | Indicates init status |
| RE1        | Display enable | Optional GPIO     |

**Oscillator Settings:**
- Oscillator Select: HFINTOSC
- Internal Clock Frequency: 32 MHz
- Clock Divider: 1:1

**MSSP1 (I2C) Settings:**
- Enabled in Master mode
- Clock rate ~100kHz (via `SSP1ADD`)
- SDA: RB1
- SCL: RB2

## Operation

1. Clone or download the repository.
2. Open the MPLAB X project or import the `.c`/`.h` files into your own project.
3. Connect the OLED’s VCC, GND, SDA, and SCL to the Curiosity Nano.
4. Build and flash the firmware.
5. After reset:
   - The OLED initializes.
   - A block animation scrolls across the screen.

---

## Function Overview

| Function | Description |
|----------|-------------|
| `ssd1306_InitDisplay()` | Initializes OLED with command sequence |
| `ssd1306_SetPixel(x, y, color)` | Set or clear a pixel |
| `ssd1306_SetDisplay()` | Flush buffer to OLED |
| `ssd1306_DemoAnimation()` | Runs scrolling animation |
| `ssd1306_SetDisplay_Horisontal()` | Uses horizontal addressing mode |
| `ssd1306_SetDisplay_Vertical()` | Uses vertical addressing mode |

---

# SSD1306 to PIC18F47Q10 Wiring

## Wiring Details:
- **SSD1306 VCC** -> 3.3V / 5V
- **SSD1306 GND** -> GND
- **SSD1306 SCL** -> RB2 (SCL)
- **SSD1306 SDA** -> RB1 (SDA)

**Note:** Use 4.7kΩ–10kΩ pull-up resistors on SDA and SCL.

---

## Summary

This project provides a clean example for driving SSD1306 OLED displays with the MSSP I2C module of PIC18F microcontrollers.  
It is suitable for quick prototyping, educational use, or integration into larger embedded applications.
