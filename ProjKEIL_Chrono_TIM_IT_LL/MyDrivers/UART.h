#ifndef UART_H
#define UART_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_rtc.h"
#include "stm32f1xx_ll_i2c.h"


void Config_Usart(USART_TypeDef *Usart);//Prepare the UART for transmission

void transmitAlert(USART_TypeDef * Usart);//Send a LOW message via UART

void set_rtc(void);//TODO configure I2C/RTC communication

int getDateTime(void);//TODO uses I2C to get the date via a RTC
#endif
