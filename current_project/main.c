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
	uint8_t mems_data;
	
	initGreenLed();
	/* 
	* MEMS 	SCK: 		PA5
	* 			MOSI:		PA7	(input)
	*				MISO:		PA6	(output)
	*				CS:			PE3 (to choose if SPI or I2C - 0 for SPI)
	*/
		
	// SWITCH SPI ON in master mode	
	SPI1_CLK_ENABLE();

	MEMS_init();
	MEMS_setData(MEMS_CTRL_REG4, 0x60 | MEMS_CTRL_REG4_ZEN | MEMS_CTRL_REG4_YEN | MEMS_CTRL_REG4_XEN);	
	_rcvd = MEMS_getData(MEMS_CTRL_REG4);
	
	while (1) 
	{
		_rcvd = MEMS_getData(MEMS_OUT_Z_H);
		_rcvd = (_rcvd << 8) | MEMS_getData(MEMS_OUT_Z_L);
	}
				
	// Finally working
	// TODO: 
	// - Write drivers for SPI (3h) + Test + Comment
	// - Write service for MEMS (6h) + Test + Comment
	//		- understand speed rate
	

}

