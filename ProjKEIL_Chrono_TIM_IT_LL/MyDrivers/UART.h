#include "stm32f1xx_ll_usart.h"
#include <time.h>
#include <stdio.h>
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_rtc.h"
#include <stdlib.h>

void Config_Usart(USART_TypeDef *Usart);

void set_rtc(void);

void getDateTime(void);

void transmitAlert(USART_TypeDef * Usart);
