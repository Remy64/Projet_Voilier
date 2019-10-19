#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H
#include "stm32f103xb.h" 
#include "MyTimer.h"
#include "stm32f1xx_ll_tim.h"

void init_PWM(TIM_TypeDef * timer,int freq);
void set_PWM_COMPARE(TIM_TypeDef * timer,int compare,int ch);


#endif
