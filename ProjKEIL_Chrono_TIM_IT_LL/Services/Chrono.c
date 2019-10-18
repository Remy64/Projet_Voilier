// A COMPLETER

/*
Service permettant de chornométrer jusqu'à 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 à TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Chrono.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_rcc.h"

// variable privée de type Time qui mémorise la durée mesurée
static Time Chrono_Time; // rem : static rend la visibilité de la variable Chrono_Time limitée à ce fichier 
const char DIGIT_CHR = 0x31;
char display[6];


// variable privée qui mémorise pour le module le timer utilisé par le module
static TIM_TypeDef * Chrono_Timer=TIM1; // init par défaut au cas où l'utilisateur ne lance pas Chrono_Conf avant toute autre fct.
static USART_TypeDef * Chrono_Usart=USART2;

// déclaration callback appelé toute les 10ms
char digit_of(char c){
	return DIGIT_CHR+c;
}
void Chrono_Task_10ms(void);
void Chrono_Conf_io(){
	//LL_GPIO_InitTypeDef my_LL_GPIO_Init_Struct ;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	
	//PIN 8(START) floatint input
	/*
	my_LL_GPIO_Init_Struct.Pin = LL_GPIO_PIN_8 ;
	my_LL_GPIO_Init_Struct.Mode = LL_GPIO_MODE_FLOATING;
	LL_GPIO_Init(GPIOC,&my_LL_GPIO_Init_Struct);
	*/
	LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_8,LL_GPIO_MODE_FLOATING);
	
	
	//PIN 6(STOP) floating input
	/*
	my_LL_GPIO_Init_Struct.Pin = LL_GPIO_PIN_8 ;
	my_LL_GPIO_Init_Struct.Mode = LL_GPIO_MODE_FLOATING;
	LL_GPIO_Init(GPIOC,&my_LL_GPIO_Init_Struct);
	*/
	LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_6,LL_GPIO_MODE_FLOATING);
	
	
	

	
	//PIN 10(LED) Output push pull
	/*
	my_LL_GPIO_Init_Struct.Pin = LL_GPIO_PIN_10;
	my_LL_GPIO_Init_Struct.Mode = LL_GPIO_MODE_OUTPUT_2MHz;
	my_LL_GPIO_Init_Struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOC,&my_LL_GPIO_Init_Struct);
	*/
	LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_10,LL_GPIO_MODE_OUTPUT_2MHz);
	LL_GPIO_SetPinOutputType(GPIOC,LL_GPIO_PIN_10,LL_GPIO_OUTPUT_PUSHPULL);
	
	
	
	
	
	
}

void Chrono_Background(){
	
	if(LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_8)){
		Chrono_Start();
	}
	else if(LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_6)){
		Chrono_Stop();
	}
}

/**
	* @brief  Configure le chronomètre. 
  * @note   A lancer avant toute autre fonction.
	* @param  Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void Chrono_Conf(TIM_TypeDef * Timer)
{
	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
	
	Chrono_Conf_io();
	
	// Fixation du Timer
	Chrono_Timer=Timer;

	// Réglage Timer pour un débordement à 10ms
	MyTimer_Conf(Chrono_Timer,999, 719);
	
	// Réglage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Chrono_Timer, Chrono_Task_10ms,3);
	
	// Validation IT
	MyTimer_IT_Enable(Chrono_Timer);

	
	
}
void Assign_Usart(USART_TypeDef * Usart){
	//Start GPIOA clock which contains USART Pins
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//Set pin PA2 ( TX ) in alternate push pull
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_2,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_2,LL_GPIO_OUTPUT_PUSHPULL);
	
	//Start USART Clock
	Chrono_Usart=Usart;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	
	//Init USART
	LL_USART_InitTypeDef Usart_Init_Struct;
	
	
	Usart_Init_Struct.TransferDirection = LL_USART_DIRECTION_TX;
	Usart_Init_Struct.BaudRate = 9600;
	Usart_Init_Struct.StopBits=LL_USART_STOPBITS_1;
	Usart_Init_Struct.DataWidth=LL_USART_DATAWIDTH_8B;
	Usart_Init_Struct.HardwareFlowControl=LL_USART_HWCONTROL_NONE;
	Usart_Init_Struct.OverSampling=LL_USART_OVERSAMPLING_16;
	Usart_Init_Struct.Parity=LL_USART_PARITY_NONE;
	
	LL_USART_Init(Chrono_Usart,&Usart_Init_Struct);
	
	LL_USART_Enable(Usart);
}


/**
	* @brief  Démarre le chronomètre. 
  * @note   si la durée dépasse 59mn 59sec 99 Hund, elle est remise à zéro et repart
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Start(void)
{
	MyTimer_Start(Chrono_Timer);
}


/**
	* @brief  Arrête le chronomètre. 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Stop(void)
{
	MyTimer_Stop(Chrono_Timer);
}


/**
	* @brief  Remet le chronomètre à 0 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Reset(void)
{
  // Arrêt Chrono
	MyTimer_Stop(Chrono_Timer);

	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
}


/**
	* @brief  Renvoie l'adresse de la variable Time privée gérée dans le module Chrono.c
  * @note   
	* @param  Aucun
  * @retval adresse de la variable Time
  */
Time * Chrono_Read(void)
{
	return &Chrono_Time;
}




/**
	* @brief  incrémente la variable privée Chron_Time modulo 60mn 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Task_10ms(void)
{ 
	
	Chrono_Time.Hund++;
	display[0] = digit_of(Chrono_Time.Hund%10);
	display[1] = digit_of(Chrono_Time.Hund/10);
	char toDisplay = 0;
	if (Chrono_Time.Hund==100)
	{
		toDisplay=1;
		Chrono_Time.Sec++;
		display[2] = digit_of(Chrono_Time.Sec%10);
		display[3] = digit_of(Chrono_Time.Sec/10);
		LL_USART_TransmitData8(Chrono_Usart,'b');
		display[0]=digit_of(0);
		display[1]=digit_of(DIGIT_CHR+0);
	
		Chrono_Time.Hund=0;
	}

	
	if (Chrono_Time.Sec==60)
	{
		Chrono_Time.Min++;
		Chrono_Time.Sec=0;
		display[4] = digit_of(Chrono_Time.Min%10);
		display[5] = digit_of(Chrono_Time.Min/10);
		display[2]=digit_of(0);
		display[3]=digit_of(0);
	}
	if (Chrono_Time.Min==60)
	{
		Chrono_Time.Min=0;
		display[4]=digit_of(0);
		display[5]=digit_of(0);
		
	}
	if(toDisplay){
		for(int i=0;i<3;i++){
			while(!LL_USART_IsActiveFlag_TXE(Chrono_Usart));
			LL_USART_TransmitData8(Chrono_Usart,display[i]);
			while(!LL_USART_IsActiveFlag_TXE(Chrono_Usart));
			LL_USART_TransmitData8(Chrono_Usart,display[i+1]);
			while(!LL_USART_IsActiveFlag_TXE(Chrono_Usart));
			LL_USART_TransmitData8(Chrono_Usart,':');
		}
		while(!LL_USART_IsActiveFlag_TXE(Chrono_Usart));
		LL_USART_TransmitData8(Chrono_Usart,0x0D);
	
	}
	
}


