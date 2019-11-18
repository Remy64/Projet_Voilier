#ifndef RX_RCV_H
#define RX_RCV_H
#include "stm32f1xx_ll_gpio.h"
#include "PWM_IN_Driver.h"

void conf_pwm_in_rx_rcv(void);
double get_pwm_in_ratio(void);
char get_orientation(void);
int get_pwm_in_duty(void);
int get_pwm_in_period(void);
#endif
