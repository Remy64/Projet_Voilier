
#ifndef ECOUTE_H
#define ECOUTE_H
#include "PWM_Driver.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
void conf_pwm_ecoute(void);//Initializes the proper GPIO ports and timers and configure an output PWM to control the servomotor
void set_angle_ecoute(double theta);// 0 <= Theta <= 180
#endif

