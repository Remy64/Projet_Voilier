#include "PWM_Driver.h"
const int GLOBAL_ARR = 1000;
PWM_TypeDef init_PWM(TIM_TypeDef * timer,int freq,int ch){
	PWM_TypeDef pwm;
	int arr =GLOBAL_ARR-1;
	int psc = 72000000/(GLOBAL_ARR)/freq;
	int compare = 0;
	MyTimer_Conf(timer,arr,psc); //Define PWM frequency
	switch(ch){//Set PWM mode on correct channel WARNING : LL_TIM_CHANNEL_CHx != x except for CH1
		case 1:LL_TIM_OC_SetMode(timer,LL_TIM_CHANNEL_CH1,LL_TIM_OCMODE_PWM1);break;
		case 2:LL_TIM_OC_SetMode(timer,LL_TIM_CHANNEL_CH2,LL_TIM_OCMODE_PWM1);break;
		case 3:LL_TIM_OC_SetMode(timer,LL_TIM_CHANNEL_CH3,LL_TIM_OCMODE_PWM1);break;
		default:LL_TIM_OC_SetMode(timer,LL_TIM_CHANNEL_CH4,LL_TIM_OCMODE_PWM1);break;
	}
	pwm.timer=timer;
	pwm.freq=freq;
	pwm.compare=compare;
	pwm.ch=ch;
	set_PWM_COMPARE(&pwm,compare);//Define PWM duty cycle
	LL_TIM_EnableCounter(timer);
	return pwm;
	
}

void set_PWM_COMPARE(PWM_TypeDef * pwm,int compare){//Define PWM duty cycle
		switch(pwm->ch){
			case 1:LL_TIM_OC_SetCompareCH1(pwm->timer,compare);break; //Modify CCRx register
			case 2:LL_TIM_OC_SetCompareCH2(pwm->timer,compare);break;
			case 3:LL_TIM_OC_SetCompareCH3(pwm->timer,compare);break;
			default:LL_TIM_OC_SetCompareCH4(pwm->timer,compare);break;
		}
}

void set_PWM_TH(PWM_TypeDef * pwm,double th){
	double coeff = th*pwm->freq; //TH/T = TH*F
	int compare = GLOBAL_ARR*coeff;//Ratio TH/T = ARR/CMPR
	set_PWM_COMPARE(pwm,compare);
}
void set_PWM_RATIO(PWM_TypeDef * pwm,double ratio){
	int compare = GLOBAL_ARR * ratio;//RATIO TH/T = ARR/CMPR
	set_PWM_COMPARE(pwm,compare);
}
double get_PWM_Period(PWM_TypeDef * pwm){
		return 1/pwm->freq;
}
