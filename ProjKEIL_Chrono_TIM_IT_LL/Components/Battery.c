#include "Battery.h"
double BATTERY_LVL(void){
	return (100.0*getBatteryLevel())/4095;
}
