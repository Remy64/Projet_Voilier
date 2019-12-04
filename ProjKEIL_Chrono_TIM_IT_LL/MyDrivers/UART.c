#include "UART.h"




void Config_Usart(USART_TypeDef * Usart){

	//Start GPIOA clock which contains USART Pins

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	//Set pin PA9 ( TX ) in alternate push pull

	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_9,LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_9,LL_GPIO_OUTPUT_PUSHPULL);
	
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_11,LL_GPIO_MODE_OUTPUT);
	
	LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_11);
	
	
	
	

	

	//Start USART Clock

	if(Usart == USART1) {

		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	} else if(Usart == USART2) {

		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	} else if(Usart == USART3) {

		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

	}

	

	

	//Init USART

	LL_USART_InitTypeDef Usart_Init_Struct;

	

	

	Usart_Init_Struct.TransferDirection = LL_USART_DIRECTION_TX;

	Usart_Init_Struct.BaudRate = 9600;

	Usart_Init_Struct.StopBits=LL_USART_STOPBITS_1;

	Usart_Init_Struct.DataWidth=LL_USART_DATAWIDTH_8B;

	Usart_Init_Struct.HardwareFlowControl=LL_USART_HWCONTROL_NONE;

	Usart_Init_Struct.OverSampling=LL_USART_OVERSAMPLING_16;

	Usart_Init_Struct.Parity=LL_USART_PARITY_NONE;

	

	LL_USART_Init(Usart, &Usart_Init_Struct);

	

	LL_USART_Enable(Usart);

}



void transmitAlert(USART_TypeDef * Usart) {
	
	while(!LL_USART_IsActiveFlag_TXE(Usart)) {}
	LL_USART_TransmitData8(Usart,'l');

	while(!LL_USART_IsActiveFlag_TXE(Usart));
	LL_USART_TransmitData8(Usart,'o');

	while(!LL_USART_IsActiveFlag_TXE(Usart));
	LL_USART_TransmitData8(Usart,'w');

	while(!LL_USART_IsActiveFlag_TXE(Usart));
	LL_USART_TransmitData8(Usart,' ');
/*
	LL_USART_TransmitData8(Usart,'b');

	LL_USART_TransmitData8(Usart,'a');

	LL_USART_TransmitData8(Usart,'t');

	LL_USART_TransmitData8(Usart,'t');

	LL_USART_TransmitData8(Usart,'e');

	LL_USART_TransmitData8(Usart,'r');

	LL_USART_TransmitData8(Usart,'y');
	*/

	

	

}

	

void set_rtc(void) {

	/*

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_BKP);

	

	LL_RTC_InitTypeDef initStructRTC;

	initStructRTC.AsynchPrescaler = 0;

	initStructRTC.OutPutSource = LL_RTC_CALIB_OUTPUT_RTCCLOCK;

	

	LL_RCC_LSE_Enable();



	// Wait untill LSE is ready

	while (LL_RCC_LSE_IsReady() != 1) {}



	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);

	LL_RCC_EnableRTC();

	LL_RTC_Init(RTC, &initStructRTC);

	*/

	

	

}



void getDateTime(void) {

	// 0x00HHMMSS in bcd format

	int t = LL_RTC_TIME_Get(RTC);

}