#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_tim.h"
#include "ADC_Driver.h"
#include "MyTimer.h"

static ADC_TypeDef *ADC;
static TIM_TypeDef *Tim;
int result = 0;
void startConversion(void) {
	LL_ADC_REG_StartConversionSWStart(ADC);
	while(!LL_ADC_IsActiveFlag_EOS(ADC)){}
	result = LL_ADC_REG_ReadConversionData32 (ADC);
};


int convert(int channel) {
	LL_ADC_REG_StartConversionSWStart(ADC);
	while(!LL_ADC_IsActiveFlag_EOS(ADC)){}
	return LL_ADC_REG_ReadConversionData12(ADC);
}


void configureADC(ADC_TypeDef * ADCx, TIM_TypeDef * Timer) {
	
	
	//ADC
	ADC = ADCx;
	//Timer
	Tim = Timer;
	
		//enable clock
	if(ADCx == ADC1)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	else if(ADCx == ADC2)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
		//init with structure
	LL_ADC_REG_InitTypeDef myInitStructure;
	
	myInitStructure.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	myInitStructure.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	myInitStructure.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE; //?
	myInitStructure.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE; //?
	myInitStructure.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE; //on déclenche via SW Start
	
	LL_ADC_REG_Init(ADC1, &myInitStructure);
	//TIMER
	//enable clock
	MyTimer_Conf(Timer, 999, 719);
	MyTimer_IT_Conf(Timer, startConversion, 1);
	MyTimer_IT_Enable(Timer);
	
	

	

	
	//réglage de la période d'échantillonage des deux voies utilisées
	LL_ADC_SetChannelSamplingTime(ADCx, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	LL_ADC_SetChannelSamplingTime(ADCx, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_1CYCLE_5);


}

void startADC(void) {
	MyTimer_Start(Tim);
}




