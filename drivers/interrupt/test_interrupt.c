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
#include "interrupt.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 
void TIM3_IRQHandler(void)
{
	TIM_resetIRFlag(TIM3);
	LED_toggle(LED_BLUE);
	LED_toggle(LED_GREEN);
	LED_toggle(LED_RED);
	LED_toggle(LED_ORANGE);
}

void EXTI0_IRQHandler(void)
{
	LED_toggle(LED_BLUE);
	EXTI_clearPending(0);
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
}

int main (void) {

	/* LED CLK enabled */
	__LED_CLK_ENABLE();	
	
	/* LED Green Init and ON */
	LED_initLed(LED_GREEN);
	LED_initLed(LED_BLUE);
	LED_initLed(LED_RED);
	LED_initLed(LED_ORANGE);
	LED_switchON(LED_GREEN);	
	
	/* Tests timer */
	__TIM3_CLK_ENABLE();
	
	TIM_enable(TIM3);
	TIM_initUpcount(TIM3);
	TIM_setPeriod(TIM3, 500000);
	TIM_resetCNT(TIM3);
	TIM3->DIER = TIM_DIER_UIE;
	TIM_resetIRFlag(TIM3);
	
	NVIC_EnableIRQ(TIM3_IRQn); // Enable interrupt from TIM3 (NVIC level)
	NVIC_EnableIRQ(EXTI0_IRQn);
	EXTI_enableLine(0);
	EXTI_setFallingEdge(0);
	EXTI_setRisingEdge(0);
	
	__SYSCFG_CLK_ENABLE();
	EXTI_setLinePin(0, SYSCFG_EXTICR_EXTI_PA);
	EXTI_setLinePin(1, SYSCFG_EXTICR_EXTI_PB);
	EXTI_setLinePin(4, SYSCFG_EXTICR_EXTI_PC);
	EXTI_setLinePin(4, SYSCFG_EXTICR_EXTI_PI);
	EXTI_setLinePin(11, SYSCFG_EXTICR_EXTI_PC);
	EXTI_setLinePin(10, SYSCFG_EXTICR_EXTI_PC);
	EXTI_setLinePin(13, SYSCFG_EXTICR_EXTI_PC);
	EXTI_setLinePin(13, SYSCFG_EXTICR_EXTI_PI);
	EXTI_setLinePin(250, SYSCFG_EXTICR_EXTI_PC);
	EXTI_setLinePin(250, SYSCFG_EXTICR_EXTI_PI);
	EXTI_setLinePin(16, SYSCFG_EXTICR_EXTI_PB);

	while (1);
}

