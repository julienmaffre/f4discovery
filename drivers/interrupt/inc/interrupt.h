/**
* @file 		interrupt.h
* @brief		Header file of interruption drivers.
* @author		Julien
* @date			05/02/2015
* @version	1.0  
* @details	
*
*	Header file listing the functions required to initialize and 
* configure the EXTernal Interrupt controller (EXTI). The Nested
* Vectored Interrupt Controller (NVIC) is already initialized with
* CMSIS's NVIC functions.
*
* 	1. Events aren't supported yet.
* 	2. See interrupt routines' names in startup_stm32f40_41xxx.s.
* 	3. Reffer to CMSIS to program NVIC 
*		Page 194 programming manual:
*		
*			void NVIC_EnableIRQ(IRQn_Type IRQn) 											Enables an interrupt or exception.
*		
*			void NVIC_DisableIRQ(IRQn_Type IRQn) 											Disables an interrupt or exception.
*		
*			void NVIC_SetPendingIRQ(IRQn_Type IRQn) 									Sets the pending status of interrupt or
*																																exception to 1.
*																								
*			void NVIC_ClearPendingIRQ(IRQn_Type IRQn) 								Clears the pending status of interrupt or
*																																exception to 0.
*																								
*			uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn) 							Reads the pending status of interrupt or
*																																exception. This function returns nonzero
*																																value if the pending status is set to 1.	
*																								
*			void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) 	Sets the priority of an interrupt or
*																																exception with configurable priority level
*																																to 1.
*																															
*			uint32_t NVIC_GetPriority(IRQn_Type IRQn)									Reads the priority of an interrupt or
*																																exception with configurable priority
*																																level. This function return the current
*																																priority level.
*		4. The initialization of an interrupt usually goes like this (PA0:
*				__SYSCFG_CLK_ENABLE();
*				NVIC_EnableIRQ(EXTI0_IRQn);
*				EXTI_enableLine(0);
*				EXTI_setFallingEdge(0);
*				EXTI_setRisingEdge(0);
*				EXTI_setLinePin(0, SYSCFG_EXTICR_EXTI_PA);
*		
*/

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdio.h>
#include <stm32f4xx.h>

/* Redefinition of SYSCFG EXTI configuration registers 
	 since all EXTICR0..4 registers are the same        */
#define SYSCFG_EXTICR_EXTI_PA		SYSCFG_EXTICR1_EXTI0_PA
#define SYSCFG_EXTICR_EXTI_PB		SYSCFG_EXTICR1_EXTI0_PB
#define SYSCFG_EXTICR_EXTI_PC		SYSCFG_EXTICR1_EXTI0_PC
#define SYSCFG_EXTICR_EXTI_PD		SYSCFG_EXTICR1_EXTI0_PD
#define SYSCFG_EXTICR_EXTI_PE		SYSCFG_EXTICR1_EXTI0_PE
#define SYSCFG_EXTICR_EXTI_PF		SYSCFG_EXTICR1_EXTI0_PF
#define SYSCFG_EXTICR_EXTI_PG		SYSCFG_EXTICR1_EXTI0_PG
#define SYSCFG_EXTICR_EXTI_PH		SYSCFG_EXTICR1_EXTI0_PH
#define SYSCFG_EXTICR_EXTI_PI		SYSCFG_EXTICR1_EXTI0_PI

#define EXTI_MAX_LINE 					16															///< Number max of EXTI lines 0..15

/*----------------------------------------------------------------------------
  Interrupt mask register (EXTI_IMR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line enable.
 * The function sets the appropriate 1 bit of the EXTI IMR register (0b1).
 * @param[in]	line EXTI line to initialize.
 */
void EXTI_enableLine(u8 line);


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
void EXTI_setLinePin(u8 line, u8 pin);


/*----------------------------------------------------------------------------
  Rising trigger selection register (EXTI_RTSR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line rising edge configuration.
 * The function sets the appropriate 1 bit of the EXTI RTSR register (0b1).
 * @param[in]	line EXTI line to configure.
 */
void EXTI_setRisingEdge(u8 line);


/*----------------------------------------------------------------------------
  Falling trigger selection register (EXTI_FTSR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line falling edge configuration.
 * The function sets the appropriate 1 bit of the EXTI FTSR register (0b1).
 * @param[in]	line EXTI line to configure.
 */
void EXTI_setFallingEdge(u8 line);


/*----------------------------------------------------------------------------
  Pending register (EXTI_PR)
 *----------------------------------------------------------------------------*/

/**
 * EXTI line pending status cleared.
 * The function sets the appropriate 1 bit of the EXTI PR register (0b1).
 * @param[in]	line EXTI line to clear.
 */
void EXTI_clearPending(u8 line);

#endif
