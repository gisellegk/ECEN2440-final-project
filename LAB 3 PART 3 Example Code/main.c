#include "msp.h"
#include "drv2605l.h"
#include "pwm.h"
#include "I2C.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	 //int * toggle_routine = &toggle_pwm_gpio;
	config_i2c();

    config_pwm_timer();

    config_pwm_gpio();

    config_drv2605L();
    config_gpio();

    //toggle_gpio();
while(1){
int i;
for(i = 0; i < 10000000; i++){
        start_pwm(90);
}
    for(i = 0; i < 10000000; i++){
        stop_pwm();
    }
}

}


 //   uint8_t i;
 //   for (i = 0; i < 50000; i++) {
 //       P2 -> OUT |= TIMER_A0->CCTL[2];
 //   }



