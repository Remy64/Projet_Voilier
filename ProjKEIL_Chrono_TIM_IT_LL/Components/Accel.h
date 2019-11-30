#ifndef ACCEL_H
#define ACCEL_H
#include "ADC_Driver.h"

double get_accel_x(void); //Acceleration on X axis in m.s-2
double get_accel_y(void); //Acceleration on Y axis in m.s-2
double get_battery_level(void); //Battery level in %

#endif
