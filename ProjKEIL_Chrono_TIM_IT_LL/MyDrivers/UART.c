#include "UART.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_rtc.h"
#include <stdlib.h>
#include <time.h>

void Config_Usart(USART_TypeDef * Usart){
	//Start GPIOA clock which contains USART Pins
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	//Set pin PA9 ( TX ) in alternate push pull
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_11,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_11,LL_GPIO_OUTPUT_PUSHPULL);
	
	//Start USART Clock
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	
	
	//Init USART
	LL_USART_InitTypeDef Usart_Init_Struct;
	
	
	Usart_Init_Struct.TransferDirection = LL_USART_DIRECTION_TX;
	Usart_Init_Struct.BaudRate = 9600;
	Usart_Init_Struct.StopBits=LL_USART_STOPBITS_1;
	Usart_Init_Struct.DataWidth=LL_USART_DATAWIDTH_8B;
	Usart_Init_Struct.HardwareFlowControl=LL_USART_HWCONTROL_NONE;
	Usart_Init_Struct.OverSampling=LL_USART_OVERSAMPLING_16;
	Usart_Init_Struct.Parity=LL_USART_PARITY_NONE;
	
	LL_USART_Init(Usart,&Usart_Init_Struct);
	
	LL_USART_Enable(Usart);
}

char * recupererHeure(void) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
	char* str_out = malloc(sizeof(char)*22);
  sprintf(str_out, "%d/%d/%d : %d:%d:%d", tm.tm_mday,  tm.tm_mon + 1,  tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return str_out;
}

void set_rtc(void) {
	LL_RTC_InitTypeDef initStructRTC;
	initStructRTC.AsynchPrescaler = ;
	initStructRTC.OutPutSource = LL_RTC_CALIB_OUTPUT_RTCCLOCK;

	LL_PWR_EnableBkUpAccess();
	LL_RCC_ForceBackupDomainReset();
	LL_RCC_ReleaseBackupDomainReset();

	LL_RCC_LSE_Enable();

	/* Wait untill LSE is ready */
	while (LL_RCC_LSE_IsReady() != 1) {};

	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);

	LL_RCC_EnableRTC();

	if (LL_RTC_DeInit(RTC) != SUCCESS) {
			return -EIO;
	}

	if (LL_RTC_Init(RTC, (LL_RTC_InitTypeDef *)&initData) != SUCCESS) {
			return -EIO;
	}

	LL_RTC_EnableShadowRegBypass(RTC);
}

char * getDateTime(void) {
	// 0x00HHMMSS in bcd format
	int t = LL_RTC_TIME_Get(RTC);
}