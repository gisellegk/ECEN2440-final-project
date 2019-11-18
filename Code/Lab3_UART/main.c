#include "msp.h"
#include 'uart.h'

/**
 * main.c
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//set p1.2 and p1.3 to UART mode
	// This is the primary function of these ports, so we want to write 01 in SEL1 and SEL0
	P1SEL0 |= 1 << 2; // writes 1 to bit 2
	P1SEL1 &= ~(1 << 2); // writes 0 to bit 2

	// set DCO to 12 MHz
    // in register CSCTL0:
    // DCORSEL - resistor select(?) write 011b nominal freq = 12MHz
    CSCTL0 |= 0b011 << CS_CTL0_DCORSEL_OFS; // set DCORSEL bits 0-1
    CSCTL0 &= ~0b100 << CS_CTL0_DCORSEL_OFS; // clear DCORSEL bit 2

	// Configure UART
    config_uart();
	// Enable UART
    enable_uart();
	// enable interrupts
    enable_interrupts();
	// what else?
}
