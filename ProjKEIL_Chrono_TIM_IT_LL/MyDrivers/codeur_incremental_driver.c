#include "codeur_incremental_driver.h"
#include "stm32f1xx_ll_bus.h"

void configure_codeur(void) { 
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	LL_TIM_SetEncoderMode(TIM3, LL_TIM_ENCODERMODE_X4_TI12) ;
	LL_TIM_IC_Config(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING | LL_TIM_ACTIVEINPUT_DIRECTTI );
	LL_TIM_IC_Config(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING | LL_TIM_ACTIVEINPUT_DIRECTTI );
	LL_TIM_EnableCounter(TIM3);
	
}