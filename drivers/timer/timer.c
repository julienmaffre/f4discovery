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

void TIM_enable(TIM_TypeDef * TIM) 
{
	TIM->CR1 |= TIM_CR1_CEN;	
}

void TIM_initUpcount(TIM_TypeDef * TIM)
{
	TIM->CR1 &= ~TIM_CR1_DIR;
}

void TIM_initDowncount(TIM_TypeDef * TIM)
{
	TIM->CR1 &= ~TIM_CR1_DIR;
	TIM->CR1 |= TIM_CR1_DIR;
}


/*----------------------------------------------------------------------------
  TIMx auto-reload register (TIMx_ARR)
 *----------------------------------------------------------------------------*/

void TIM_setARR(TIM_TypeDef * TIM, u16 arr)
{
	TIM->ARR = arr;
}


/*----------------------------------------------------------------------------
  TIMx prescaler (TIMx_PSC)
 *----------------------------------------------------------------------------*/

void TIM_setPSC(TIM_TypeDef * TIM, u16 psc)
{
	TIM->PSC = psc;
}


/*----------------------------------------------------------------------------
  TIMx counter (TIMx_CNT)
 *----------------------------------------------------------------------------*/
 
void TIM_resetCNT(TIM_TypeDef * TIM)
{
	TIM->EGR |= TIM_EGR_UG;
}


/*----------------------------------------------------------------------------
  TIMx status register (TIMx_SR)
 *----------------------------------------------------------------------------*/
 
void TIM_resetIRFlag(TIM_TypeDef * TIM)
{
	TIM->SR &= ~TIM_SR_UIF;
}


/*----------------------------------------------------------------------------
  More than one registers
 *----------------------------------------------------------------------------*/
 
void TIM_setPeriod(TIM_TypeDef * TIM, u32 usperiod)
{
	u32 tim_clk = (SystemCoreClock * 1 / 4 * 2);
	
	TIM->PSC = DEFAULT_PSC;
	TIM->ARR = (usperiod * (tim_clk / 1000000)) / (TIM->PSC + 1) ;
}
