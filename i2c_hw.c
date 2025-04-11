#include <xc.h>
#include "i2c_hw.h"

void I2C1_interruptFlagPolling(void)
{
  while (!PIR3bits.SSP1IF)
  {
    ;
  }

  PIR3bits.SSP1IF = 0;
}

void I2C1_open(void)
{
  PIR3bits.SSP1IF = 0;

  SSP1CON1bits.SSPEN = 1;
}

void I2C1_close(void)
{
  SSP1CON1bits.SSPEN = 0;
}

void I2C1_startCondition(void)
{
  SSP1CON2bits.SEN = 1;

  I2C1_interruptFlagPolling();
}

void I2C1_stopCondition(void)
{
  SSP1CON2bits.PEN = 1;

  I2C1_interruptFlagPolling();
}

void I2C1_sendData(uint8_t byte)
{
  SSP1BUF = byte;
  I2C1_interruptFlagPolling();
}

uint8_t I2C1_getAckstatBit(void)
{
  return SSP1CON2bits.ACKSTAT;
}

void I2C1_write1ByteRegister(uint8_t address, uint8_t reg, uint8_t data)
{
  uint8_t writeAddress = (address << 1) & ~0x01;

  I2C1_open();
  I2C1_startCondition();

  I2C1_sendData(writeAddress);
  if (I2C1_getAckstatBit())
  {
    return;
  }

  I2C1_sendData(reg);
  if (I2C1_getAckstatBit())
  {
    return;
  }

  I2C1_sendData(data);
  if (I2C1_getAckstatBit())
  {
    return;
  }

  I2C1_stopCondition();
  I2C1_close();
}