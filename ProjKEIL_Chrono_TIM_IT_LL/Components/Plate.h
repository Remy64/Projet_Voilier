#ifndef PLATE_H
#define PLATE_H
#include "PWM_Driver.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
void conf_pwm_plate(void);//Timer 2;Port A1;Channel 2;50Hz
void set_servo_mean_voltage(double mean_voltage);//Set the PWM high period to generate a mean signal of [mean_voltage]V
void set_orientation(char orientation);
void turn(char orientation,double voltage);
void forward(void);
#endif
