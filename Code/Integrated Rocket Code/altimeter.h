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

#define OTP_SET_UP_1 0xC5
#define OTP_SET_UP_2 0x95
#define OTP_SET_UP_3 0x00
#define OTP_SET_UP_4 0x66
#define OTP_SET_UP_5 0x9C

#define OTP_READ_MSB 0xC7
#define OTP_READ_LSB 0xF7

void request_id(uint8_t id[]);
void request_pressure_measurement(uint8_t *pressure);
void request_full_measurement(uint8_t *data);
void get_calibration(uint8_t *cn, uint8_t address);


#endif /* ALTIMETER_H_ */
