#include "Ecoute.h"
#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_tim.h" 
#include "PWM_Driver.h"
void conf_pwm_ecoute(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_8);
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_8,LL_GPIO_OUTPUT_PUSHPULL); // ATTENTION
	TIM1->CCER |= TIM_CCER_CC1E;
	TIM1->BDTR |= TIM_BDTR_MOE;
	init_PWM(TIM1,50,1);
}
