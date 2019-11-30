#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_rtc.h"
#include "ADC_Driver.h"
#include "MyTimer.h"

void configureADC(ADC_TypeDef * ADCx, TIM_TypeDef * Timer);
void startADC(void);
int getX(void);
int getY(void);
int getBatteryLevel(void);

int * getXref(void);
int * getYRef(void);
#endif
