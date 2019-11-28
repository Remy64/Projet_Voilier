#include "Plate.h"
const double GLOBAL_VOLTAGE =12.0;
PWM_TypeDef pwm_plate;
PWM_TypeDef pwm_orientation;
void conf_pwm_plate(void){//Timer 2;Port A1;Channel 2;50Hz
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_1,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_1,LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_2,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_2,LL_GPIO_OUTPUT_PUSHPULL);
	pwm_plate=init_PWM(TIM2,50,2);
	pwm_orientation = init_PWM(TIM2,50,3);
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->CCER |= TIM_CCER_CC3E;
	TIM2->BDTR |= TIM_BDTR_MOE;
	
}
void set_servo_mean_voltage(double mean_voltage){
	set_PWM_RATIO(&pwm_plate,mean_voltage/GLOBAL_VOLTAGE);
}

//range 5V-10V
double find_voltage_from_ratio (double ratio){
	return 5.0+(5.0*ratio);
}


void set_orientation(char orientation){
	if(orientation){
		set_PWM_RATIO(&pwm_orientation,1);
	}
	else{
		set_PWM_RATIO(&pwm_orientation,0);
	}
}
void turn(char orientation,double ratio){
		set_orientation(orientation);
		set_servo_mean_voltage(find_voltage_from_ratio(ratio));
}
void forward(void){
	set_servo_mean_voltage(0.0);
}
