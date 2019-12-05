#include "msp.h"
#include "I2C.h"
#include "gpio.h"

#define DRV2605L       0x5A

#define STATUS         0x00
#define MODE           0x01
#define GO             0x0C
#define CONTROL3       0x1D

#define MODE_PWM       0x03
#define MODE_STANDBY     (1 << 6)
#define GO_GO          0x01
#define LIBRARY        0x03
#define LRA            0x06
#define PWM            0x00

void config_drv2605L(void){
    config_gpio();
    toggle_gpio();

    int i;
    for(i = 0; i < 100000; i++);
    write_register(DRV2605L, MODE, MODE_STANDBY);
    //come out of standby mode
    uint8_t mode_reg = read_register(DRV2605L,MODE);
    write_register(DRV2605L,MODE,MODE_PWM);
    write_register(DRV2605L,CONTROL3,PWM);
    write_register(DRV2605L,LIBRARY, LRA);
    //set MODE reg. to 3
    //set CONTROL3 to PWM
    //select LRA library
    mode_reg = read_register(DRV2605L,MODE);
    mode_reg = read_register(DRV2605L,MODE);
    if(mode_reg != (0x03)) {
        P1 ->DIR |= BIT0;
        P1-> OUT |= BIT0;
    }
    uint16_t control_three_reg = read_register(DRV2605L, CONTROL3);
    if(control_three_reg != 0x00){
        P1 ->DIR |= BIT0;
        P1-> OUT |= BIT0;
    }
    }

