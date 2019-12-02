#include "msp.h"
#include "I2C.h"
#include <stdint.h>
#include <stdio.h>
#include "altimeter.h"

/**
 * main.c
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    config_i2c();

    uint8_t id = request_id();

    uint8_t pressure[6];

    request_pressure_measurement(pressure);

    while(1){
    }

    return 0;
}
