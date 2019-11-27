/*
 * uart.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Giselle
 */

#include "msp.h"
#include "uart.h"

#define fBRCLK 12000000 // Hz - input clock freq.

//char []

void init_buffer(){
    buffer_size = 0;
    int i;
    for(i = 0;  i < BUFFER_MAX; i++){
        buffer[i] = 0;
    }
}

void config_uart(uint16_t baud){
    //set p1.2 and p1.3 to UART mode
    // This is the primary function of these ports, so we want to write 01 in SEL1 and SEL0
    P1SEL0 |= BIT2 | BIT3; // writes 1 to bits 2 and 3
    P1SEL1 &= ~(BIT2 | BIT3); // writes 0 to bits 2 and 3

    // set UCSWRST
    disable_uart();

    // initialize all eUSCI_A registers
    //// select SMCLK = 12MHz for this project
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

    //// BRDIV value (78) http://processors.wiki.ti.com/index.php/USCI_UART_Baud_Rate_Gen_Mode_Selection
    //// 24.3.10 Setting a Baud Rate in slau356i
    float N = fBRCLK / baud;
    EUSCI_A0->BRW = (uint16_t)(N/16);
    //// UCxBRF = 2
    EUSCI_A0->MCTLW |= (uint16_t)(((N/16) - (float)((uint16_t)(N/16)) )*16)  << EUSCI_A_MCTLW_BRF_OFS; //0b10 << EUSCI_A_MCTWL_BRF_OFS ;
    //// UCxBRS = 0
    ////Check out table 24-4 on page 915 of slau356i if you're not using 115200 or 9600
    if (baud == 115200) EUSCI_A0->MCTLW |= (0x11 << EUSCI_A_MCTLW_BRS_OFS);
    else EUSCI_A0->MCTLW &= ~(EUSCI_A_MCTLW_BRS_MASK << EUSCI_A_MCTLW_BRS_OFS); // defaults to 9600 setting.

    //// oversampling
    EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16; // enable oversampling


    //// No parity (disabled)
    EUSCI_A0->CTLW0 &= ~(1 << EUSCI_A_CTLW0_PEN_OFS);
    //// LSB first
    EUSCI_A0->CTLW0 &= ~(1 << EUSCI_A_CTLW0_MSB_OFS);
    //// one stop bit
    EUSCI_A0->CTLW0 &= ~(1 << EUSCI_A_CTLW0_SPB_OFS);
    //// uart mode
    EUSCI_A0->CTLW0 &= ~(1 << EUSCI_A_CTLW0_SYNC_OFS); // async mode
    EUSCI_A0->CTLW0 &= ~(0b11 << EUSCI_A_CTLW0_MODE_OFS); // UART mode, no auto baud rate



}

void enable_uart(){
    // clear UCSWRST
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
    enable_interrupts();
    EUSCI_A0->IFG |= (BIT1); // set TX flag?
}

void disable_uart(){
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;
    //this also will reset UCTXIE and UCRXIE - manually enable interrupts after use.
}

void enable_interrupts(){
    EUSCI_A0->IFG &= ~(BIT1 | BIT0); // reset TX and RX interrupt flags
    // enable interrupts with UCRXIE or UCTXIE
    EUSCI_A0->IE |= (BIT0); //just RX.
    NVIC_EnableIRQ(EUSCIA0_IRQn); //Enables global interrupts
    __NVIC_SetPriority(EUSCIA0_IRQn, 2); //Sets the priority of interrupt 8 to 2

}

int write_uart(uint8_t byte){
    if((buffer_size) != BUFFER_MAX){ // if not full
        buffer[buffer_size] = byte;
        buffer_size++; // increment size.
        EUSCI_A0->IE |= EUSCI_A_IE_TXIE;
        //EUSCI_A0->IFG |= (BIT1); // set TX flag?
        return 1;
    }
    return 0;
}

void readUART(){

}


void EUSCIA0_IRQHandler(){
    if((EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)){
        if(buffer_size > 0){ // if we have more to transmit
            P2OUT ^= 0x2; // toggle led when this happens for debug
            EUSCI_A0->TXBUF = buffer[buffer_size-1]; // put next char in UCAxTXBUF
            // Manuel says that TXIFG is reset when you write to TXBUF, but tbh it doesn't happen???
            buffer_size--;
        } else {
            EUSCI_A0->IE &=~EUSCI_A_IE_TXIE;
        }

    }
    if(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG){
        P2OUT ^= 0x1; // toggle led when this happens.
        // set when character is received and loaded into UCAxRXBUF
        // Read character out of buffer
        uint8_t data = EUSCI_A0->RXBUF;
        // echo to tx
        //EUSCI_A0->TXBUF = data;
        // automatically reset when UCAxRXBUF is read
    }

}
