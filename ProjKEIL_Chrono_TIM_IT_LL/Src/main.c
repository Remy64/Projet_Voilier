/**
  ******************************************************************************
  * @file    Templates_LL/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body through the LL API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_tim.h" 
#include "Ecoute.h"
#include "Plate.h"
#include "Chrono.h"
#include "RX_Rcv.h"
#include "stdlib.h"

void  SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	int view;


// R:\LLGDB\CubeF1\Drivers\STM32F1xx_HAL_Driver\HTML
//To see PIN X N in Loic analyser : PORTX.N
//MOE a 1 -> TIMx_BTRD dans le genre
int main(void)
{
  /* Configure the system clock to 72 MHz */
  SystemClock_Config();
	
//PWM TESTS
//UNCOMMENT EACH SECTIONS INDIVIDUALLY TO PERFORM TESTS
	
	/*
	//SECTION 1 : MANUAL TEST PWM DRIVER PORT A8 TIMER 1
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_8,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_8,LL_GPIO_OUTPUT_PUSHPULL); // ATTENTION
	TIM1->CCER |= TIM_CCER_CC1E;
	TIM1->BDTR |= TIM_BDTR_MOE;
	PWM_TypeDef pwm =init_PWM(TIM1,50,1);//Period T = 0.02s
	//Manual Test high period time setting
	//set_PWM_TH(&pwm,0.005);//0.02/4
	//set_PWM_TH(&pwm,0.01);
	//set_PWM_TH(&pwm,0.015);
	//set_PWM_TH(&pwm,0.02);
	
	//Manual Test high period ratio setting(Uncomment only one of the manuals and automated test cases)
	//set_PWM_RATIO(&pwm,0.25);
	//set_PWM_RATIO(&pwm,0.5);
	//set_PWM_RATIO(&pwm,0.75);
	//set_PWM_RATIO(&wm,1);
	
	//Automated cycling ratio test
	//Cycle infinitely through 0%;25%;50%;75%;100%
	int i=0;
	int c=0;
  while (1)
  {		
		if(++i>1000000){
			c++;
			c%=5;
			i=0;
			set_PWM_RATIO(&pwm,c*0.25);
		}
  }
	//END SECTION 1
	*/
	
	/*
	//SECTION 2: TEST PWM_CONF FOR COMPONENT : ECOUTE
	//Increases angle from 0 to 180 by 10 degrees steps then stops PWM
	//WATCH PA8
	conf_pwm_ecoute();
	int i=0;
	double c=0.0;
	set_angle_ecoute(0);
	while (c<=180.0){
		if(++i>500000){
			c+=10;
			i=0;
			set_angle_ecoute(c);
		}
	}
	set_angle_ecoute(0);
	//END SECTION 2
	*/
	
	
	/*
	//SECTION 3 : TEST PWM FOR COMPONENT : PLATE
	//Increases mean voltage from 0 to 12 by 0.5V steps then stops PWM
	//WATCH PA1
	conf_pwm_plate();
	set_orientation(1);
	int i=0;
	double c= 0.0;
	set_servo_mean_voltage(c);
	while (c<12.0){
		if(++i>50000){
			c+=0.5;
			if(c>6.0){
				set_orientation(0);
			}
			i=0;
			double modc = c;
			if(modc>6)modc=c-6;
			set_servo_mean_voltage(modc);
		}
	}
	TIM2->CCER &= ~TIM_CCER_CC2E;
	//END SECTION 3
	*/
	
	//SECTION 4 TEST PWM_IN FOR COMPONENT : RX_RCV
	//Stores pwm period and duty cycles
	/*
	
054D

00BF
0090
0071
	*/
	conf_pwm_plate();
	set_orientation(1);
	int period;
	int duty;
	int range_from_zero;
	double ratio;
	conf_pwm_in_rx_rcv();
	while(1){
		period = get_pwm_in_period();
		duty = get_pwm_in_duty();
		ratio = get_pwm_in_ratio();
		
		range_from_zero = duty-153;
		
		if(ratio ==0){//ATTENTION , A AFFINER POUR EVITER ARRACHEMENT DU CABLE
			forward();
		}
		else if(range_from_zero>3){
			turn(1,ratio);
			ratio = abs(range_from_zero)/25.0;
		}
		else if(range_from_zero<-3){
			turn(0,ratio);
			ratio = abs(range_from_zero)/35.0;
		}
		else{
			forward();
		}
	}
	
		
}







/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Enable HSE oscillator */
	// ********* Commenter la ligne ci-dessous pour MCBSTM32 *****************
	// ********* Conserver la ligne si Nucléo*********************************
  //LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 72MHz */
  LL_Init1msTick(72000000); // utile lorsqu'on utilise la fonction LL_mDelay

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(72000000);
}



/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
