#include "RX_Rcv.h"
PWM_IN_TypeDef pwm_rx_rcv;
void conf_pwm_in_rx_rcv(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	LL_GPIO_SetPinMode(GPIOB,LL_GPIO_PIN_6,LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(GPIOB,LL_GPIO_PIN_7,LL_GPIO_MODE_INPUT);
	pwm_rx_rcv=conf_pwm_in(TIM4);
	
}
double get_pwm_in_ratio(void){
	return get_duty_cycle(&pwm_rx_rcv) / get_period(&pwm_rx_rcv);//Assuming duty_cycle is expressed in time unit and not already in %
};
char get_orientation(void){
	return 0;//TODO
}
int get_pwm_in_duty(void){
	return get_duty_cycle(&pwm_rx_rcv);
}
int get_pwm_in_period(void){
	return get_period(&pwm_rx_rcv);
}
