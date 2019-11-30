#include "codeur_incremental_driver.h"
void configure_codeur(void) { 

	//NE PAS OUBLIER DE BRANCHER L'ALIM

	//Interruption avec l'exti

	//tim3 =29

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_6,LL_GPIO_MODE_FLOATING);

	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_7,LL_GPIO_MODE_FLOATING);

	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_5,LL_GPIO_MODE_FLOATING);

	//un tour = 720

	LL_TIM_SetAutoReload(TIM3, 720) ;

	LL_TIM_SetEncoderMode(TIM3, LL_TIM_ENCODERMODE_X2_TI1) ;

	LL_TIM_IC_Config(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING | LL_TIM_ACTIVEINPUT_DIRECTTI );

	LL_TIM_IC_Config(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING | LL_TIM_ACTIVEINPUT_DIRECTTI );

	while (!LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_5)){}

		LL_TIM_EnableCounter(TIM3);
}

int mesurer_angle(void) {
	return LL_TIM_GetCounter(TIM3)/2 ;
}
