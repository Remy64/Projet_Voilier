#ifndef PLATE_H
#define PLATE_H
#include "PWM_Driver.h"
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_gpio.h"
void conf_pwm_plate(void);//Timer 2;Port A1;Channel 2;50Hz
void set_servo_mean_voltage(double mean_voltage);//Set the PWM high period to generate a mean signal of [mean_voltage]V
void set_orientation(char orientation);//Choose a clockwise(0) or anticlockwise (1) rotation for the plate. Conserves the current power.
void turn(char orientation,double ratio);//Turn the plate clockwise/anticlockwise if orientation = 0/1. Ratio is the fraction of the plate max speed to apply.
void forward(void);//Stop the rotation of the plate
#endif
