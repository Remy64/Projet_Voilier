#include "Ecoute.h"

//Constantes à vérifier
const double ANGLE_MAX = 180;
const double ANGLE_MIN = 0;
const double TH_MAX = 0.002;
const double TH_MIN = 0.001;

PWM_TypeDef pwm_ecoute;
void conf_pwm_ecoute(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_8,LL_GPIO_OUTPUT_PUSHPULL); // ATTENTION
	TIM1->CCER |= TIM_CCER_CC1E;
	TIM1->BDTR |= TIM_BDTR_MOE;
	pwm_ecoute=init_PWM(TIM1,50,1);
}
void set_angle_ecoute(double theta){
	double period = TH_MIN + (theta/(ANGLE_MAX-ANGLE_MIN))*(TH_MAX-TH_MIN); //On ramène l'intervalle angulaire sur l'intervalle temporel.
	set_PWM_TH(&pwm_ecoute,period);
}
