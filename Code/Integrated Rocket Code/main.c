#include "msp.h"
#include "I2C.h"
#include <stdint.h>
#include <stdio.h>
#include "altimeter.h"
#include "teensy_uart.h"

/**
 * main.c
 */

#define DEBUG

void config_clock(void){
    // set DCO to 12 MHz
    // in register CSCTL0:
    // DCORSEL - resistor select(?) write 011b nominal freq = 12MH
    CS->KEY  = 0x695A; //unlock clock
    CS->CTL0|= CS_CTL0_DCORSEL_3;
    CS->KEY  = 0; //lock clock
}
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    config_clock(); // set clock to 12 MHz

    #ifdef DEBUG
    //RGB LEDs for debug
    P2DIR |= 0x7;     // Set as output
    P2OUT &= ~0x7;     // Set to 0state
    #endif

    int delay_ctr;

    config_i2c();
    // Configure UART
    config_teensy_uart(9600);
    init_teensy_vars();
    // Enable UART
    enable_teensy_uart(); // also enables interrupts
    while(teensy_ready == 0){}

    uint8_t id = request_id();

    uint8_t pressure[6];



    while(1){
        request_pressure_measurement(pressure);
        write_altitude(pressure[0], pressure[1], pressure[3]);
        for(delay_ctr = 0; delay_ctr < (100000); delay_ctr++); // wait a bit.
    }

    return 0;
}
