#ifndef COD_INC_DRIVER_H
#define COD_INC_DRIVER_H
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "Mytimer.h"
void configure_codeur(void);
int mesurer_angle(void) ;
#endif
