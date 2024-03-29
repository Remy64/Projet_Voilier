#include "ADC_Driver.h"
static ADC_TypeDef *ADC;
static TIM_TypeDef *TIM;
static int X = 0;
static int Y = 0;
static int batteryLevel = 0;
static int currentChannel = 1;

//Once started, the ADC continously switch between three channels at each interruption to update the X,Y and Battery fields

//Update function, called by an interruption
void startConversion(void) {
	//ADDON bit has to be set twice to start conversion
	LL_ADC_Enable(ADC);
	LL_ADC_Enable(ADC);
	
	//X aquisition disabled
	/*if(currentChannel == 0) {
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_10);*/
	if(currentChannel == 1) {
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_11);
	} else if(currentChannel == 2) {
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_12);
	}
	
	LL_ADC_REG_StartConversionSWStart(ADC);
	while(!LL_ADC_IsActiveFlag_EOS(ADC)){}
	int result = LL_ADC_REG_ReadConversionData32(ADC);
	
	if(currentChannel == 1) {
		Y = result;
	} else if(currentChannel == 2) {
		batteryLevel = result;
	} 
	
	
	currentChannel++;
	currentChannel%=3;
	currentChannel++;
	//End conversion by resetting the ADDON bit
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
	
	
	//on divise la fr�quence de l'ADC par 4 pour s'assurer que la fr�quence de l'ADC soit inf�rieure � 14 MHz
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_8);
	
	//init with structure
	LL_ADC_REG_InitTypeDef myInitStructure;
	
	myInitStructure.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	myInitStructure.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	myInitStructure.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	myInitStructure.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	myInitStructure.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE; //on d�clenche via SW Start
	LL_ADC_REG_Init(ADC, &myInitStructure);
	
	//TIMER
	//Enable clock
	MyTimer_IT_Conf(Timer, startConversion, 1);
	MyTimer_IT_Enable(Timer);
}

void startADC(void) {
		MyTimer_Start(TIM);
}

