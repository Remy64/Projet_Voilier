#include "stm32f1xx_ll_adc.h"


void configureADC(ADC_TypeDef * ADCx) {
	LL_ADC_REG_InitTypeDef myInitStructure;
	
	myInitStructure.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	myInitStructure.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	myInitStructure.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	myInitStructure.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	myInitStructure.TriggerSource = LL_ADC_REG_TRIG_EXT_TIM1_CH1;
	
	LL_ADC_REG_Init(ADC1, &myInitStructure);
}