#include "Accel.h"

//Observed interval for acceleration values is 1730-2270
//So 1730 = 0 and 2270 = g
int range = 540;
double get_accel_x(void){
	return (getX() - 1730.0) * (9.806/range);
}

double get_accel_y(void){
	return (getY() - 1730.0) * (9.806/range);
}
