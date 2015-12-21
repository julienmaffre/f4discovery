/*----------------------------------------------------------------------------
 * Name:    test_led.c
 * Purpose: LED test file
 * Note(s): Tested.
 *----------------------------------------------------------------------------
 *
 *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stm32f4xx.h>
#include "led.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 
int main (void) {

	/* LED CLK enabled */
	LED_CLK_ENABLE();	
	
	/* LED Init */
	LED_initLed(LED_GREEN);
	LED_initLed(LED_ORANGE);
	LED_initLed(LED_BLUE);
	LED_initLed(LED_RED);
		
	/* Switch ON/OFF and Toggle */
	LED_switchON(LED_GREEN);	
	LED_switchOFF(LED_GREEN);
	
	LED_switchON(LED_RED);
	
	LED_toggle(LED_ORANGE);
	LED_toggle(LED_ORANGE);
	
	LED_switchOFF(LED_BLUE);
	LED_switchON(LED_BLUE);

  while(1);
}

