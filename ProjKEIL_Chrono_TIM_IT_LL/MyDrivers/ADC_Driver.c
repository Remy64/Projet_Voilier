#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_rcc.h"
#include "ADC_Driver.h"
#include "MyTimer.h"

static ADC_TypeDef *ADC;
static TIM_TypeDef *TIM;
static int X = 0;
static int Y = 0;
static int batteryLevel = 0;
static int currentChannel = 0;

void startConversion(void) {
	LL_ADC_Enable(ADC);
	LL_ADC_Enable(ADC);
	
	if(currentChannel == 0) {
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_10);
	} else if(currentChannel == 1) {
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_11);
	} else if(currentChannel == 2) {
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_12);
	}
	
	LL_ADC_REG_StartConversionSWStart(ADC);
	while(!LL_ADC_IsActiveFlag_EOS(ADC)){}
	int result = LL_ADC_REG_ReadConversionData32(ADC);
	
	if(currentChannel == 0) {
		X = result;
	} else if(currentChannel == 1) {
		Y = result;
	} else if(currentChannel == 2) {
		batteryLevel = result;
	}
	
	currentChannel++;
	currentChannel%=3;
	
	LL_ADC_Disable(ADC);
}

int getX(void) {
	return X;
}

int getY(void){
	return Y;
}

int getBatteryLevel(void){
	return batteryLevel;
}

void configureADC(ADC_TypeDef * ADCx, TIM_TypeDef * Timer) {
	//affectation variables globales
	ADC = ADCx;
	TIM = Timer;
	
	//enable GPIO
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_2, LL_GPIO_MODE_ANALOG);
	
	//enable clock
	if(ADC == ADC1)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	else if(ADC == ADC2)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
	
	//on active l'ADC
	//LL_ADC_Enable(ADC);
	
	
	//on divise la fréquence de l'ADC par 4 pour s'assurer que la fréquence de l'ADC soit inférieure à 14 MHz
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_8);
	
	//init with structure
	LL_ADC_REG_InitTypeDef myInitStructure;
	
	myInitStructure.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	myInitStructure.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	myInitStructure.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	myInitStructure.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	myInitStructure.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE; //on déclenche via SW Start
	
	LL_ADC_REG_Init(ADC, &myInitStructure);
	
	//TIMER
	//enable clock
	MyTimer_Conf(Timer, 999, 719);
	MyTimer_IT_Conf(Timer, startConversion, 1);
	MyTimer_IT_Enable(Timer);
	
	//réglage de la période d'échantillonage des deux voies utilisées
	//LL_ADC_SetChannelSamplingTime(ADCx, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	//LL_ADC_SetChannelSamplingTime(ADC, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_1CYCLE_5);
}

void startADC(void) {
		MyTimer_Start(TIM);
}




