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

PWM_TypeDef init_PWM(TIM_TypeDef * timer,int freq,int ch);//Initialize a PWM assuming proper GPIOs ports are active and configured
void set_PWM_COMPARE(PWM_TypeDef * pwm,int compare);//Set PWM CMPR field
void set_PWM_TH(PWM_TypeDef * pwm,double th);//Set PWM shift temporal high state period
void set_PWM_RATIO(PWM_TypeDef * pwm,double ratio);//Set PWM highstate period to fit the ratio = highstate period/global period
double get_PWM_Period(PWM_TypeDef * pwm);

#endif
