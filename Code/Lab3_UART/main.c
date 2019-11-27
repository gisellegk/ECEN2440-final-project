#include "msp.h"
#include "teensy_uart.h"
#include <stdlib.h>

/**
 * main.c
 */


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	//RGB LEDs for debug
	P2DIR |= 0x7;     // Set as output
	P2OUT &= ~0x7;     // Set to 0state
	int i; int delay_ctr;
    init_teensy_vars();


	// set DCO to 12 MHz
    // in register CSCTL0:
    // DCORSEL - resistor select(?) write 011b nominal freq = 12MH
	 CS->KEY  = 0x695A; //unlock clock
	 CS->CTL0|= CS_CTL0_DCORSEL_3;
	 CS->KEY  = 0; //lock clock
	// Configure UART
    config_teensy_uart(9600);
	// Enable UART
    enable_teensy_uart(); // also enables interrupts
    uint8_t test_data[10][3] = {{0, 11, 22},
                                {1, 22, 33},
                                {2, 33, 44},
                                {3, 44, 55},
                                {4, 55, 66},
                                {5, 66, 77},
                                {6, 77, 88},
                                {7, 88, 99},
                                {8, 99, 00},
                                {9, 00, 11}};
    while(teensy_ready == 0){}
    for(i = 0; i < 10; i = (i+1)%10){
        write_altitude(test_data[i][0], test_data[i][1], test_data[i][2]);
        for(delay_ctr = 0; delay_ctr < (100000); delay_ctr++); // wait a bit.
    }

}
