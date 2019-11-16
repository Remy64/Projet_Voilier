#include "PWM_IN_Driver.h"

PWM_IN_TypeDef conf_pwm_in(TIM_TypeDef * timer){
	PWM_IN_TypeDef pwm;
	pwm.timer = timer;
	
	//CC1S bits to _1
	timer -> CCMR1 |=TIM_CCMR1_CC1S_0;
	timer -> CCER |= TIM_CCER_CC1P;
	
	//CC2S bits to 10
	timer -> CCMR2 |=TIM_CCMR1_CC2S_1;
 	timer -> CCMR2 &=~TIM_CCMR1_CC2S_0;
	timer -> CCER &=~TIM_CCER_CC2P;
	
	//TS bits to 101
	timer -> SMCR |= TIM_SMCR_TS_2;
	timer -> SMCR &=~TIM_SMCR_TS_1;
	timer -> SMCR |= TIM_SMCR_TS_0;
	
	//SMS bits to 100
	timer -> SMCR |= TIM_SMCR_SMS_2;
	timer -> SMCR &=~TIM_SMCR_SMS_1;
	timer -> SMCR &=~TIM_SMCR_SMS_0;
	
	//CC_E bits to 1 : enables catpure
	timer -> CCER |= TIM_CCER_CC1E;
	timer -> CCER |= TIM_CCER_CC2E;

	return pwm;
}
double get_period(PWM_IN_TypeDef * pwm){
	return pwm ->timer ->CCR1; //WARNING, CONVERSION ? Absolute unit ? Realtive to SystemClock ?
}

double get_duty_cycle(PWM_IN_TypeDef * pwm){
	return pwm -> timer -> CCR2; //WARNING, CONVERSION? Duty cycle expressed in % or in time unit?
}
