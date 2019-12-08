#ifndef PWM_IN_DRIVER
#define PWM_IN_DRIVER
#include "MyTimer.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_bus.h"

/*
PWM_IN caracteritics of the telecommand
054D period

00BF duty max
0090 duty middle
0071 duty min
	*/
typedef struct {
	TIM_TypeDef * timer;
}PWM_IN_TypeDef;

PWM_IN_TypeDef conf_pwm_in(TIM_TypeDef * timer);
int get_duty_cycle(PWM_IN_TypeDef * pwm);//Expressed in time unit, not %
int get_period(PWM_IN_TypeDef * pwm);//PWM global period

#endif
