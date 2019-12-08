#include "Battery.h"
double BATTERY_LVL(void){
	return (100.0*getBatteryLevel())/4095;//Observed min-ax values of battery are 0-4095
}
