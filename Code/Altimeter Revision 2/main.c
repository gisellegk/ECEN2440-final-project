#include "msp.h"
#include "I2C.h"
#include <stdint.h>
#include <stdio.h>

#define ICP10111 0x63
#define WRITE_HEADER 0xC6
#define PRESSURE_MEASUREMENT_MSB 0x48
#define PRESSURE_MEASUREMENT_LSB 0xA3
#define READ_HEADER 0xC7
#define ID_MSB 0xEF
#define ID_LSB 0xC8

int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    config_i2c();

    measurement_sequence(ICP10111, WRITE_HEADER, ID_MSB, ID_LSB);

    read_probing(ICP10111, READ_HEADER);

    uint8_t i = 0;
    for (i; i < 2; i++) {
        uint8_t id = read_data(ICP10111);
    }

    send_stop();

    measurement_sequence(ICP10111, WRITE_HEADER, PRESSURE_MEASUREMENT_MSB, PRESSURE_MEASUREMENT_LSB);

    read_probing(ICP10111, READ_HEADER);

    uint8_t pressure [6];

    i = 0;

    for(i = 0; i < 6; i++) {
        pressure[i] = read_data(ICP10111);
    }

    send_stop();

    return 0;
}
