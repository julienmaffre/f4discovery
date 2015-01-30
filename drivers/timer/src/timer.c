/**
* @file 		timer.h
* @brief		Source file of TIMER drivers.
* @author		Julien
* @date			30/01/2015
* @version	0.1 
* @details	
*
*	Source file listing the functions required to initiliaze the GP and 
* basic TIMERs (TIM2-TIM7), set their Auto-Reload and Prescalar registers,
* reset their Counter register and Interrupt Flag. A function also 
* initializes a timer to trigger an interrupt at a requested frequency.
*
*/
#include "timer.h"

/*----------------------------------------------------------------------------
  TIMx control register 1 (TIMx_CR1)
 *----------------------------------------------------------------------------*/

/**
 * Timer enable.
 * The function sets the CEN bit of the TIM CR1 register (0b1).
 * @param[in]	_timer Timer to enable.
 */
void TIM_enable(TIM_TypeDef * _timer) 
{
	_timer->CR1 |= TIM_CR1_CEN;	
}

/**
 * Timer set as upcounter.
 * The function sets the DIR bit of the TIM CR1 register (0b0).
 * @param[in]	_timer Timer to initialize.
 */
void TIM_initUpcount(TIM_TypeDef * _timer)
{
	_timer->CR1 &= ~TIM_CR1_DIR;
}

/**
 * Timer set as downcounter.
 * The function sets the DIR bit of the TIM CR1 register (0b1).
 * @param[in]	_timer Timer to initialize.
 */
void TIM_initDowncount(TIM_TypeDef * _timer)
{
	_timer->CR1 &= ~TIM_CR1_DIR;
	_timer->CR1 |= TIM_CR1_DIR;
}


/*----------------------------------------------------------------------------
  TIMx auto-reload register (TIMx_ARR)
 *----------------------------------------------------------------------------*/

/**
 * Auto-Reload register set at desired value.
 * The function write the desired ARR in the TIM ARR 16-bit register.
 * @param[in]	_timer Timer to set.
 * @param[in]	_arr Value of ARR.
 */
void TIM_setARR(TIM_TypeDef * _timer, u16 _arr)
{
	_timer->ARR = _arr;
}


/*----------------------------------------------------------------------------
  TIMx prescaler (TIMx_PSC)
 *----------------------------------------------------------------------------*/

/**
 * Prescaler register set at desired value.
 * The function write the desired PSC in the TIM PSC 16-bit register.
 * @param[in]	_timer Timer to set.
 * @param[in]	_psc Value of PSC.
 */
void TIM_setPSC(TIM_TypeDef * _timer, u16 _psc)
{
	_timer->PSC = _psc;
}


/*----------------------------------------------------------------------------
  TIMx counter (TIMx_CNT)
 *----------------------------------------------------------------------------*/
 
/**
 * Counter register reset.
 * The function resets the TIM CNT 16-bit register.
 * @param[in]	_timer Timer to reset.
 */
void TIM_resetCNT(TIM_TypeDef * _timer)
{
	_timer->EGR |= TIM_EGR_UG;
}


/*----------------------------------------------------------------------------
  TIMx status register (TIMx_SR)
 *----------------------------------------------------------------------------*/
 
/**
 * Interruption Flag reset.
 * The function resets the UIF bit of the TIM SR 16-bit register.
 * @param[in]	_timer Timer to reset.
 * @details To be used in most IR handlers to acknowledge the interruption.
 */
void TIM_resetIRFlag(TIM_TypeDef * _timer)
{
	_timer->SR &= ~TIM_SR_UIF;
}


/*----------------------------------------------------------------------------
  More than one registers
 *----------------------------------------------------------------------------*/
 
/**
 * Timer set to generate an event (overflow or underflow) at a constant period.
 * The function sets the TIM PSC register and then calculates the value of TIM ARR 
 * register according to the TIMxCLK.
 * @param[in]	_timer Timer to set.
 * @param[in]	_usPeriod Period of the interruption in µs.
 * @details 
 * CLK resolution 1MHz (less than this, the division by 1000000 makes it invisible)
 * For CLC Timer = 84MHz and PSC = 9999, 
 * 							 	- ARR = 0x0001: T = 0x1/8400 ~ 119ms
 */
void TIM_setPeriod(TIM_TypeDef * _timer, u32 _usPeriod)
{
	u32 tim_clk = (SystemCoreClock * 1 / 4 * 2);
	
	_timer->PSC = DEFAULT_PSC;
	_timer->ARR = (_usPeriod * (tim_clk / 1000000)) / (_timer->PSC + 1) ;
}
