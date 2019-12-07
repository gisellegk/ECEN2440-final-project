/*
 * morse.c
 *
 *  Created on: Dec 2, 2019
 *      Author: xutao
 */

#include "morse.h"
#include "msp.h"

#define UNIT_PERIOD 325000

void config_pwm_morse(void) {
    TIMER_A0 ->CTL |=TIMER_A_CTL_CLR ;
    TIMER_A0 -> CTL |=TIMER_A_CTL_SSEL__SMCLK;
    TIMER_A0 -> CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;
}

void start_pwm_morse(uint8_t on_units, uint8_t total_units) {
    uint8_t high_ticks = (on_units* UNIT_PERIOD);
    uint8_t total_ticks = total_units * UNIT_PERIOD;
    TIMER_A0 ->CCR[1] = high_ticks;
    TIMER_A0->CCR[0] = total_ticks;
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;
}

void config_gpio_morse(void) {
    P2->DIR |= BIT0;

}
