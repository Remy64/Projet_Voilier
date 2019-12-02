#include "stm32f1xx_ll_usart.h"
#include <time.h>
#include <stdio.h>

void Config_Usart(USART_TypeDef *Usart);
void set_rtc(void);
void getDateTime(void);
void transmitAlert(USART_TypeDef * Usart);