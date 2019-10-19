#include "PWM_Driver.h"
void init_PWM(TIM_TypeDef * timer,int freq){
	int arr =999;
	int psc = 72000000/(arr+1)/freq;
	int compare = 0; //TODO to compute using freq psc and arr range 0x0000 0xFFFF
	int ch = 1; //Channel 1 by default ? 
	MyTimer_Conf(timer,arr,psc); //Define PWM frequency
	LL_TIM_OC_SetMode(timer,ch,LL_TIM_OCMODE_PWM1);//Set PWM
	set_PWM_COMPARE(timer,compare,ch);//Define PWM duty cycle
}

void set_PWM_COMPARE(TIM_TypeDef * timer,int compare,int ch){//Define PWM duty cycle
		switch(ch){
			case 1:LL_TIM_OC_SetCompareCH1(timer,compare); //Modify CCRx register
			case 2:LL_TIM_OC_SetCompareCH2(timer,compare);
			case 3:LL_TIM_OC_SetCompareCH3(timer,compare);
			default:LL_TIM_OC_SetCompareCH4(timer,compare);
	}
}
