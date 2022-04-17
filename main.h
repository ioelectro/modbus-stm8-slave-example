#ifndef __main_h__
#define __main_h__

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */
#define LED_GPIO_PORT  GPIOA
#define LED_GPIO_PIN   GPIO_PIN_3

/* Public function prototypes -----------------------------------------------*/
void TimOutTimer_OVF(void);
void Uart1_RXIntrrupt(void);
void TimeOutTimer_Reset(void);

#endif
