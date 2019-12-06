/*
 * uart.h
 *
 *  Created on: Oct 14, 2019
 *      Author: Giselle
 */

#ifndef TEENSY_UART_H_
#define TEENSY_UART_H_

#define TEENSY_BUFFER_MAX 1
#define TEENSY_LOG_LENGTH 9


//TODO: Convert this to a circular buffer.
int teensy_buffer_size; //index of the last entry in the buffer + 1. 0 means it's empty.
uint8_t teensy_buffer[TEENSY_BUFFER_MAX][TEENSY_LOG_LENGTH];
int teensy_ready;

uint8_t teensy_uart_state; // 0, 1, 2....TEENSY_LOG_LENGTH-1: transmit byte X. TEENSY_LOG_LENGTH: idle.

void init_teensy_vars();
void config_teensy_uart(uint16_t baud);

void enable_teensy_uart();
void disable_teensy_uart();
void enable_teensy_interrupts();
int write_altitude(uint8_t byte0, uint8_t byte1, uint8_t byte2);
int write_data(uint8_t alt0, uint8_t alt1, uint8_t crc_alt0, uint8_t alt2, uint8_t alt3, uint8_t crc_alt1, uint8_t temp0, uint8_t temp1, uint8_t crc_temp);
int write_part_number(uint8_t byte0, uint8_t byte1, uint8_t crc);
int write_calibration(uint8_t id, uint8_t byte0, uint8_t byte1, uint8_t crc);

#endif /* TEENSY_UART_H_ */
