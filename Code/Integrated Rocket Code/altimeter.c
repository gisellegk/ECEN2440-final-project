/*
 * altimeter.c
 *
 *  Created on: Dec 2, 2019
 *      Author: Giselle
 */
#include "altimeter.h"

void request_id(uint8_t *id){
    measurement_sequence(ICP10111, WRITE_HEADER, ID_MSB, ID_LSB);

    read_probing(ICP10111, READ_HEADER);

    uint8_t i;
    for(i = 0; i < 3; i++){
        id[i] = read_data(ICP10111); // msb, lsb, crc.
    }
    send_stop();

}

void request_pressure_measurement(uint8_t *pressure){
    measurement_sequence(ICP10111, WRITE_HEADER, PRESSURE_MEASUREMENT_MSB, PRESSURE_MEASUREMENT_LSB);

    read_probing(ICP10111, READ_HEADER);

    int i = 0;

    for(i = 0; i < 9; i++) {
        pressure[i] = read_data(ICP10111);
    }

    send_stop();
}

void request_full_measurement(uint8_t *data){
    measurement_sequence(ICP10111, WRITE_HEADER, PRESSURE_MEASUREMENT_MSB, PRESSURE_MEASUREMENT_LSB);

    read_probing(ICP10111, READ_HEADER);

    int i = 0;

    for(i = 0; i < 9; i++) {
        data[i] = read_data(ICP10111);
    }

    send_stop();
}

void get_calibration(uint8_t cn[], uint8_t address) {
    set_as_transmitter();
    set_i2c_address(address);
    set_i2c_byte_counter(4);
    send_start();

    EUSCI_B0->TXBUF = OTP_SET_UP_1;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0->TXBUF = OTP_SET_UP_2;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0->TXBUF = OTP_SET_UP_3;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0->TXBUF = OTP_SET_UP_4;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0->TXBUF = OTP_SET_UP_5;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    send_start();

    EUSCI_B0->TXBUF = OTP_READ_MSB;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    EUSCI_B0->TXBUF = OTP_READ_LSB;
    while(!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));

    read_probing(address, 0);

    int i;
    for (i = 0; i < 4; i++) {
        int cn_msb = read_data(address);
        int cn_lsb = read_data(address);
        int cn_crc = read_data(address);

        cn[0 + (3 * i)] = cn_msb;
        cn[1 + (3 * i)] = cn_lsb;
        cn[2 + (3 * i)] = cn_crc;
    }

    send_stop();
}

