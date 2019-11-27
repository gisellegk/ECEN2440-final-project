/*
 * uart.h
 *
 *  Created on: Oct 14, 2019
 *      Author: Giselle
 */

#ifndef UART_H_
#define UART_H_

#define TEENSY_BUFFER_MAX 10
int teensy_buffer_size; //index of the last entry in the buffer + 1. 0 means it's empty.
uint8_t teensy_buffer[TEENSY_BUFFER_MAX][3];
int teensy_ready;

uint8_t teensy_uart_state; // 0, 1, 2: transmit byte X. 3: idle.

void init_teensy_vars();
void config_teensy_uart(uint16_t baud);

void enable_teensy_uart();
void disable_teensy_uart();
void enable_teensy_interrupts();
int write_teensy(uint8_t byte);



#endif /* UART_H_ */
