/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: Template main file
 * Note(s): 
 *----------------------------------------------------------------------------
 *
 *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stm32f4xx.h>
#include "gpio.h"
#include "rcc.h"

#define LED_NUMBER 14
#define LED_NUMBER2 (LED_NUMBER+1)
#define LED_NUMBER3 (LED_NUMBER2+1)
#define LED_NUMBER4 (LED_NUMBER3+1)


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 
int main (void) {

	__GPIOD_CLK_ENABLE();
	GPIO_initOutput(GPIOD, LED_NUMBER);
	GPIO_initOutputPushpull(GPIOD, LED_NUMBER);
	GPIO_initOutputFastspeed(GPIOD, LED_NUMBER);
	GPIO_initPullup(GPIOD, LED_NUMBER);
	GPIO_setPin(GPIOD, LED_NUMBER);	
	GPIO_writePin(GPIOD, LED_NUMBER, GPIO_PIN_LOW);
	
	GPIO_initOutput(GPIOD, 0);
	GPIO_initPullup(GPIOD, 0);
	
	if (GPIO_readPin(GPIOA, 0) == GPIO_PIN_LOW)
		GPIO_writePin(GPIOD, LED_NUMBER, GPIO_PIN_HIGH);
	else if (GPIO_readPin(GPIOA, 0) == GPIO_PIN_HIGH)
		GPIO_writePin(GPIOD, LED_NUMBER, GPIO_PIN_HIGH);
	
	
	
		
  while(1);
}

