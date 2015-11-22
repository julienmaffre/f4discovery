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

#ifndef LED_H
#define LED_H
 
#include <stdio.h>
#include <stm32f4xx.h>
#include "gpio.h"
#include "rcc.h"
 
#define GPIO_LED 		GPIOD 		///< GPIO handling 4 user leds

#define __LED_CLK_ENABLE()				__GPIOD_CLK_ENABLE()		///< Macro to switch ON the LED CLK
 
#define PIN_LED_GREEN 	12				///< Pin number of green led
#define PIN_LED_ORANGE 	13				///< Pin number of orange led
#define PIN_LED_RED 		14				///< Pin number of red led
#define PIN_LED_BLUE 		15				///< Pin number of blue led

typedef enum
{
	LED_GREEN = 0,
	LED_ORANGE,
	LED_RED, 
	LED_BLUE	
}LED_Color;

/**
 * Returns pin number of the led according to its color.
 * The function matches the pin number with the color (see schematics).
 * @param[in]	_led color of the led (see LED_Color typedef).
 * @retval PIN_LED_GREEN
 * @retval PIN_LED_ORANGE
 * @retval PIN_LED_RED
 * @retval PIN_LED_BLUE
 */
u8 LED_getPinNumber(LED_Color LED);

/**
 * Initializes led based on its color.
 * The function initialises the appropriate GPIO pin as an Output push-pull, fast-speed pin.
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_initLed(LED_Color LED);
 
/**
 * Switches ON led based on its color.
 * The function sets the appropriate GPIO pin.
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_switchON(LED_Color LED);

/**
 * Switches OFF led based on its color.
 * The function resets the appropriate GPIO pin.
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_switchOFF(LED_Color LED);

/**
 * Toggles led based on its color.
 * The function toggles the appropriate GPIO pin (ON->OFF and OFF->ON).
 * @param[in]	LED color of the led (see LED_Color typedef).
 */
void LED_toggle(LED_Color LED);

 
 
 
 
 
#endif

