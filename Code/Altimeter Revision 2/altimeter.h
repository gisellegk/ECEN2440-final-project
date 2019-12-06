/*
 * altimeter.h
 *
 *  Created on: Dec 2, 2019
 *      Author: Giselle
 */




#ifndef ALTIMETER_H_
#define ALTIMETER_H_

#include "msp.h"
#include "I2C.h"
#include <stdlib.h>

#define ICP10111 0x63
#define WRITE_HEADER 0xC6
#define PRESSURE_MEASUREMENT_MSB 0x48
#define PRESSURE_MEASUREMENT_LSB 0xA3
#define READ_HEADER 0xC7
#define ID_MSB 0xEF
#define ID_LSB 0xC8

uint8_t request_id(void);

void request_pressure_measurement(uint8_t *pressure);
void request_full_measurement(uint8_t *data);
void get_calibration(uint8_t cn[], uint8_t address);
void request_id(uint8_t id[]);


#endif /* ALTIMETER_H_ */
