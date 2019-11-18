/*
 * uart.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Giselle
 */

#include "msp.h"
#include "uart.h"

#define fBRCLK 12000000 // Hz - input clock freq.

char []

void config_uart(uint8_t baud){
    // set UCSWRST
    disable_uart();

    // initialize all eUSCI_A registers
    //// select SMCLK = 12MHz for this project
    //UCA0CTLW0 |= 0b11 << UCSSEL_OFS; // apparently setting it to either 10b or 11b = SMCLK ?????
    EUSCI_A0->CTLW0 |= 0x11 << EUSCI_A_CTLW0_SSEL_OFS;

    //// BRDIV value (78) http://processors.wiki.ti.com/index.php/USCI_UART_Baud_Rate_Gen_Mode_Selection
    //UCA0BRW = fBRCLK / baud;
    EUSCI_A0->BRW = fBRCLK / baud;
    //// UCxBRF = 2
    UCA0MCTLW |= 0b10 << UCBRF_OFS;
    UCA0MCTLW &= ~(1 << UCBRF_OFS);
    //// UCxBRS = 0
    UCA0MCTLW &= ~1 << UCBRS_OFS;
    //// oversampling
    UCA0MCTLW |= 1; // bit 1 set = oversampling enabled

    //// No parity
    UCA0CTLW0 &= ~(1 << UCPEN_OFS);
    //// LSB first
    UCA0CTLW0 &= ~(1 << UCPAR_OFS);
    //// one stop bit
    UCA0CTLW0 &= ~(1 << UCSPB_OFS);

    //// uart mode
    UCA0CTLW0 & = ~(1 << UCSYNC_OFS); // async mode
    UCA0CTLW0 &= ~(0b11 << UCMODE_OFS); // UART mode, no auto baud rate

}

void enable_uart(){
    // clear UCSWRST
    UCA0CTLW0 &= ~1;
}

void disable_uart(){
    UCA0CTLW0 |= 1;
    //this also will reset UCTXIE and UCRXIE - manually enable interrupts after use.
}

void enable_interrupts(){
    // enable interrupts (optional) with UCRXIE or UCTXIE
    UCA0IE |= 0b11; // enable both TXIE and RXIE
    NVIC_EnableIRQ(EUSCIA0_IRQn); //Enables global interrupts
    __NVIC_SetPriority(EUSCIA0_IRQn, 2); //Sets the priority of interrupt 8 to 2

}

void writeUART(){

}

void readUART(){

}


void EUSCIA0_IRQHandler(){
    if(UCTXIFG){
        // if we have more to transmit
        // put next char in UCAxTXBUF
        // this is automatically reset once it's written
    }
    if(UCRXIFG){
        // set when character is received and loaded into UCAxRXBUF
        // Read character out of buffer
        // automatically reset when UCAxRXBUF is read
    }

}
