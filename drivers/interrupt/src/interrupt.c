/**
* @file 		interrupt.c
* @brief		Source file of interruption drivers.
* @author		Julien
* @date			05/02/2015
* @version	1.0  
* @details	
*
*	Source file listing the functions required to initialize and 
* configure the EXTernal Interrupt controller (EXTI). The Nested
* Vectored Interrupt Controller (NVIC) is already initialized with
* CMSIS's NVIC functions.
*
*/

#include "interrupt.h"

/*----------------------------------------------------------------------------
  Interrupt mask register (EXTI_IMR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line enable.
 * The function sets the appropriate 1 bit of the EXTI IMR register (0b1).
 * @param[in]	line EXTI line to initialize.
 */
void EXTI_enableLine(u8 line) 
{
	if (line < EXTI_MAX_LINE)
	{
		EXTI->IMR |= (0x1 << line);
	}
}


/*----------------------------------------------------------------------------
  SYSCFG external interrupt configuration registers (SYSCFG_EXTICR)
 *----------------------------------------------------------------------------*/

/**
 * Pin association with EXTI line.
 * The function sets the appropriate 4 bits of the appropriate SYSCFG EXTICRx register (x 1..4).
 * @param[in]	line EXTI line to set.
 * @param[in]	pin Pin to associate.
 * @details pin must be in range (SYSCFG_EXTICR_EXTI_PA..SYSCFG_EXTICR_EXTI_PI)
 */
void EXTI_setLinePin(u8 line, u8 pin)
{	
	if (line < EXTI_MAX_LINE && pin <= SYSCFG_EXTICR_EXTI_PI)
	{
		if (line < 4)
		{
			SYSCFG->EXTICR[0] &= ~(0xF << (4 * (line % 4)));
			SYSCFG->EXTICR[0] |= (pin << (4 * (line % 4)));
		}
		else if (line < 8)
		{
			SYSCFG->EXTICR[1] &= ~(0xF << (4 * (line % 4)));
			SYSCFG->EXTICR[1] |= (pin << (4 * (line % 4)));
		}
		else if (line < 12)
		{
			SYSCFG->EXTICR[2] &= ~(0xF << (4 * (line % 4)));
			SYSCFG->EXTICR[2] |= (pin << (4 * (line % 4))); 
		}
		else if (line < EXTI_MAX_LINE)
		{
			SYSCFG->EXTICR[3] &= ~(0xF << (4 * (line % 4)));
			SYSCFG->EXTICR[3] |= (pin << (4 * (line % 4))); 
		}
	}
}


/*----------------------------------------------------------------------------
  Rising trigger selection register (EXTI_RTSR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line rising edge configuration.
 * The function sets the appropriate 1 bit of the EXTI RTSR register (0b1).
 * @param[in]	line EXTI line to configure.
 */
void EXTI_setFallingEdge(u8 line)
{
	if (line < EXTI_MAX_LINE)
	{
		EXTI->FTSR |= (0x1 << line);
	}
}


/*----------------------------------------------------------------------------
  Falling trigger selection register (EXTI_FTSR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line falling edge configuration.
 * The function sets the appropriate 1 bit of the EXTI FTSR register (0b1).
 * @param[in]	line EXTI line to configure.
 */
void EXTI_setRisingEdge(u8 line)
{
	if (line < EXTI_MAX_LINE)
	{
		EXTI->RTSR |= (0x1 << line);
	}
}


/*----------------------------------------------------------------------------
  Pending register (EXTI_PR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line pending status cleared.
 * The function sets the appropriate 1 bit of the EXTI PR register (0b1).
 * @param[in]	line EXTI line to clear.
 */
void EXTI_clearPending(u8 line)
{
	if (line < EXTI_MAX_LINE)
	{
		EXTI->PR |= (0x1 << line);
	}
}
