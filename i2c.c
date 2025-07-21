/*

 */

#include "i2c.h"
#include "em_i2c.h"
#include "stddef.h"
#include "sl_i2cspm.h"
#include "em_cmu.h"

I2C_TransferReturn_TypeDef i2cWrite(uint16_t addr, uint8_t* data, uint16_t length)
{
  I2C_TransferSeq_TypeDef seq={0};
  seq.addr=addr;
  seq.flags=I2C_FLAG_WRITE;
  seq.buf[0].data=data;
  seq.buf[0].len=length;
  return I2CSPM_Transfer(I2C0, &seq);
}


I2C_TransferReturn_TypeDef i2cRead(uint16_t addr, uint8_t* buffer, uint16_t length)
{
  I2C_TransferSeq_TypeDef seq={0};
  seq.addr=addr;
  seq.flags=I2C_FLAG_READ;
  seq.buf[0].data=buffer;
  seq.buf[0].len=length;
  return I2CSPM_Transfer(I2C0, &seq);
}

void I2CSPM_DeInit(I2CSPM_Init_TypeDef *init)
{
  CMU_Clock_TypeDef i2cClock;
  I2C_Init_TypeDef i2cInit;

  EFM_ASSERT(init != NULL);
  I2C_Enable(init->port, false);
  i2cInit.enable = false;
  i2cInit.master = true;
  i2cInit.freq = init->i2cMaxFreq;
  i2cInit.refFreq = init->i2cRefFreq;
  i2cInit.clhr = init->i2cClhr;

  I2C_Init(init->port, &i2cInit);

#if defined (_I2C_ROUTEPEN_MASK)
  init->port->ROUTEPEN  = 0;
  init->port->ROUTELOC0 = 0;
#elif defined (_I2C_ROUTE_MASK)
  init->port->ROUTE =0;
#else

#endif

  GPIO_PinModeSet(init->sclPort, init->sclPin, gpioModeDisabled, 0);
  GPIO_PinModeSet(init->sdaPort, init->sdaPin, gpioModeDisabled, 0);


  if (false) {
#if defined(I2C0)
  } else if (init->port == I2C0) {
    i2cClock = cmuClock_I2C0;
#endif
#if defined(I2C1)
  } else if (init->port == I2C1) {
    i2cClock = cmuClock_I2C1;
#endif
#if defined(I2C2)
  } else if (init->port == I2C2) {
    i2cClock = cmuClock_I2C2;
#endif
  } else {
    /* I2C clock is not defined */
    EFM_ASSERT(false);
    return;
  }
  CMU_ClockEnable(i2cClock, false);
#if defined(_CMU_HFPERCLKEN0_MASK)
  CMU_ClockEnable(cmuClock_HFPER, false);
#endif

}
