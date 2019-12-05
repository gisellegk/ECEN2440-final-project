


#include "msp.h"
#include "gpio.h"


void config_gpio(void) {
P2 -> DIR |= BIT6;
P2 -> OUT |= BIT6;
}
void toggle_gpio(void) {
    P2->DIR ^= BIT6;
}
