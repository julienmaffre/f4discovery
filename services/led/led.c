/**
* @file 		led.h
* @brief		Header file of LED service.
* @author		Julien
* @date			26/01/2015
* @version	1.0  
* @details	
*
*	Header file listing the functions required to initialize the 4 LEDS
* of the STM32F4 discovery board and switch them ON/OFF or toggle.
*
* 	1. Use it as follow:
*			__LED_CLK_ENABLE();
*			LED_initLed(LED_GREEN);
*			LED_switchON(LED_GREEN);	
*			LED_switchOFF(LED_GREEN);
*			LED_toggle(LED_GREEN);
*
*/

#include "led.h"

/**
 * Returns pin number of the led according to its color.
 * The function matches the pin number with the color (see schematics).
 * @param[in]	LED color of the led (see LED_Color typedef).
 * @retval PIN_LED_GREEN
 * @retval PIN_LED_ORANGE
 * @retval PIN_LED_RED
 * @retval PIN_LED_BLUE
 */
u8 LED_getPinNumber(LED_Color LED)
{
	u8 pin_LED;
	
	if (LED == LED_GREEN)
		pin_LED = PIN_LED_GREEN;
	else if (LED == LED_ORANGE)
		pin_LED = PIN_LED_ORANGE;
	else if (LED == LED_RED)
		pin_LED = PIN_LED_RED;
	else if (LED == LED_BLUE)
		pin_LED = PIN_LED_BLUE;	
	else 
		pin_LED = PIN_LED_RED;		// default case
	
	return pin_LED;
}

/**
 * Initializes led based on its color.
 * The function initialises the appropriate GPIO pin as an Output push-pull, fast-speed pin.
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_initLed(LED_Color LED)
{
	u8 pin_LED = LED_getPinNumber(LED);
	
	GPIO_initOutput(GPIO_LED, pin_LED);
	GPIO_initOutputPushpull(GPIO_LED, pin_LED);
	GPIO_initOutputFastspeed(GPIO_LED, pin_LED);
}

/**
 * Switches ON led based on its color.
 * The function sets the appropriate GPIO pin.
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_switchON(LED_Color LED)
{
	u8 pin_LED = LED_getPinNumber(LED);
	GPIO_setPin(GPIO_LED, pin_LED);
}

/**
 * Switches OFF led based on its color.
 * The function resets the appropriate GPIO pin.
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_switchOFF(LED_Color LED)
{
	u8 pin_LED = LED_getPinNumber(LED);
	GPIO_resetPin(GPIO_LED, pin_LED);
}

/**
 * Toggles led based on its color.
 * The function toggles the appropriate GPIO pin (ON->OFF and OFF->ON).
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_toggle(LED_Color LED)
{
	u8 pin_LED = LED_getPinNumber(LED);
	GPIO_togglePin(GPIO_LED, pin_LED);
}

