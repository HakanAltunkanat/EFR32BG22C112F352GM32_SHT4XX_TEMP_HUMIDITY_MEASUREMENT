/*
 * sht40.c
 *
 *  Created on: 17 Jul 2025
 *      Author: Step
 */


#include "sht40.h"
#include "i2c.h"
#include "stdint.h"
#include "sl_sleeptimer.h"
#define sht40_Addr 0x44
#define sht40_MeasureHighPrecision 0xFD

#define sht40_MeasureHighPrecisionPtr (&(uint8_t){sht40_MeasureHighPrecision})
int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);
void delayMs(uint32_t delay)
{
  sl_sleeptimer_init();
  sl_sleeptimer_delay_millisecond(delay);

}

SHT40_Status_t sht40_Measure(float *temperature, float *humidity)
{
  I2C_TransferReturn_TypeDef status;
  uint16_t tTicks=0, rhTicks=0; // Variables to store ticks
  uint8_t checkSum_t=0, checkSum_rh=0; // Variables to store checksums
  uint8_t rxBuffer[6];
  status=i2cWrite(sht40_Addr<<0x01, sht40_MeasureHighPrecisionPtr, 1);
  delayMs(10);
  status=i2cRead(sht40_Addr<<0x01,rxBuffer,6);
  for(int i=0; i<6; i++)
    {
      SEGGER_RTT_printf(0, "%u - ",rxBuffer[i]);
    }
  SEGGER_RTT_printf(0, "\n");
  tTicks=rxBuffer[0]*256+rxBuffer[1];
  checkSum_t=rxBuffer[2];
  rhTicks=rxBuffer[3]*256+rxBuffer[4];
  checkSum_rh=rxBuffer[5];
  *temperature=-45+175*(((float)(tTicks))/65535); // Calculate temperature
  *humidity=-6+125*(((float)(rhTicks))/65535); // Calculate humidity
  if(status!= i2cTransferDone)
    return sht40_OK;
  else
   return sht40_Error;
}
