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
 * @param[in]	_led color of the led (see LED_Color typedef).
 * @retval PIN_LED_GREEN
 * @retval PIN_LED_ORANGE
 * @retval PIN_LED_RED
 * @retval PIN_LED_BLUE
 */
u8 LED_getPinNumber(LED_Color _led)
{
	u8 pin_led;
	
	if (_led == LED_GREEN)
		pin_led = PIN_LED_GREEN;
	else if (_led == LED_ORANGE)
		pin_led = PIN_LED_ORANGE;
	else if (_led == LED_RED)
		pin_led = PIN_LED_RED;
	else if (_led == LED_BLUE)
		pin_led = PIN_LED_BLUE;	
	else 
		pin_led = PIN_LED_RED;		// default case
	
	return pin_led;
}

/**
 * Initializes led based on its color.
 * The function initialises the appropriate GPIO pin as an Output push-pull, fast-speed pin.
 * @param[in]	_led color of the led (see LED_Color typedef).
 */
void LED_initLed(LED_Color _led)
{
	u8 pin_led = LED_getPinNumber(_led);
	
	GPIO_initOutput(GPIO_LED, pin_led);
	GPIO_initOutputPushpull(GPIO_LED, pin_led);
	GPIO_initOutputFastspeed(GPIO_LED, pin_led);
}

/**
 * Switches ON led based on its color.
 * The function sets the appropriate GPIO pin.
 * @param[in]	_led color of the led (see LED_Color typedef).
 */
void LED_switchON(LED_Color _led)
{
	u8 pin_led = LED_getPinNumber(_led);
	GPIO_setPin(GPIO_LED, pin_led);
}

/**
 * Switches OFF led based on its color.
 * The function resets the appropriate GPIO pin.
 * @param[in]	_led color of the led (see LED_Color typedef).
 */
void LED_switchOFF(LED_Color _led)
{
	u8 pin_led = LED_getPinNumber(_led);
	GPIO_resetPin(GPIO_LED, pin_led);
}

/**
 * Toggles led based on its color.
 * The function toggles the appropriate GPIO pin (ON->OFF and OFF->ON).
 * @param[in]	_led color of the led (see LED_Color typedef).
 */
void LED_toggle(LED_Color _led)
{
	u8 pin_led = LED_getPinNumber(_led);
	GPIO_togglePin(GPIO_LED, pin_led);
}

