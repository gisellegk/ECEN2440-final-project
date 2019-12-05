#ifndef PWM_H_
#define PWM_H_
/*   DEFINES  */
#define SYSTEM_CLOCK        3000000  // [Hz] system_msp432p401r.c
#define PWM_FREQUENCY       100000   // [Hz] PWM frequency desired
#define CALC_PERIOD      (SYSTEM_CLOCK / PWM_FREQUENCY) //calc # of ticks in period


void config_pwm_timer(void);

void start_pwm(uint8_t duty_cycle);

void stop_pwm(void);

void config_pwm_gpio(void);

#endif /* PWM_H_ */
