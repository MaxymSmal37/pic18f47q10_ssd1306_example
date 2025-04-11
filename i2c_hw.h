/*
 * File:   i2c_hw.h
 * Author: maxymsmal
 *
 * Created on April 10, 2025, 10:32 PM
 */
#ifndef I2C_HW_H
#define I2C_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define I2C_SLAVE_ADDR 0x32

void I2C1_open(void);

void I2C1_close(void);

void I2C1_startCondition(void);

void I2C1_stopCondition(void);

void I2C1_sendData(uint8_t data);

void I2C1_interruptFlagPolling(void);

uint8_t I2C1_getAckstatBit(void);

void I2C1_write1ByteRegister(uint8_t address, uint8_t reg, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* I2C_HW_H */
