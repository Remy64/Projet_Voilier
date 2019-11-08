#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H
#include "stm32f103xb.h" 
#include "MyTimer.h"
#include "stm32f1xx_ll_tim.h"



typedef struct {
	TIM_TypeDef * timer;
	int freq;
	int compare;
	int ch;
}PWM_TypeDef;

PWM_TypeDef init_PWM(TIM_TypeDef * timer,int freq,int ch);
void set_PWM_COMPARE(PWM_TypeDef * pwm,int compare);


#endif
