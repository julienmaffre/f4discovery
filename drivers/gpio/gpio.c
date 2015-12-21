/**
* @file 		gpio.c
* @brief		Source file of GPIO drivers.
* @author		Julien
* @date			24/01/2015
* @version	1.0  
* @details	
*
*	Source file of the functions required to initialize the GPIO,
* set or reset the different pins or read from a certain pin.
*
*/

#include "gpio.h"

/*----------------------------------------------------------------------------
  GPIO port mode register (GPIOx_MODER)
 *----------------------------------------------------------------------------*/

void GPIO_initInput(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->MODER &= ~(0x3 << 2*pin);
	}
}

void GPIO_initOutput(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->MODER &= ~(0x3 << 2*pin);
		GPIO->MODER |= (0x1 << 2*pin);
	}
}

void GPIO_initAlternate(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->MODER &= ~(0x3 << 2*pin);
		GPIO->MODER |= (0x2 << 2*pin);
	}
}

void GPIO_initAnalog(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->MODER &= ~(0x3 << 2*pin);
		GPIO->MODER |= (0x3 << 2*pin);
	}
}


/*----------------------------------------------------------------------------
  GPIO port output type register (GPIOx_OTYPER)
 *----------------------------------------------------------------------------*/

void GPIO_initOutputPushpull(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->OTYPER &= ~(0x1 << pin);
	}
}

void GPIO_initOutputOpendrain(GPIO_TypeDef * GPIO, uint8_t pin)
{
		if (pin < GPIO_MAX_PIN) 
	{
		GPIO->OTYPER &= ~(0x1 << pin);
		GPIO->OTYPER |= (0x1 << pin);
	}
}


/*----------------------------------------------------------------------------
  GPIO port output speed register (GPIOx_OSPEEDR)
 *----------------------------------------------------------------------------*/
 
void GPIO_initOutputLowspeed(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->OSPEEDR &= ~(0x3 << 2*pin);
	}
}

void GPIO_initOutputMediumspeed(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->OSPEEDR &= ~(0x3 << 2*pin);
		GPIO->OSPEEDR |= (0x1 << 2*pin);
	}
}

void GPIO_initOutputFastspeed(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->OSPEEDR &= ~(0x3 << 2*pin);
		GPIO->OSPEEDR |= (0x2 << 2*pin);
	}
}

void GPIO_initOutputHighspeed(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->OSPEEDR &= ~(0x3 << 2*pin);
		GPIO->OSPEEDR |= (0x3 << 2*pin);
	}
}


/*----------------------------------------------------------------------------
  GPIO port pull-up/pull-down register (GPIOx_PUPDR)
 *----------------------------------------------------------------------------*/
 
void GPIO_initNopull(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->PUPDR &= ~(0x3 << 2*pin);
		GPIO->PUPDR |= (0x0 << 2*pin);
	}
}

void GPIO_initPullup(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->PUPDR &= ~(0x3 << 2*pin);
		GPIO->PUPDR |= (0x1 << 2*pin);
	}
}

void GPIO_initPulldown(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->PUPDR &= ~(0x3 << 2*pin);
		GPIO->PUPDR |= (0x2 << 2*pin);
	}
}

void GPIO_initReserved(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->PUPDR &= ~(0x3 << 2*pin);
		GPIO->PUPDR |= (0x3 << 2*pin);
	}
}


/*----------------------------------------------------------------------------
  GPIO port bit set/reset register (GPIOx_BSRR)
 *----------------------------------------------------------------------------*/
// Note: better to use BSRR than ODR because of its atomicity.

void GPIO_setPin(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->BSRRL &= ~(0x1 << pin);
		GPIO->BSRRL |= (0x1 << pin);
	}
}	

void GPIO_resetPin(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->BSRRH &= ~(0x1 << pin);
		GPIO->BSRRH |= (0x1 << pin);
	}
}

void GPIO_writePin(GPIO_TypeDef * GPIO, uint8_t pin, GPIO_PinState pin_State)
{
	if (pin < GPIO_MAX_PIN) 
	{
		if (pin_State == GPIO_PIN_HIGH)
		{
			GPIO->BSRRL &= ~(0x1 << pin);
			GPIO->BSRRL |= (0x1 << pin);
		}
		else if (pin_State == GPIO_PIN_LOW)
		{
			GPIO->BSRRH &= ~(0x1 << pin);
			GPIO->BSRRH |= (0x1 << pin);
		}
	}
}

void GPIO_togglePin(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		GPIO->ODR ^= (0x1 << pin);
	}	
}


/*----------------------------------------------------------------------------
  GPIO port input data register (GPIOx_IDR)
 *----------------------------------------------------------------------------*/
 
GPIO_PinState GPIO_readPin(GPIO_TypeDef * GPIO, uint8_t pin)
{
	if (pin < GPIO_MAX_PIN) 
	{
		if (((GPIO->IDR & (0x1 << pin)) >> pin) == 0x0)
		{
			return GPIO_PIN_LOW;
		}
		else if (((GPIO->IDR & (0x1 << pin)) >> pin) == 0x1)
		{
			return GPIO_PIN_HIGH;
		}
		else 
		{
			return GPIO_PIN_UNDEF;
		}
	}
	return GPIO_PIN_UNDEF;
}
