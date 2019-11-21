#include "PWM_IN_Driver.h"
#include "stm32f1xx_ll_bus.h"
PWM_IN_TypeDef conf_pwm_in(TIM_TypeDef * timer){
	PWM_IN_TypeDef pwm;
	pwm.timer = timer;
	if (timer==TIM1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	else if (timer==TIM2) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	else if (timer==TIM3) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	else  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	//CC1S bits to _1
	timer -> CCMR1 |=TIM_CCMR1_CC1S_0;
	timer -> CCMR1 &=~TIM_CCMR1_CC1S_1;
	
	timer -> CCER &=~TIM_CCER_CC1P;
	
	//CC2S bits to 10
	timer -> CCMR1 |= TIM_CCMR1_CC2S_1;
 	timer -> CCMR1 &=~TIM_CCMR1_CC2S_0;
	
	timer -> CCER |=TIM_CCER_CC2P;
	
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
	
	timer -> DIER |= LL_TIM_DIER_CC1IE;
	timer -> DIER |= LL_TIM_DIER_CC2IE;
	LL_TIM_SetPrescaler(timer,719);
	LL_TIM_EnableIT_UPDATE(timer);
	LL_TIM_EnableCounter(timer);
	return pwm;
}
int get_period(PWM_IN_TypeDef * pwm){
	return pwm ->timer ->CCR1; //WARNING, CONVERSION ? Absolute unit ? Relative to SystemClock ?
}

int get_duty_cycle(PWM_IN_TypeDef * pwm){
	return pwm -> timer -> CCR2; //WARNING, CONVERSION? Duty cycle expressed in % or in time unit?
}
