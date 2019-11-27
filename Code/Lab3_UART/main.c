#include "msp.h"
#include "uart.h"

/**
 * main.c
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	//RGB LEDs for debug
	P2DIR |= 0x7;     // Set as output
	P2OUT |= 0x7;     // Set to 0state

	// set DCO to 12 MHz
    // in register CSCTL0:
    // DCORSEL - resistor select(?) write 011b nominal freq = 12MH
	 CS->KEY  = 0x695A;
	 CS->CTL0|= CS_CTL0_DCORSEL_3;
	 CS->KEY  = 0;
	// Configure UART
    config_uart(9600);
	// Enable UART
    enable_uart(); // also enables interrupts
	// enable interrupts
    //enable_interrupts();
	// what else?
    while(1){}
}
