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
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P2->DIR |= BIT4;
    P2->OUT |= BIT4;

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

    if (pressure_mmsb != 0xFF &&
        pressure_mlsb != 0xFF &&
        pressure_lmsb != 0xFF) {
        P2->OUT = BIT4;
    }

    P2->OUT |= BIT4;

    return 0;
}
