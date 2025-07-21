/*
 * i2c.h
 *
 *  Created on: 17 Jul 2025
 *      Author: Step
 */

#ifndef I2C_H_
#define I2C_H_
#include "stdint.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "sl_i2cspm.h"

I2C_TransferReturn_TypeDef i2cWrite(uint16_t addr, uint8_t* data, uint16_t length);
I2C_TransferReturn_TypeDef i2cRead(uint16_t addr, uint8_t* buffer, uint16_t length);
void I2CSPM_DeInit(I2CSPM_Init_TypeDef *init);

#endif /* I2C_H_ */
