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

    for(i = 0; i < 6; i++) {
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

