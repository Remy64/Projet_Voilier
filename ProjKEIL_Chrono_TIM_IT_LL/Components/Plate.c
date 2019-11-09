#include "Plate.h"
const double GLOBAL_VOLTAGE =12.0;
PWM_TypeDef pwm_plate;
void conf_pwm_plate(void){//Timer 2;Port A1;Channel 2;50Hz
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_1,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_1,LL_GPIO_OUTPUT_PUSHPULL);
	pwm_plate=init_PWM(TIM2,50,2);
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->BDTR |= TIM_BDTR_MOE;
	
}
void set_servo_mean_voltage(double mean_voltage){
	set_PWM_RATIO(&pwm_plate,mean_voltage/GLOBAL_VOLTAGE);
}
