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

void transmitText(USART_TypeDef * Usart, const char * txt) {
char c;
while (( c = *(txt++) ) != 0 )
{
while(!LL_USART_IsActiveFlag_TXE(Usart)) {}
	LL_USART_TransmitData8(Usart,c);
}
}

void transmitAlert(USART_TypeDef * Usart) {
	
	while(!LL_USART_IsActiveFlag_TXE(Usart)) {}
	LL_USART_TransmitData8(Usart,'L');

	while(!LL_USART_IsActiveFlag_TXE(Usart));
	LL_USART_TransmitData8(Usart,'O');

	while(!LL_USART_IsActiveFlag_TXE(Usart));
	LL_USART_TransmitData8(Usart,'W');
	
}

	

void set_rtc(void) {//TODO

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

	

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
	//LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	LL_I2C_InitTypeDef init;

	init.ClockSpeed = 4096;

	init.DutyCycle = LL_I2C_DUTYCYCLE_2;

	init.PeripheralMode = LL_I2C_MODE_I2C;

	init.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;

	init.TypeAcknowledge = LL_I2C_ACK;

	init.OwnAddress1 = 0;

	LL_I2C_Init(I2C2, &init);
	
	/* Configure Event IT:
   *  - Set priority for I2C1_EV_IRQn
   *  - Enable I2C1_EV_IRQn
   */
  NVIC_SetPriority(I2C2_EV_IRQn, 0);  
  NVIC_EnableIRQ(I2C2_EV_IRQn);

  /* Configure Error IT:
   *  - Set priority for I2C1_ER_IRQn
   *  - Enable I2C1_ER_IRQn
   */
  NVIC_SetPriority(I2C2_ER_IRQn, 0);  
  NVIC_EnableIRQ(I2C2_ER_IRQn);
	
	LL_I2C_EnableIT_EVT(I2C2);
  LL_I2C_EnableIT_ERR(I2C2);
	
	 /* Configure SCL Pin as : Alternate function, High Speed, Open drain, Pull up */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);

  /* Configure SDA Pin as : Alternate function, High Speed, Open drain, Pull up */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_OPENDRAIN);
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_11, LL_GPIO_PULL_UP);

	while(LL_I2C_IsActiveFlag_BUSY(I2C2)) {}
	LL_I2C_GenerateStartCondition(I2C2);


	while(!LL_I2C_IsActiveFlag_SB(I2C2)) {}
	LL_I2C_TransmitData8 (I2C2, 0xD1);
	while(!LL_I2C_IsActiveFlag_RXNE(I2C2)) ;
	

	while(!LL_I2C_IsActiveFlag_ADDR(I2C2)) {}
	LL_I2C_ClearFlag_ADDR(I2C2);

}

int getDateTime(void) {//TODO
	
	volatile int date ;
	// 0x00HHMMSS in bcd format
	while (!LL_I2C_IsActiveFlag_RXNE(I2C2)) {}
	date = LL_I2C_ReceiveData8(I2C2);
		
	LL_I2C_AcknowledgeNextData(I2C2, LL_I2C_ACK) ;
	return date ;
		
}
