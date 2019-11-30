#include "Accel.h"
int range = 540;
double get_accel_x(void){
	return getX() * 1.0;
}

double get_accel_y(void){
	return (getY() - 1730.0) * (9.806/540);
}

double get_battery_level(void){
	return getBatteryLevel() * 1.0;
}
