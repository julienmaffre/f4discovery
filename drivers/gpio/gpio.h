/**
* @file 		gpio.h
* @brief		Header file of GPIO drivers.
* @author		Julien
* @version	1.0  
* @details	
*
*	Header file listing the functions required to initialize the GPIO,
* set or reset the different pins or read from a certain pin.
*
*		1. Use the GPIO_PinState enum for the Low, High and Undefined
* 	states of the pins.
*		2. Use the function defined in the RCC drivers to set the GPIO 
*		clocks.
*				ex: GPIOD_CLK_ENABLE();
*		3. The initialization of a pin usually goes like this (LED example):
*				GPIOD_CLK_ENABLE();
*				GPIO_initOutput(GPIOD, LED_NUMBER);
*				GPIO_initOutputPushpull(GPIOD, LED_NUMBER);
*				GPIO_initFastspeed(GPIOD, LED_NUMBER);
*				GPIO_initPullup(GPIOD, LED_NUMBER);
*				GPIO_setPin(GPIOD, LED_NUMBER);
*/

#ifndef GPIO_H
#define GPIO_H
 
#include <stdio.h>
#include <stm32f4xx.h>

#define GPIO_MAX_PIN 		16				///< Number max of pin for each port

/* Enum type to define the 3 logic levels of a pin */
typedef enum 
{
	GPIO_PIN_LOW = 0,
	GPIO_PIN_HIGH,
	GPIO_PIN_UNDEF
}GPIO_PinState;


/*----------------------------------------------------------------------------
  GPIO port mode register (GPIOx_MODER)
 *----------------------------------------------------------------------------*/

/**
 * GPIO pin initialization as input.
 * The function sets the appropriate 2 bits of the GPIO MODER register (0b00).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as an input.
 */
void GPIO_initInput(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin initialization as output.
 * The function sets the appropriate 2 bits of the GPIO MODER register (0b01).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as output.
 */
void GPIO_initOutput(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin initialization as alternate function.
 * The function sets the appropriate 2 bits of the GPIO MODER register (0b10).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as alternate.
 */
void GPIO_initAlternate(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin initialization as analog.
 * The function sets the appropriate 2 bits of the GPIO MODER register (0b11).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as analog.
 */
void GPIO_initAnalog(GPIO_TypeDef * GPIO, uint8_t pin);


/*----------------------------------------------------------------------------
  GPIO port output type register (GPIOx_OTYPER)
 *----------------------------------------------------------------------------*/
 
/**
 * GPIO pin initialization as push-pull (output).
 * The function sets the appropriate 1 bit of the GPIO OTYPER register (0b0).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as push-pull.
 */
void GPIO_initOutputPushpull(GPIO_TypeDef * GPIO, uint8_t pin);
 
/**
 * GPIO pin initialization as open-drain (output).
 * The function sets the appropriate 1 bit of the GPIO OTYPER register (0b1).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as open-drain.
 */
void GPIO_initOutputOpendrain(GPIO_TypeDef * GPIO, uint8_t pin);


/*----------------------------------------------------------------------------
  GPIO port output speed register (GPIOx_OSPEEDR)
 *----------------------------------------------------------------------------*/
 
/**
 * GPIO output pin initialization as low speed.
 * The function sets the appropriate 2 bits of the GPIO OSPEEDR register (0b00).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as low speed.
 */
void GPIO_initOutputLowspeed(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO output pin initialization as medium speed.
 * The function sets the appropriate 2 bits of the GPIO OSPEEDR register (0b01).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as medium speed.
 */
void GPIO_initOutputMediumspeed(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO output pin initialization as fast speed.
 * The function sets the appropriate 2 bits of the GPIO OSPEEDR register (0b10).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as fast speed.
 */
void GPIO_initOutputFastspeed(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO output pin initialization as high speed.
 * The function sets the appropriate 2 bits of the GPIO OSPEEDR register (0b11).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as high speed.
 */
void GPIO_initOutputHighspeed(GPIO_TypeDef * GPIO, uint8_t pin);


/*----------------------------------------------------------------------------
  GPIO port pull-up/pull-down register (GPIOx_PUPDR)
 *----------------------------------------------------------------------------*/
 
/**
 * GPIO pin initialization as no pull-up or pull-down.
 * The function sets the appropriate 2 bits of the GPIO PUPDR register (0b00).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as no pull-up or pull-down.
 */
void GPIO_initNopull(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin initialization as pull-up.
 * The function sets the appropriate 2 bits of the GPIO PUPDR register (0b01).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as no pull-up.
 */
void GPIO_initPullup(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin initialization as pull-down.
 * The function sets the appropriate 2 bits of the GPIO PUPDR register (0b10).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as no pull-down.
 */
void GPIO_initPulldown(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin initialization as reserved.
 * The function sets the appropriate 2 bits of the GPIO PUPDR register (0b11).
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as reserved.
 */
void GPIO_initReserved(GPIO_TypeDef * GPIO, uint8_t pin);


/*----------------------------------------------------------------------------
  GPIO port bit set/reset register (GPIOx_BSRR)
 *----------------------------------------------------------------------------*/
// Better to use BSRR than ODR because it's atomic.

/**
 * GPIO pin set as high logic level.
 * The function sets the appropriate 1 bit of the GPIO BSRRL register (0b1).
 * @param[in]	GPIO GPIO to set.
 * @param[in]	pin Pin set as high level.
 */
void GPIO_setPin(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin set as low logic level.
 * The function sets the appropriate 1 bit of the GPIO BSRRH register (0b1).
 * @param[in]	GPIO GPIO to reset.
 * @param[in]	pin Pin set as low level.
 */
void GPIO_resetPin(GPIO_TypeDef * GPIO, uint8_t pin);

/**
 * GPIO pin set as the indicated logic level.
 * The function sets the appropriate 1 bit of the GPIO BSRRL or BSRRH register (0b1).
 * @param[in]	GPIO GPIO to write.
 * @param[in]	pin Pin set as desired level.
 * @param[in]	pinState Desired logic level.
 */
void GPIO_writePin(GPIO_TypeDef * GPIO, uint8_t pin, GPIO_PinState pin_State);

/**
 * GPIO pin toggled.
 * The function toggles the appropriate 1 bit of the GPIO ODR register.
 * @param[in]	GPIO GPIO to toggle.
 * @param[in]	pin Pin to toggle.
 * @par This function is not atomic.
 */
void GPIO_togglePin(GPIO_TypeDef * GPIO, uint8_t pin);


/*----------------------------------------------------------------------------
  GPIO port input data register (GPIOx_IDR)
 *----------------------------------------------------------------------------*/
 
/**
 * Read logic state of GPIO pin.
 * The function reads the logic state of the desired GPIO pin from the IDR register.
 * @param[in]	GPIO GPIO to initialize.
 * @param[in]	pin Pin set as low level.
 * @retval GPIO_PIN_LOW
 * @retval GPIO_PIN_HIGH
 * @retval GPIO_PIN_UNDEF
 */
GPIO_PinState GPIO_readPin(GPIO_TypeDef * GPIO, uint8_t pin);

#endif
