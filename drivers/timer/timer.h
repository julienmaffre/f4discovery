/**
* @file 		timer.h
* @brief		Header file of TIMER drivers.
* @author		Julien
* @date			30/01/2015
* @version	0.1 
* @details	
*
*	Header file listing the functions required to initiliaze the GP and 
* basic TIMERs (TIM2-TIM7), set their Auto-Reload and Prescalar registers,
* reset their Counter register and Interrupt Flag. A function also 
* initializes a timer to trigger an interrupt at a requested frequency.
*
*		1. Page 213 of the Reference Manual or system_stm32f4xx.c define the 
*		frequency of the timers' clock. It is set at 84MHz acording to the 
*		following formula:
*			TIMxCLK = SystemCoreClock / AHBPSC / APB1PSC * 2
*						  = 168 MHz / 1 / 4 * 2 = 84 MHz
*		2. Use the function defined in the RCC drivers to set the TIMER 
*		clocks.
*				ex: __GPIOD_CLK_ENABLE();
*		3. Initializing a timer usually goes like this:
*			__TIM3_CLK_ENABLE();
*			TIM_enable(TIM3);
*			TIM_initUpcount(TIM3);
*			TIM_setARR(TIM3, 8400);
*			TIM_setPeriod(TIM3, 5000000);
*			TIM_resetCNT(TIM3);
*		4. In the interruption handler, it is necessary to reset the interruption
*		flag.
*			TIM_resetIRFlag(TIM3);
*/
#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <stm32f4xx.h>

#define DEFAULT_PSC 	9999	///< Default PSC value

/*----------------------------------------------------------------------------
  TIMx control register 1 (TIMx_CR1)
 *----------------------------------------------------------------------------*/

/**
 * Timer enable.
 * This function sets the CEN bit of the TIM CR1 register (0b1).
 * @param[in]	TIM Timer to enable.
 */
void TIM_enable(TIM_TypeDef * TIM);

/**
 * Timer set as upcounter.
 * This function sets the DIR bit of the TIM CR1 register (0b0).
 * @param[in]	TIM Timer to initialize.
 */
void TIM_initUpcount(TIM_TypeDef * TIM);

/**
 * Timer set as downcounter.
 * This function sets the DIR bit of the TIM CR1 register (0b1).
 * @param[in]	TIM Timer to initialize.
 */
void TIM_initDowncount(TIM_TypeDef * TIM);


/*----------------------------------------------------------------------------
  TIMx auto-reload register (TIMx_ARR)
 *----------------------------------------------------------------------------*/

/**
 * Auto-Reload register set at desired value.
 * This function writes the desired ARR in the TIM ARR 16-bit register.
 * @param[in]	TIM Timer to set.
 * @param[in]	_arr Value of ARR.
 */
void TIM_setARR(TIM_TypeDef * TIM, u16 arr);


/*----------------------------------------------------------------------------
  TIMx prescaler (TIMx_PSC)
 *----------------------------------------------------------------------------*/

/**
 * Prescaler register set at desired value.
 * This function writes the desired PSC in the TIM PSC 16-bit register.
 * @param[in]	TIM Timer to set.
 * @param[in]	_psc Value of PSC.
 */
void TIM_setPSC(TIM_TypeDef * _timer, u16 psc);


/*----------------------------------------------------------------------------
  TIMx counter (TIMx_CNT)
 *----------------------------------------------------------------------------*/
 
/**
 * Counter register reset.
 * This function resets the TIM CNT 16-bit register.
 * @param[in]	TIM Timer to reset.
 */
void TIM_resetCNT(TIM_TypeDef * TIM);


/*----------------------------------------------------------------------------
  TIMx status register (TIMx_SR)
 *----------------------------------------------------------------------------*/
 
/**
 * Interruption Flag reset.
 * This function resets the UIF bit of the TIM SR 16-bit register.
 * @param[in]	TIM Timer to reset.
 * @details To be used in most IR handlers to acknowledge the interruption.
 */
void TIM_resetIRFlag(TIM_TypeDef * TIM);


/*----------------------------------------------------------------------------
  More than one registers
 *----------------------------------------------------------------------------*/
 
/**
 * Timer set to generate an event (overflow or underflow) at a constant period.
 * This function sets the TIM PSC register and then calculates the value of TIM ARR 
 * register according to the TIMxCLK.
 * @param[in]	TIM Timer to set.
 * @param[in]	_usPeriod Period of the interruption in µs.
 * @details 
 * CLK resolution 1MHz (less than this, the division by 1000000 makes it invisible)
 * For CLC Timer = 84MHz and PSC = 9999, 
 * 							 	- ARR = 0x0001: T = 0x1/8400 ~ 119ms
 * 								- ARR = 0xFFFF: T = 0xFFF/8400 ~ 7800ms
 */
void TIM_setPeriod(TIM_TypeDef * TIM, u32 usperiod);

#endif
