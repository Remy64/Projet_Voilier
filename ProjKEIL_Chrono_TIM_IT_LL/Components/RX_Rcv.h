#ifndef RX_RCV_H
#define RX_RCV_H
#include "stm32f1xx_ll_gpio.h"
#include "PWM_IN_Driver.h"

void conf_pwm_in_rx_rcv(void);


int get_pwm_in_duty(void);//Returns the current duty period received from the telecommand
double get_pwm_in_ratio(void);//Returns the current pwm duty period/global period ration
int get_pwm_in_period(void);//Returns the global period of the telecommand PWM
char get_orientation(void);//TODO, currently handled in the main. Returns 0 or 1 based on the orientation of the telecommand wheel.
#endif
