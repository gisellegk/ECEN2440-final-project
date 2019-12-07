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

#define p_Pa_calib_0 45000.0
#define p_Pa_calib_1 80000.0
#define p_Pa_calib_2 105000.0
#define LUT_lower 3.5 * (1U<<20)
#define LUT_upper 11.5 * (1U<<20)
#define quadr_factor (1 / 16777216.0)
#define offst_factor 2048.0

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

    P9->DIR |= BIT1;

    P9->DIR &= ~BIT2;
    P9->REN |= BIT2;
    P9->OUT &= ~BIT2;

    config_i2c();
    // Configure UART
    config_teensy_uart(9600);
    init_teensy_vars();
    // Enable UART
    enable_teensy_uart(); // also enables interrupts
    while(teensy_ready == 0){}

    P9->OUT |= BIT1; // turn LED on once teensy is ready

    while((P9->IN & BIT2) == BIT2){} // Wait until the tag is pulled and the jumper wire is pulled out

    uint8_t id[3] = {0, 0, 0};
    request_id(id);
    uint8_t check_id = write_part_number(id[0], id[1], id[2]);
    for(delay_ctr = 0; delay_ctr < (100000); delay_ctr++); // wait a bit.
    uint8_t cn[12];
    get_calibration(cn, ICP10111);
    int jk;
    uint8_t check_cn = 2;
    for (jk = 0; jk < 4; jk++) {
        check_cn = write_calibration(jk, cn[0 + (3 * jk)], cn[1 + (3 * jk)], cn[2 + (3 * jk)]);
        for(delay_ctr = 0; delay_ctr < (100000); delay_ctr++); // wait a bit.
    }
    // write 4 calibration #'s

    uint8_t pressure[9];

    int16_t cn_decoded_0 = (cn[0] << 8) | (cn[1] >> 8);

    int16_t cn_decoded_1 = ((cn[3] << 8) | (cn[4]) >> 8);

    int16_t cn_decoded_2 = ((cn[6] << 8) | (cn[7]) >> 8);

    int16_t cn_decoded_3 = (cn[9] << 8) | (cn[10] >> 8);

    int16_t cn_decoded[4] = {cn_decoded_0, cn_decoded_1, cn_decoded_2, cn_decoded_3};

    while(1){
        request_pressure_measurement(pressure);
        //TODO: fix this so it's the whole 9 bytes
        uint8_t check_data = write_data(pressure[0], pressure[1], pressure[2], pressure[3], pressure[4], pressure[5], pressure[6], pressure[7], pressure[8]);

        for(delay_ctr = 0; delay_ctr < (100000); delay_ctr++); // wait a bit.

        // do math
        // write_altitude.
    }

    return 0;
}
