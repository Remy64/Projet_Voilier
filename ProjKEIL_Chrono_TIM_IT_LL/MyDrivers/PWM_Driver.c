#include "PWM_Driver.h"
void init_PWM(TIM_TypeDef * timer,int freq){
	
	int arr =999;
	int psc = 72000000/(arr+1)/freq;
	MyTimer_Conf(timer,arr,psc);
}
