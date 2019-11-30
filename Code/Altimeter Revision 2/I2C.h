/*
 * I2C.h
 *
 *  Created on: Nov 14, 2019
 *      Author: xutao
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void measurement_sequence(uint8_t address, uint8_t reg, uint8_t msb, uint8_t lsb);

void get_id( uint8_t address, uint8_t msb, uint8_t lsb);

void read_probing(uint8_t address, uint8_t reg);

void config_i2c(void); // configures to MSP432 to act in master mode

void write_register(uint8_t address, uint8_t reg, uint8_t value);

uint8_t read_register(uint8_t address, uint8_t reg);

void send_start(void);

void send_stop(void);

void set_as_transmitter(void);

void set_as_receiver(void);

/* change the slave address being communicated with */
void set_i2c_address(uint8_t addr);

void set_i2c_byte_counter(uint8_t n);

void send_data(uint8_t adrress, uint8_t data);

uint8_t read_data(uint8_t address);

#endif /* I2C_H_ */
