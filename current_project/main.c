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
#include "mems.h"

/*----------------------------------------------------------------------------
	MAIN function
 *----------------------------------------------------------------------------*/

int _rcvd = 0x0000;	
 
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
	mems_data = 0x69;
	MEMS_setData(0x20, mems_data);
	
	while (1) 
	{
		_rcvd = MEMS_getData(0x0C);
	}
				
	// Finally working
	// TODO: 
	// - Write drivers for SPI (3h) + Test + Comment
	// 		- double check uint16_t to uint8_t conversions
	// - Write service for MEMS (6h) + Test + Comment
	//		- understand speed rate
	

}

