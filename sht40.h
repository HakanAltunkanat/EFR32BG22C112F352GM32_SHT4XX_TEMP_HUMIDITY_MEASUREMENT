/*
 * sht40.h
 *
 *  Created on: 17 Jul 2025
 *      Author: Step
 */

#ifndef SHT40_H_
#define SHT40_H_

typedef enum {
  sht40_Error,
  sht40_OK
} SHT40_Status_t;

SHT40_Status_t sht40_Measure(float *temperature, float *humidity);
#endif /* SHT40_H_ */
