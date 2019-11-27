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
	int i;
    init_teensy_buffer();


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

    while(1){
        write_teensy('a' + (uint8_t)rand()%26);  // add random number to next index of list.
        for(i = 0; i < (100000); i++); // wait a bit.

    }
}
