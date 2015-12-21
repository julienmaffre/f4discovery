/*----------------------------------------------------------------------------
 * Name:		test_led.c
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
#include "spi.h"
#include "mems_LIS3DSH.h"

/*----------------------------------------------------------------------------
	MAIN function
 *----------------------------------------------------------------------------*/

int _rcvd = 0x00000000;	
 
void initGreenLed(void)
{
	/* LED CLK enabled */
	LED_CLK_ENABLE();	
	
	/* LED Green Init and ON */
	LED_initLed(LED_GREEN);
	LED_initLed(LED_BLUE);
	LED_initLed(LED_RED);
	LED_initLed(LED_ORANGE);
	LED_switchON(LED_GREEN);		
}

int main (void) {

	initGreenLed();
	
	MEMS_CLK_ENABLE();
	MEMS_init();
	
	MEMS_setBitsInRegister(MEMS_CTRL_REG4, MEMS_CTRL_REG4_XEN | MEMS_CTRL_REG4_YEN | MEMS_CTRL_REG4_ZEN);
	MEMS_setValueBitsInRegister(MEMS_CTRL_REG4, MEMS_CTRL_REG4_ODR, (6 << 4));
	
	while (1) 
	{
		_rcvd = MEMS_getTemperature();
	}
}

