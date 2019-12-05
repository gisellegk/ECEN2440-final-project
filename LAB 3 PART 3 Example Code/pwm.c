


#include "msp.h"
#include "pwm.h"




void config_pwm_timer(void) {
TIMER_A0 ->CTL |=TIMER_A_CTL_CLR ;
TIMER_A0 -> CTL |=TIMER_A_CTL_SSEL__SMCLK;
TIMER_A0 -> CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7; //7
}
void start_pwm(uint8_t duty_cycle){
    uint8_t high_ticks = (duty_cycle* CALC_PERIOD) / 100;

    //TIMER_A0->CCTL |= (BIT5 | BIT6);
    TIMER_A0 ->CCR[1] = high_ticks;
    TIMER_A0->CCR[0] = CALC_PERIOD;
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;

     }
void stop_pwm(void){
TIMER_A0->CTL |=TIMER_A_CTL_MC0;
}

void config_pwm_gpio(void) {
P2 -> DIR |= BIT4;
P2 -> SEL0 |= BIT4;
P2 -> SEL1 &= ~BIT4;

}
