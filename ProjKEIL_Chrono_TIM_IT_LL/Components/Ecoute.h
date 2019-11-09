
#ifndef ECOUTE_H
#define ECOUTE_H
#include "PWM_Driver.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
void conf_pwm_ecoute(void);
void set_angle_ecoute(double theta);
#endif

