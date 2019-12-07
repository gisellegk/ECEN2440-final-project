/*
 * uart.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Giselle
 */

#include "msp.h"
#include "teensy_uart.h"

#define fBRCLK 12000000 // Hz - input clock freq.

#define DEBUG
//char []

void init_teensy_vars(){
    teensy_uart_state = TEENSY_LOG_LENGTH;
    teensy_ready = 0;
    teensy_buffer_size = 0;
    int i; int j;
    for(i = 0;  i < TEENSY_BUFFER_MAX; i++){
        for(j = 0; j < TEENSY_LOG_LENGTH; j++){
            teensy_buffer[i][j] = 0;
        }
    }
}

void config_teensy_uart(uint16_t baud){
    // P9.6 as RX and P9.7 as TX forUART mode
    // per Table 6.65 pg 143 of datasheet: P9SEL1.x = 0 P9SEL0.x = 1
    P9SEL0 |= BIT6 | BIT7; // writes 1 to bits 6 and 7
    P9SEL1 &= ~(BIT6 | BIT7); // writes 0 to bits 6 and 7

    // set UCSWRST
    disable_teensy_uart();

    // initialize all eUSCI_A registers
    //// select SMCLK = 12MHz for this project
    EUSCI_A3->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

    //// BRDIV value (78) http://processors.wiki.ti.com/index.php/USCI_UART_Baud_Rate_Gen_Mode_Selection
    //// 24.3.10 Setting a Baud Rate in slau356i
    float N = fBRCLK / baud;
    EUSCI_A3->BRW = (uint16_t)(N/16);
    //// UCxBRF = 2
    EUSCI_A3->MCTLW |= (uint16_t)(((N/16) - (float)((uint16_t)(N/16)) )*16)  << EUSCI_A_MCTLW_BRF_OFS; //0b10 << EUSCI_A_MCTWL_BRF_OFS ;
    //// UCxBRS = 0
    ////Check out table 24-4 on page 915 of slau356i if you're not using 115200 or 9600
    if (baud == 115200) EUSCI_A3->MCTLW |= (0x11 << EUSCI_A_MCTLW_BRS_OFS);
    else EUSCI_A3->MCTLW &= ~(EUSCI_A_MCTLW_BRS_MASK << EUSCI_A_MCTLW_BRS_OFS); // defaults to 9600 setting.

    //// oversampling
    EUSCI_A3->MCTLW |= EUSCI_A_MCTLW_OS16; // enable oversampling


    //// No parity (disabled)
    EUSCI_A3->CTLW0 &= ~(1 << EUSCI_A_CTLW0_PEN_OFS);
    //// LSB first
    EUSCI_A3->CTLW0 &= ~(1 << EUSCI_A_CTLW0_MSB_OFS);
    //// one stop bit
    EUSCI_A3->CTLW0 &= ~(1 << EUSCI_A_CTLW0_SPB_OFS);
    //// uart mode
    EUSCI_A3->CTLW0 &= ~(1 << EUSCI_A_CTLW0_SYNC_OFS); // async mode
    EUSCI_A3->CTLW0 &= ~(0b11 << EUSCI_A_CTLW0_MODE_OFS); // UART mode, no auto baud rate



}

void enable_teensy_uart(){
    // clear UCSWRST
    EUSCI_A3->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
    enable_teensy_interrupts();
    EUSCI_A3->IFG |= (BIT1); // set TX flag?
}

void disable_teensy_uart(){
    EUSCI_A3->CTLW0 |= EUSCI_A_CTLW0_SWRST;
    //this also will reset UCTXIE and UCRXIE - manually enable interrupts after use.
}

void enable_teensy_interrupts(){
    EUSCI_A3->IFG &= ~(BIT1 | BIT0); // reset TX and RX interrupt flags
    // enable interrupts with UCRXIE or UCTXIE
    EUSCI_A3->IE |= (BIT0); //just RX.
    NVIC_EnableIRQ(EUSCIA3_IRQn); //Enables global interrupts
    __NVIC_SetPriority(EUSCIA3_IRQn, 2); //Sets the priority of interrupt to 2

}


int write_altitude(uint8_t byte0, uint8_t byte1, uint8_t byte_2){
    // log processed data altitude - after math.
    return 0;
}

int write_data(uint8_t alt0, uint8_t alt1, uint8_t crc_alt0, uint8_t alt2, uint8_t alt3, uint8_t crc_alt1, uint8_t temp0, uint8_t temp1, uint8_t crc_temp){
    if((teensy_buffer_size) < TEENSY_BUFFER_MAX){ // if not full
        teensy_buffer[teensy_buffer_size][0] = alt0;
        teensy_buffer[teensy_buffer_size][1] = alt1;
        teensy_buffer[teensy_buffer_size][2] = crc_alt0;
        teensy_buffer[teensy_buffer_size][3] = alt2;
        teensy_buffer[teensy_buffer_size][4] = alt3;
        teensy_buffer[teensy_buffer_size][5] = crc_alt1;
        teensy_buffer[teensy_buffer_size][6] = temp0;
        teensy_buffer[teensy_buffer_size][7] = temp1;
        teensy_buffer[teensy_buffer_size][8] = crc_temp;
        teensy_buffer_size++; // increment size.
        EUSCI_A3->IE |= EUSCI_A_IE_TXIE;
        //EUSCI_A3->IFG |= (BIT1); // set TX flag?
        return 1;
    }
    return 0;
}

int write_part_number(uint8_t byte0, uint8_t byte1, uint8_t crc){
    if((teensy_buffer_size) < TEENSY_BUFFER_MAX){ // if not full
            teensy_buffer[teensy_buffer_size][0] = 'p'; // PART NUMBER
            teensy_buffer[teensy_buffer_size][1] = 'n';
            teensy_buffer[teensy_buffer_size][2] = 0;
            teensy_buffer[teensy_buffer_size][3] = 0;
            teensy_buffer[teensy_buffer_size][4] = 0;
            teensy_buffer[teensy_buffer_size][5] = 0;
            teensy_buffer[teensy_buffer_size][6] = byte0;
            teensy_buffer[teensy_buffer_size][7] = byte1;
            teensy_buffer[teensy_buffer_size][8] = crc;
            teensy_buffer_size++; // increment size.
            EUSCI_A3->IE |= EUSCI_A_IE_TXIE;
            //EUSCI_A3->IFG |= (BIT1); // set TX flag?
            return 1;
        }
        return 0;
}

int write_calibration(uint8_t id, uint8_t byte0, uint8_t byte1, uint8_t crc){
    if((teensy_buffer_size) < TEENSY_BUFFER_MAX){ // if not full
                teensy_buffer[teensy_buffer_size][0] = 'c'; // CALIBRATION NUMBER
                teensy_buffer[teensy_buffer_size][1] = 'n';
                teensy_buffer[teensy_buffer_size][2] = id; // idk what they are but this tells us which is which
                teensy_buffer[teensy_buffer_size][3] = 0;
                teensy_buffer[teensy_buffer_size][4] = 0;
                teensy_buffer[teensy_buffer_size][5] = 0;
                teensy_buffer[teensy_buffer_size][6] = byte0;
                teensy_buffer[teensy_buffer_size][7] = byte1;
                teensy_buffer[teensy_buffer_size][8] = crc;
                teensy_buffer_size++; // increment size.
                EUSCI_A3->IE |= EUSCI_A_IE_TXIE;
                //EUSCI_A3->IFG |= (BIT1); // set TX flag?
                return 1;
            }
            return 0;
}

void EUSCIA3_IRQHandler(){

    if((EUSCI_A3->IFG & EUSCI_A_IFG_TXIFG)){
        if(teensy_buffer_size > 0){ // if we have more to transmit
            #ifdef DEBUG
            P2OUT ^= 0x2; // toggle GREEN led when this happens for debug
            #endif

            P9->OUT ^= BIT1;
            teensy_uart_state = (teensy_uart_state+1) % (TEENSY_LOG_LENGTH+1);
            if(teensy_uart_state != TEENSY_LOG_LENGTH){
                uint8_t nextChar = teensy_buffer[teensy_buffer_size-1][teensy_uart_state]; // put next char in UCAxTXBUF
                EUSCI_A3->TXBUF = nextChar;
            } else {
                // Manuel says that TXIFG is reset when you write to TXBUF
                teensy_buffer_size--;
            }
        } else {
            EUSCI_A3->IE &=~EUSCI_A_IE_TXIE;
        }

    }
    if(EUSCI_A3->IFG & EUSCI_A_IFG_RXIFG){
        #ifdef DEBUG
        P2OUT ^= 0b1; // toggle RED led when this happens.
        #endif
        // set when character is received and loaded into UCAxRXBUF
        // Read character out of buffer
        uint8_t data = EUSCI_A3->RXBUF;
        if(data == 'r' && !teensy_ready){
            #ifdef DEBUG
            P2OUT ^= 0b100; // toggle BLUE led when this happens.
            #endif
            teensy_ready = 1;

            // send back 'a' for acknowledge
            EUSCI_A3->TXBUF = 'a';
        }
        if(teensy_ready == 1){
            P2OUT &= ~0b101; // turn off red and blue.
        }
        // echo to tx
        //EUSCI_A3->TXBUF = data;
        // automatically reset when UCAxRXBUF is read
    }

}
