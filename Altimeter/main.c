/*****************************************************************************
*
* Copyright (C) 2013 - 2017 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
#include "I2C.h"
#include <stdint.h>
#include <stdio.h>

#define ICP10111 0x63
#define WRITE_HEADER 0xC6
#define PRESSURE_MEASUREMENT_MSB 0x48
#define PRESSURE_MEASUREMENT_LSB 0xA3
#define READ_HEADER 0xC7

int main(void)
{
    config_i2c();
    send_start();

    send_data(ICP10111, WRITE_HEADER);

    send_data(ICP10111, PRESSURE_MEASUREMENT_MSB);

    send_data(ICP10111, PRESSURE_MEASUREMENT_LSB);

    send_data(ICP10111, READ_HEADER);

    uint8_t ACK = read_data(ICP10111);

    while(ACK) {
        send_data(ICP10111, READ_HEADER);
        ACK = read_data(ICP10111);
    }

    uint8_t pressure_mmsb = read_data(ICP10111);
    uint8_t pressure_mlsb = read_data(ICP10111);
    uint8_t pressure_crc = read_data(ICP10111);

    uint8_t pressure_lmsb = read_data(ICP10111);
    uint8_t pressure_llsb = read_data(ICP10111);
    pressure_crc = read_data(ICP10111); // Disregard llsb

    P2->DIR |= BIT4;

    if (pressure_mmsb != 0xFF &&
        pressure_mlsb != 0xFF &&
        pressure_lmsb != 0xFF) {
        P2->OUT = BIT4;
    }

    return 0;
}
