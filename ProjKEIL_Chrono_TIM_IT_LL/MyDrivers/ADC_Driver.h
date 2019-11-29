#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
#include "stm32f1xx_ll_adc.h"

void configureADC(ADC_TypeDef * ADCx, TIM_TypeDef * Timer);
void startADC(void);
int getX(void);
int getY(void);
int getBatteryLevel(void);

#endif