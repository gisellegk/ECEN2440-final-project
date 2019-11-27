#include "msp.h"
#include "uart.h"
#include "buffer.h"
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
    buffer_size = 0;
	int i;
	for(i = 0;	i < BUFFER_MAX; i++){
	    buffer[i] = 0;
	}


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
    while(1){
        if((buffer_size) != BUFFER_MAX){ // if not full
            buffer[buffer_size] = 'a' + (uint8_t)rand()%26; // add random number to next index of list.
            buffer_size++; // increment size.
            EUSCI_A0->IE |= EUSCI_A_IE_TXIE;
            EUSCI_A0->IFG |= (BIT1); // set TX flag?
            for(i = 0; i < 100000; i++); // wait a bit.

        }

    }
}
