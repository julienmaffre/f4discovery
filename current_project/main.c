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
#include "rcc.h"
#include "timer.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 
int main (void) {

	/* LED CLK enabled */
	__LED_CLK_ENABLE();	
	
	/* LED Green Init and ON */
	LED_initLed(LED_GREEN);
	LED_initLed(LED_BLUE);
	LED_switchON(LED_GREEN);	
	
	/* Tests timer */
	__TIM6_CLK_ENABLE();
	
	TIM_enable(TIM6);

	TIM_initUpcount(TIM6);
	//TIM_setARR(TIM3, 8400);
	TIM_setPeriod(TIM6, 5000000);
	TIM_resetCNT(TIM6);
	//TIM_setPSC(TIM3, 9999);
	
	/*TIM3->ARR = 8400;
	TIM3->EGR &= ~(0x01);		///< reset counter
	TIM3->EGR |= 0x01;
	TIM3->PSC = 9999;	*/
  
	while (1) 
	{
		if(TIM6->SR & TIM_SR_UIF) // if UIF flag is set
		{
			TIM_resetIRFlag(TIM6);
			LED_toggle(LED_BLUE);
		}
	}
}

