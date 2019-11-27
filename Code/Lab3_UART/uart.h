/*
 * uart.h
 *
 *  Created on: Oct 14, 2019
 *      Author: Giselle
 */

#ifndef UART_H_
#define UART_H_

#define BUFFER_MAX 10
int buffer_size; //index of the last entry in the buffer + 1. 0 means it's empty.
int buffer[BUFFER_MAX];

void init_buffer();
void config_uart(uint16_t baud);

void enable_uart();
void disable_uart();
void enable_interrupts();
int write_uart(uint8_t byte);



#endif /* UART_H_ */
